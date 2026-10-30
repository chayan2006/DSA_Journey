
class Solution {
public:
    string reverseVowels(string s) {
        int i = 0, j = s.size() - 1;

        while (i < j) {
            while (i < j && string("aeiouAEIOU").find(s[i]) == string::npos) {
                i++;
            }

            while (i < j && string("aeiouAEIOU").find(s[j]) == string::npos) {
                j--;
            }

            swap(s[i], s[j]);
            i++;
            j--;
        }

        return s;
    }
};
