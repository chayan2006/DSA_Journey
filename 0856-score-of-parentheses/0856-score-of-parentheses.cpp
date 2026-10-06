class Solution {
public:
    int scoreOfParentheses(string s) {
        int depth = 0;
        int score = 0;

        for (int i = 0; i < s.size(); i++) {
            if (s[i] == '(') {
                depth++;
            } else {
                depth--;
                if (s[i - 1] == '(') {      // yeh ek "()" tha
                    score += 1 << depth;    // 2^depth
                }
            }
        }
        return score;
    }
};