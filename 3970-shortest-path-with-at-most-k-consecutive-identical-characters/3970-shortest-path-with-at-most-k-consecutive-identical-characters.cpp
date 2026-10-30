
class Solution {
public:
    int shortestPath(int n, vector<vector<int>>& edges, string labels, int k) {
        vector<vector<pair<int, int>>> adj(n);

        for (const auto& e : edges) {
            adj[e[0]].push_back({e[1], e[2]});
        }

        if (n == 1) return 0;
        if (k <= 0) return -1;

        using State = tuple<long long, int, int>;
        // State: {distance, node, run length}

        priority_queue<State, vector<State>, greater<State>> pq;

        // Store distances only for states that are reached.
        unordered_map<long long, long long> dist;
        dist.reserve(n * 2);

        auto encode = [&](int node, int run) -> long long {
            return 1LL * node * (k + 1) + run;
        };

        int startRun = 1;
        dist[encode(0, startRun)] = 0;
        pq.push({0, 0, startRun});

        while (!pq.empty()) {
            auto [d, u, run] = pq.top();
            pq.pop();

            long long key = encode(u, run);

            auto it = dist.find(key);
            if (it == dist.end() || it->second != d) continue;

            if (u == n - 1) {
                return static_cast<int>(d);
            }

            for (auto [v, w] : adj[u]) {
                int nextRun = (labels[u] == labels[v]) ? run + 1 : 1;

                if (nextRun > k) continue;

                long long nextKey = encode(v, nextRun);
                long long nd = d + w;

                auto jt = dist.find(nextKey);

                if (jt == dist.end() || nd < jt->second) {
                    dist[nextKey] = nd;
                    pq.push({nd, v, nextRun});
                }
            }
        }

        return -1;
    }
};
