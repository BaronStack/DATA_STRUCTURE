class Solution {
public:
    string longestCommonPrefix(vector<string>& strs) {
        std::string res;
        if (strs.size() <= 1) return strs[0];
        
        int min_len = -1;
        for (int i = 1;i < strs.size();i ++) {
            if (strs[i].size() == 0) return res;
            min_len = strs[i].size() < min_len ? strs[i].size() : min_len;
        }

        for (int i = 0;i < min_len; i++) {
            int j = 1;
            for (; j < strs.size(); j++) {
                if(strs[j][i] != strs[j-1][i]) return res;
            }
            if (j == strs.size())
                res += strs[0][i];
        }
        return res;
    }
};
