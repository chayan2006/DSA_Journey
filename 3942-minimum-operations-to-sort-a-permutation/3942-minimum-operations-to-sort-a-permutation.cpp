
class Solution {
public:
    int minOperations(vector<int>& nums) {
        int n = nums.size();
        int k = nums[0];

        bool inc = true, dec = true;

        for (int i = 0; i < n; i++) {
            if (nums[i] != (k + i) % n)
                inc = false;

            if (nums[i] != (k - i + n) % n)
                dec = false;
        }

        int ans = INT_MAX;

        if (inc) {
            int left = (n - k) % n;
            int right = (k == 0 ? 0 : k + 2);
            ans = min(left, right);
        }

        if (dec) {
            int r = (k + 1) % n;
            int cost = 1 + min(r, (n - r) % n);
            ans = min(ans, cost);
        }

        return ans == INT_MAX ? -1 : ans;
    }
};

