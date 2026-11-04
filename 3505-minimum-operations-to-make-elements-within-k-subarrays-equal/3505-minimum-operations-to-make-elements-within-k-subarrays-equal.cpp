
class Solution {
private:
    multiset<int> low, high;
    long long sumLow = 0, sumHigh = 0;

    void balance() {
        while (low.size() > high.size() + 1) {
            int val = *low.rbegin();

            low.erase(prev(low.end()));
            sumLow -= val;

            high.insert(val);
            sumHigh += val;
        }

        while (low.size() < high.size()) {
            int val = *high.begin();

            high.erase(high.begin());
            sumHigh -= val;

            low.insert(val);
            sumLow += val;
        }
    }

    void addNum(int val) {
        if (low.empty() || val <= *low.rbegin()) {
            low.insert(val);
            sumLow += val;
        } else {
            high.insert(val);
            sumHigh += val;
        }

        balance();
    }

    void removeNum(int val) {
        auto it = low.find(val);

        if (it != low.end()) {
            low.erase(it);
            sumLow -= val;
        } else {
            it = high.find(val);
            high.erase(it);
            sumHigh -= val;
        }

        balance();
    }

    long long getCost() {
        long long median = *low.rbegin();

        return median * low.size() - sumLow
             + sumHigh - median * high.size();
    }

public:
    long long minOperations(vector<int>& nums, int x, int k) {
        int n = nums.size();

        low.clear();
        high.clear();
        sumLow = sumHigh = 0;

        // Step 1: Calculate cost of every window
        vector<long long> cost(n - x + 1);

        for (int i = 0; i < x; i++) {
            addNum(nums[i]);
        }

        cost[0] = getCost();

        for (int i = x; i < n; i++) {
            removeNum(nums[i - x]);
            addNum(nums[i]);

            cost[i - x + 1] = getCost();
        }

        // Step 2: Dynamic Programming
        const long long INF = 1e18;

        vector<vector<long long>> dp(
            k + 1,
            vector<long long>(n + 1, INF)
        );

        // Zero subarrays require zero operations
        for (int i = 0; i <= n; i++) {
            dp[0][i] = 0;
        }

        // dp[t][i] = minimum cost to select
        // t non-overlapping windows from first i elements

        for (int t = 1; t <= k; t++) {
            for (int i = 1; i <= n; i++) {

                // Option 1: Skip current element
                dp[t][i] = dp[t][i - 1];

                // Option 2: Select window ending at i-1
                if (i >= x && dp[t - 1][i - x] != INF) {
                    dp[t][i] = min(
                        dp[t][i],
                        dp[t - 1][i - x] + cost[i - x]
                    );
                }
            }
        }

        return dp[k][n];
    }
};
