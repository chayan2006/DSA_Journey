
class Solution {
public:
    int climbStairs(int n, vector<int>& costs) {

        vector<int> dp(n + 1, INT_MAX);

        // Starting point
        dp[0] = 0;

        for (int i = 1; i <= n; i++) {

            // We can jump from previous 1, 2 or 3 steps
            for (int j = 1; j <= 3; j++) {

                int prev = i - j;

                if (prev >= 0) {

                    int jumpCost = costs[i - 1] + j * j;

                    dp[i] = min(dp[i],
                                dp[prev] + jumpCost);
                }
            }
        }

        return dp[n];
    }
};
