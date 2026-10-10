class Solution {
public:
    long long minSumSquareDiff(vector<int>& nums1, vector<int>& nums2, int k1, int k2) {
        const int M = 100000;
        vector<long long> cnt(M + 1, 0);
        int n = nums1.size();
        long long k = (long long)k1 + k2;

        for (int i = 0; i < n; i++) {
            cnt[abs(nums1[i] - nums2[i])]++;
        }

        for (int v = M; v > 0 && k > 0; v--) {
            if (cnt[v] == 0) continue;
            long long take = min(k, cnt[v]);
            cnt[v] -= take;
            cnt[v - 1] += take;
            k -= take;
        }

        long long ans = 0;
        for (long long v = 1; v <= M; v++) {
            ans += cnt[v] * v * v;
        }
        return ans;
    }
};