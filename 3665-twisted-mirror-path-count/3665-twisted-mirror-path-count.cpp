class Solution {
public:
    int uniquePaths(vector<vector<int>>& grid) {
        const int MOD = 1e9 + 7;
        int m = grid.size(), n = grid[0].size();

        vector<vector<int>> dp(m, vector<int>(n, 0));

        // go[i][j][d] stores the final destination of a move
        // entering cell (i,j) in direction d.
        // d = 0: right, d = 1: down
        vector<vector<array<int, 2>>> go(
            m, vector<array<int, 2>>(n, {-2, -2})
        );

        function<int(int, int, int)> resolve =
            [&](int x, int y, int d) -> int {
                if (x < 0 || x >= m || y < 0 || y >= n)
                    return -1;

                int &res = go[x][y][d];

                if (res != -2)
                    return res;

                // Empty cell: valid final destination
                if (grid[x][y] == 0)
                    return res = x * n + y;

                // Mirror: right -> down, down -> right
                if (d == 0)
                    return res = resolve(x + 1, y, 1);

                return res = resolve(x, y + 1, 0);
            };

        dp[0][0] = 1;

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (dp[i][j] == 0)
                    continue;

                // Try moving right
                if (j + 1 < n) {
                    int dest = resolve(i, j + 1, 0);

                    if (dest != -1) {
                        int x = dest / n;
                        int y = dest % n;

                        dp[x][y] =
                            (dp[x][y] + dp[i][j]) % MOD;
                    }
                }

                // Try moving down
                if (i + 1 < m) {
                    int dest = resolve(i + 1, j, 1);

                    if (dest != -1) {
                        int x = dest / n;
                        int y = dest % n;

                        dp[x][y] =
                            (dp[x][y] + dp[i][j]) % MOD;
                    }
                }
            }
        }

        return dp[m - 1][n - 1];
    }
};