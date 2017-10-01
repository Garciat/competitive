# https://leetcode.com/problems/first-unique-character-in-a-string/

def find_first_unique_char(s):
    seen_chars = set()
    unique_chars_to_position = {}

    for idx, c in enumerate(s):
        if c in seen_chars:
            continue
        elif c in unique_chars_to_position:
            del unique_chars_to_position[c]
            seen_chars.add(c)
        else:
            unique_chars_to_position[c] = idx

    if not unique_chars_to_position:
        return -1

    return min(unique_chars_to_position.values())

class Solution(object):
    def firstUniqChar(self, s):
        return find_first_unique_char(s)
