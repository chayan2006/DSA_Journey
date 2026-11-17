class Solution {
public:
    int minimumChanges(string s, int k) {
        int n = s.size();
        const int INF = 1e9;

        // cost[i][j] = min changes to make s[i..j] a semi-palindrome
        vector<vector<int>> cost(n, vector<int>(n, INF));
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                int len = j - i + 1;
                for (int d = 1; d <= len / 2; d++) {
                    if (len % d) continue;
                    int m = len / d, cnt = 0;
                    for (int r = 0; r < d; r++)
                        for (int a = 0, b = m - 1; a < b; a++, b--)
                            if (s[i + r + a * d] != s[i + r + b * d]) cnt++;
                    cost[i][j] = min(cost[i][j], cnt);
                }
            }
        }

        // dp[i][j] = min cost to split the first i chars into j parts
        vector<vector<int>> dp(n + 1, vector<int>(k + 1, INF));
        dp[0][0] = 0;
        for (int j = 1; j <= k; j++)
            for (int i = 2 * j; i <= n; i++)
                for (int p = 2 * (j - 1); p <= i - 2; p++)
                    if (dp[p][j - 1] < INF && cost[p][i - 1] < INF)
                        dp[i][j] = min(dp[i][j], dp[p][j - 1] + cost[p][i - 1]);
        return dp[n][k];
    }
};