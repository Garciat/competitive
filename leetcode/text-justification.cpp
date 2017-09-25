// https://leetcode.com/problems/text-justification/

class Solution {
public:
    vector<string> fullJustify(vector<string>& words, int maxWidth) {
        for (string& word : words) {
            if (word.size() > maxWidth)
                return {};
        }
        
        vector<string> ans;
        int totalWordSize = 0;
        vector<string*> lineElems;
        
        for (string& word : words) {
            if (totalWordSize + lineElems.size() + word.size() > maxWidth) {
                string line;
                int separations = lineElems.size() - 1;
                int spaces = maxWidth - totalWordSize;
                int avail = spaces;
                
                for (int i = 0; i < lineElems.size(); ++i) {
                    if (i > 0) {
                        int use = spaces/separations + int(spaces % separations >= i);
                        line += string(use, ' ');
                        avail -= use;
                    }
                    
                    line += *lineElems[i];
                }
                
                line += string(avail, ' ');
                
                ans.push_back(line);
                
                lineElems.clear();
                totalWordSize = 0;
            }
            
            lineElems.push_back(&word);
            totalWordSize += word.size();
        }
        
        {
            string line;
        
            for (int i = 0; i < lineElems.size(); ++i) {
                if (i > 0) {
                    line += ' ';
                }

                line += *lineElems[i];
            }

            line += string(maxWidth - line.size(), ' ');

            ans.push_back(line);
        }
        
        return ans;
    }
};
