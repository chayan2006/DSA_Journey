class Solution {
public:
    vector<long long> resultArray(vector<int>& nums, int k) {
        vector<long long> res(k, 0), cnt(k, 0);

        for (int v : nums) {
            vector<long long> nw(k, 0);
            for (int r = 0; r < k; r++) {
                nw[(r * (v % k)) % k] += cnt[r];
            }
            nw[v % k] += 1;

            for (int r = 0; r < k; r++) res[r] += nw[r];
            cnt = nw;
        }
        return res;
    }
};