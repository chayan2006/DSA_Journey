class Solution {
    typedef long long ll;
    static const ll MOD = 1e9 + 7;
    vector<ll> sum, sq, lz;

    void apply(int node, int len, ll v) {
        sq[node] += 2 * v * sum[node] + v * v * len;
        sum[node] += v * len;
        lz[node] += v;
    }
    void push(int node, int l, int r) {
        if (lz[node]) {
            int mid = (l + r) / 2;
            apply(2 * node, mid - l + 1, lz[node]);
            apply(2 * node + 1, r - mid, lz[node]);
            lz[node] = 0;
        }
    }
    void update(int node, int l, int r, int ql, int qr) {
        if (qr < l || r < ql) return;
        if (ql <= l && r <= qr) {
            apply(node, r - l + 1, 1);
            return;
        }
        push(node, l, r);
        int mid = (l + r) / 2;
        update(2 * node, l, mid, ql, qr);
        update(2 * node + 1, mid + 1, r, ql, qr);
        sum[node] = sum[2 * node] + sum[2 * node + 1];
        sq[node] = sq[2 * node] + sq[2 * node + 1];
    }

public:
    int sumCounts(vector<int>& nums) {
        int n = nums.size();
        sum.assign(4 * n, 0);
        sq.assign(4 * n, 0);
        lz.assign(4 * n, 0);

        unordered_map<int, int> last;
        ll ans = 0;
        for (int j = 0; j < n; j++) {
            int prev = last.count(nums[j]) ? last[nums[j]] : -1;
            update(1, 0, n - 1, prev + 1, j);
            ans = (ans + sq[1]) % MOD;
            last[nums[j]] = j;
        }
        return ans;
    }
};