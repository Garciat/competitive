import argparse
from collections import namedtuple
import errno
from functools import partial
from functools32 import lru_cache
import itertools
import multiprocessing.pool
import os
import re
import requests
import time


API_BASE_URL = 'http://codeforces.com'

PAGE_SIZE = 100

SUBDIR_MODE = 0755

LANGUAGE_INFO = [
    ('GNU C', 'c', '//'),
    ('GNU C11', 'c', '//'),
    ('GNU C++', 'cpp', '//'),
    ('GNU C++0x', 'cpp', '//'),
    ('GNU C++11', 'cpp', '//'),
    ('GNU C++14', 'cpp', '//'),
    ('Haskell', 'hs', '--'),
    ('Python 2', 'py', '#'),
    ('Python 3', 'py', '#'),
]


class Language(object):
    def __init__(self, name, ext, comment):
        self.name = name
        self.ext = ext
        self.comment = comment

    def format_filename(self, s):
        return '{}.{}'.format(s, self.ext)

    def format_comment(self, s):
        return '{} {}'.format(self.comment, s)


LANGUAGES = {x[0]: Language(*x) for x in LANGUAGE_INFO}


class Session(namedtuple('Session', ['session_id', 'csrf_token'])):
    pass


class Contest(namedtuple('Contest', ['id', 'name', 'slug'])):
    pass


class Problem(namedtuple('Problem', ['contest_id', 'index', 'name'])):
    @property
    def url(self):
        return '{}/problemset/problem/{}/{}'.format(
            API_BASE_URL,
            self.contest_id,
            self.index,
        )


class Submission(namedtuple('Submission', ['id', 'problem', 'verdict', 'language'])):
    @property
    def is_ok(self):
        return self.verdict == 'OK'

    @property
    def source_tag(self):
        return self.language.format_comment(self.problem.url)

    @property
    def filename(self):
        return self.language.format_filename(self.problem.index)

    def format_source(self, source):
        return '{}\n\n{}\n'.format(
            self.source_tag,
            source.replace('\r\n', '\n').strip(),
        )


class SourceFile(namedtuple('SourceFile', ['filename', 'contents'])):
    pass


class NoResponse(BaseException):
    pass


def with_retry(f):
    response = None
    wait_time = 1.5

    for i in range(10):
        try:
            response = f()
        except:
            time.sleep(wait_time ** (i + 1))
        else:
            break

    if response is None:
        raise NoResponse

    return response


def makedirs_safe(path, mode):
    try:
        os.makedirs(path, mode)
    except OSError as exception:
        if exception.errno != errno.EEXIST:
            raise


def remove_prefix(s, prefix):
    return s[len(prefix):] if s.startswith(prefix) else s


def canonicalize_contest_name(raw_name):
    parts = re.sub('[^a-z0-9]', ' ', raw_name.lower()).split(' ')
    slug = '-'.join(filter(None, parts))
    return remove_prefix(slug, 'codeforces-')


@lru_cache(maxsize=1000)
def get_contest(contest_id):
    url = '{}/api/contest.standings?contestId={}&from=1&count=1'.format(
        API_BASE_URL,
        contest_id,
    )

    response = with_retry(lambda: requests.get(url).json())

    name = response['result']['contest']['name']
    slug = canonicalize_contest_name(name)

    return Contest(
        id=contest_id,
        name=name,
        slug=slug,
    )


def get_user_submissions_page(user_handle, index, count):
    url = '{}/api/user.status?handle={}&from={}&count={}'.format(
        API_BASE_URL,
        user_handle,
        index + 1,
        count,
    )

    response = with_retry(lambda: requests.get(url).json())

    submissions = []

    for fields in response['result']:
        submissions.append(Submission(
            id=fields['id'],
            problem=Problem(
                contest_id=fields['contestId'],
                index=fields['problem']['index'],
                name=fields['problem']['name'],
            ),
            verdict=fields['verdict'],
            language=LANGUAGES[fields['programmingLanguage']],
        ))

    return submissions


def get_user_submissions(user_handle):
    submissions = []

    for index in itertools.count(start=0, step=PAGE_SIZE):
        page = get_user_submissions_page(user_handle, index, PAGE_SIZE)
        if not page:
            break
        submissions.extend(page)

    return submissions


def get_user_ok_submissions(user_handle):
    submissions = get_user_submissions(user_handle)
    return [s for s in submissions if s.is_ok]


def get_session(session_id):
    """Looks for the following tag:

    <meta name="X-Csrf-Token" content="..."/>
    """

    url = API_BASE_URL

    cookies = {
        'JSESSIONID': session_id,
    }

    r = with_retry(lambda: requests.get(url, cookies=cookies, stream=True))

    csrf_token = None

    for line in r.iter_lines():
        if '<meta name="X-Csrf-Token"' in line:
            csrf_token = line.split('"')[3]
            r.close()
            break

    if csrf_token is None:
        raise NoResponse

    return Session(
        session_id=session_id,
        csrf_token=csrf_token,
    )


def get_submission_source_contents(submission_id, session):
    url = '{}/data/submitSource'.format(
        API_BASE_URL,
    )

    data = {
        'submissionId': submission_id,
        'csrf_token': session.csrf_token,
    }

    cookies = {
        'JSESSIONID': session.session_id,
    }

    response = with_retry(lambda: requests.post(url, data=data, cookies=cookies).json())

    return response['source']


def get_source_file(submission, session):
    contest = get_contest(submission.problem.contest_id)

    source = get_submission_source_contents(submission.id, session)

    return SourceFile(
        filename=os.path.join(contest.slug, submission.filename),
        contents=submission.format_source(source),
    )


def save_source_file(destination, source_file):
    filepath = os.path.join(destination, source_file.filename)

    if os.path.exists(filepath):
        return None

    makedirs_safe(os.path.dirname(filepath), SUBDIR_MODE)

    with open(filepath, 'wt') as f:
        f.write(source_file.contents)

    return filepath


def download_user_submissions(user_handle, destination, session_id):
    session = get_session(session_id)

    submissions = get_user_ok_submissions(user_handle)

    pool = multiprocessing.pool.ThreadPool(4)

    func = partial(get_source_file, session=session)

    for source_file in pool.imap(func, submissions):
        filepath = save_source_file(destination, source_file)
        if filepath:
            print 'DONE', filepath


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument('user_handle')
    parser.add_argument('destination')
    parser.add_argument('session_id')

    args = parser.parse_args()

    download_user_submissions(args.user_handle, args.destination, args.session_id)


if __name__ == '__main__':
    main()
