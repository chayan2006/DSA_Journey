class Solution {
public:
    int numOfSubarrays(vector<int>& arr) {
        const int MOD = 1e9 + 7;
        long long even = 1, odd = 0;  // even starts at 1 for the empty prefix (sum 0)
        int parity = 0;
        long long ans = 0;

        for (int x : arr) {
            parity ^= (x & 1);        // running prefix-sum parity
            if (parity) {             // odd prefix: pair with earlier even prefixes
                ans += even;
                odd++;
            } else {                  // even prefix: pair with earlier odd prefixes
                ans += odd;
                even++;
            }
            ans %= MOD;
        }
        return (int)ans;
    }
};