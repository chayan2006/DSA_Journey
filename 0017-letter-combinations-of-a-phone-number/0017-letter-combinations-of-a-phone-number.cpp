class Solution {
public:
    vector<string> letterCombinations(string digits) {
        vector<string> res;
        if (digits.empty()) return res;

        vector<string> mp = {"", "", "abc", "def", "ghi", "jkl",
                             "mno", "pqrs", "tuv", "wxyz"};
        string cur;
        backtrack(0, digits, mp, cur, res);
        return res;
    }

private:
    void backtrack(int i, const string& digits, const vector<string>& mp,
                   string& cur, vector<string>& res) {
        if (i == digits.size()) {
            res.push_back(cur);
            return;
        }
        for (char c : mp[digits[i] - '0']) {
            cur.push_back(c);                    // choose
            backtrack(i + 1, digits, mp, cur, res);  // explore
            cur.pop_back();                      // undo
        }
    }
};