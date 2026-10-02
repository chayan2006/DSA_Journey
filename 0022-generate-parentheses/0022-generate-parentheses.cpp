class Solution {
public:
    vector<string> generateParenthesis(int n) {
        vector<string> ans;
        string s;

        backtrack(ans, s, 0, 0, n);
        return ans;
    }

    void backtrack(vector<string>& ans, string& s,
                   int open, int close, int n) {
        if (s.size() == 2 * n) {
            ans.push_back(s);
            return;
        }

        if (open < n) {
            s.push_back('(');
            backtrack(ans, s, open + 1, close, n);
            s.pop_back();
        }

        if (close < open) {
            s.push_back(')');
            backtrack(ans, s, open, close + 1, n);
            s.pop_back();
        }
    }
};