class Solution {
public:
    int minAddToMakeValid(string s) {
        int open = 0;   // unmatched '('
        int add = 0;    // insertions needed for unmatched ')'

        for (char c : s) {
            if (c == '(') {
                open++;
            } else {
                if (open > 0) open--;   // match mil gaya
                else add++;             // match nahi mila, '(' insert karna padega
            }
        }
        return open + add;   // bache hue '(' ko close karne ke liye ')' chahiye
    }
};