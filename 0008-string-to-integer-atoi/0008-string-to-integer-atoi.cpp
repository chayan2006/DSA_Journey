
class Solution {
public:
    int myAtoi(string s) {
        int i = 0, n = s.size();

        // 1. Skip leading whitespaces
        while (i < n && s[i] == ' ') {
            i++;
        }

        // 2. Check sign
        int sign = 1;
        if (i < n && (s[i] == '+' || s[i] == '-')) {
            if (s[i] == '-') sign = -1;
            i++;
        }

        // 3. Convert digits and handle overflow
        long long num = 0;

        while (i < n && isdigit(s[i])) {
            int digit = s[i] - '0';

            num = num * 10 + digit;

            if (sign * num <= INT_MIN) return INT_MIN;
            if (sign * num >= INT_MAX) return INT_MAX;

            i++;
        }

        return sign * num;
    }
};
