class Solution {
public:
    string reverseParentheses(string s) {
        stack<char> st;

        for (char c : s) {
            if (c == ')') {
                // Reverse everything until '('
                string temp;

                while (st.top() != '(') {
                    temp += st.top();
                    st.pop();
                }

                // Remove '('
                st.pop();

                // Put reversed string back
                for (char ch : temp) {
                    st.push(ch);
                }
            }
            else {
                st.push(c);
            }
        }

        // Build final answer
        string ans;

        while (!st.empty()) {
            ans += st.top();
            st.pop();
        }

        reverse(ans.begin(), ans.end());

        return ans;
    }
};