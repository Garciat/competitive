# https://leetcode.com/problems/word-frequency/

# Read from the file words.txt and output the word frequency list to stdout.
awk '{a[$1]++}END{for(k in a)if(k)print k,a[k]}' RS=" |\n" words.txt | sort -r -n -k2
