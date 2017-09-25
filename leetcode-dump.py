import os
import json
import requests
from collections import namedtuple
import multiprocessing


API_BASE_URL = 'https://leetcode.com'

SESSION_ID = os.getenv('SESSION_ID', '')

COOKIES = dict(LEETCODE_SESSION=SESSION_ID)

SOURCE_MARKER = '  submissionCode: '

# from: "  editCodeUrl: '/problems/hamming-distance/',"
PROBLEM_ID_MARKER = '  editCodeUrl: '

LANG_EXTENSIONS = {
    'c': 'c',
    'cpp': 'cpp',
    'python': 'py',
    'javascript': 'js',
    'golang': 'go',
    'mysql': 'sql',
    'bash': 'sh',
}

LANG_COMMENT = {
    'c': '//',
    'cpp': '//',
    'python': '#',
    'javascript': '//',
    'golang': '//',
    'mysql': '--',
    'bash': '#',
}


Submission = namedtuple('Submission', ['problem_id', 'source'])

SourceFile = namedtuple('SourceFile', ['filename', 'contents'])


def get_submissions():
    i = 0
    n = 10000
    submissions = []
    while True:
        url = API_BASE_URL + '/api/submissions/?offset={}&limit={}'.format(i, n)
        req = requests.get(url, cookies=COOKIES)
        response = req.json()
        submissions.extend(response['submissions_dump'])
        if not response['has_next']:
            break
        i += n
    return submissions


def get_submission(path):
    url = API_BASE_URL + path
    req = requests.get(url, cookies=COOKIES, stream=True)
    problem_id = None
    source = None
    for line in req.iter_lines():
        if line.startswith(SOURCE_MARKER):
            # source starts with: '  submissionCode: '
            # and ends with: ','
            # it is surrounded by single quotes and special characters are encoded as '\uXXXX'
            source_str = line[len(SOURCE_MARKER):-1]
            source = eval('u{}'.format(source_str))
        if line.startswith(PROBLEM_ID_MARKER):
            problem_id = line[len("  editCodeUrl: '/problems/"):-len("/',")]
        if problem_id and source:
            return Submission(problem_id, source)


def lang_to_extension(lang):
    return LANG_EXTENSIONS.get(lang, lang)


def lang_comment(lang, s):
    return '{} {}'.format(LANG_COMMENT.get(lang, '//'), s)


def download_submission(descriptor):
    submission = get_submission(descriptor['url'])

    extension = lang_to_extension(descriptor['lang'])
    filename = '{}.{}'.format(submission.problem_id, extension)
    ref_link = '{}/problems/{}/'.format(API_BASE_URL, submission.problem_id)

    contents = lang_comment(descriptor['lang'], ref_link)
    contents += '\n\n'
    contents += submission.source.strip()
    contents += '\n'

    return SourceFile(
        filename=filename,
        contents=contents,
    )


def main():
    destination = 'leetcode'
    p = multiprocessing.Pool(8)
    accepted_submissions = [s for s in get_submissions() if s['status_display'] == 'Accepted']
    for source_file in p.imap(download_submission, accepted_submissions):
        filepath = os.path.join(destination, source_file.filename)
        if os.path.exists(filepath):
            continue
        with open(filepath, 'wt') as f:
            f.write(source_file.contents)
        print 'DONE', source_file.filename


if __name__ == '__main__':
    main()
