class Solution {
    typedef long long ll;
    static const ll MOD = 1e9 + 7;
    vector<vector<ll>> C;

    ll ways(const vector<int>& v) {
        if (v.size() <= 2) return 1;
        vector<int> L, R;
        for (size_t i = 1; i < v.size(); i++)
            (v[i] < v[0] ? L : R).push_back(v[i]);
        ll res = C[L.size() + R.size()][L.size()];
        res = res * ways(L) % MOD;
        res = res * ways(R) % MOD;
        return res;
    }

public:
    int numOfWays(vector<int>& nums) {
        int n = nums.size();
        C.assign(n + 1, vector<ll>(n + 1, 0));
        for (int i = 0; i <= n; i++) {
            C[i][0] = 1;
            for (int j = 1; j <= i; j++)
                C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % MOD;
        }
        return (ways(nums) - 1 + MOD) % MOD;
    }
};