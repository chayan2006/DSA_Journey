class Solution {
    int k, n;
    struct Node {
        int prod;
        int cnt[5];
    };
    vector<Node> t;

    Node ident() {
        Node a;
        a.prod = 1 % k;
        for (int i = 0; i < 5; i++) a.cnt[i] = 0;
        return a;
    }

    Node mergeNode(const Node& L, const Node& R) {
        Node res;
        res.prod = (L.prod * R.prod) % k;
        for (int i = 0; i < 5; i++) res.cnt[i] = L.cnt[i];
        for (int b = 0; b < k; b++) {
            res.cnt[(L.prod * b) % k] += R.cnt[b];
        }
        return res;
    }

    Node leaf(int v) {
        Node a = ident();
        a.prod = v % k;
        a.cnt[v % k] = 1;
        return a;
    }

    void build(int o, int l, int r, vector<int>& a) {
        if (l == r) { t[o] = leaf(a[l]); return; }
        int m = (l + r) / 2;
        build(2 * o, l, m, a);
        build(2 * o + 1, m + 1, r, a);
        t[o] = mergeNode(t[2 * o], t[2 * o + 1]);
    }

    void update(int o, int l, int r, int pos, int v) {
        if (l == r) { t[o] = leaf(v); return; }
        int m = (l + r) / 2;
        if (pos <= m) update(2 * o, l, m, pos, v);
        else update(2 * o + 1, m + 1, r, pos, v);
        t[o] = mergeNode(t[2 * o], t[2 * o + 1]);
    }

    Node query(int o, int l, int r, int ql, int qr) {
        if (ql > r || qr < l) return ident();
        if (ql <= l && r <= qr) return t[o];
        int m = (l + r) / 2;
        return mergeNode(query(2 * o, l, m, ql, qr),
                         query(2 * o + 1, m + 1, r, ql, qr));
    }

public:
    vector<int> resultArray(vector<int>& nums, int k, vector<vector<int>>& queries) {
        this->k = k;
        n = nums.size();
        t.resize(4 * n);
        build(1, 0, n - 1, nums);

        vector<int> result;
        for (auto& q : queries) {
            int index = q[0], value = q[1], start = q[2], x = q[3];
            update(1, 0, n - 1, index, value);
            Node res = query(1, 0, n - 1, start, n - 1);
            result.push_back(res.cnt[x]);
        }
        return result;
    }
};