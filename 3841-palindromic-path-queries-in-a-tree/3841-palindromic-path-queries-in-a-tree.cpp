class Solution {
public:
    vector<bool> palindromePath(int n, vector<vector<int>>& edges,
                                string s, vector<string>& queries) {
        vector<vector<int>> adj(n);

        for (auto& e : edges) {
            adj[e[0]].push_back(e[1]);
            adj[e[1]].push_back(e[0]);
        }

        int LOG = 1;
        while ((1 << LOG) <= n) LOG++;

        vector<vector<int>> up(LOG, vector<int>(n, 0));
        vector<int> tin(n), tout(n), depth(n);
        vector<int> pref(n, 0);
        vector<int> bit(n + 2, 0);

        int timer = 0;

        function<void(int, int)> dfs = [&](int u, int p) {
            tin[u] = timer++;
            up[0][u] = (p == -1 ? u : p);

            for (int k = 1; k < LOG; k++) {
                up[k][u] = up[k - 1][up[k - 1][u]];
            }

            pref[u] = (p == -1 ? 0 : pref[p]) ^ (1 << (s[u] - 'a'));

            for (int v : adj[u]) {
                if (v == p) continue;
                depth[v] = depth[u] + 1;
                dfs(v, u);
            }

            tout[u] = timer;
        };

        dfs(0, -1);

        auto add = [&](int idx, int val) {
            for (++idx; idx < (int)bit.size(); idx += idx & -idx)
                bit[idx] ^= val;
        };

        auto get = [&](int idx) {
            int res = 0;
            for (++idx; idx > 0; idx -= idx & -idx)
                res ^= bit[idx];
            return res;
        };

        auto updateSubtree = [&](int u, int val) {
            add(tin[u], val);
            add(tout[u], val);
        };

        auto getPrefix = [&](int u) {
            return pref[u] ^ get(tin[u]);
        };

        auto lca = [&](int u, int v) {
            if (depth[u] < depth[v]) swap(u, v);

            int diff = depth[u] - depth[v];

            for (int k = 0; k < LOG; k++) {
                if (diff & (1 << k))
                    u = up[k][u];
            }

            if (u == v) return u;

            for (int k = LOG - 1; k >= 0; k--) {
                if (up[k][u] != up[k][v]) {
                    u = up[k][u];
                    v = up[k][v];
                }
            }

            return up[0][u];
        };

        vector<bool> ans;

        for (string& q : queries) {
            stringstream ss(q);
            string type;
            int u;
            ss >> type >> u;

            if (type == "update") {
                char c;
                ss >> c;

                int newMask = 1 << (c - 'a');
                int oldMask = 1 << (s[u] - 'a');
                int change = oldMask ^ newMask;

                updateSubtree(u, change);
                s[u] = c;
            } else {
                int v;
                ss >> v;

                int w = lca(u, v);

                int pathMask = getPrefix(u) ^ getPrefix(v)
                             ^ (1 << (s[w] - 'a'));

                ans.push_back((pathMask & (pathMask - 1)) == 0);
            }
        }

        return ans;
    }
};