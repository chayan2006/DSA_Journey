class Solution {
public:
    int reverseDegree(string s) {
        int total = 0;
        for (int i = 0; i < s.size(); i++) {
            int rev = 'z' - s[i] + 1;   // reversed alphabet position
            total += rev * (i + 1);     // 1-indexed position
        }
        return total;
    }
};