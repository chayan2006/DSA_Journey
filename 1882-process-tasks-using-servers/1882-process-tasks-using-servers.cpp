
class Solution {
public:
    vector<int> assignTasks(vector<int>& servers, vector<int>& tasks) {

        // {weight, serverIndex}
        priority_queue<
            pair<int,int>,
            vector<pair<int,int>>,
            greater<pair<int,int>>
        > available;

        // {freeTime, weight, serverIndex}
        priority_queue<
            tuple<long long,int,int>,
            vector<tuple<long long,int,int>>,
            greater<tuple<long long,int,int>>
        > busy;

        int n = servers.size();
        int m = tasks.size();

        vector<int> ans(m);

        // Initially, all servers are available
        for (int i = 0; i < n; i++) {
            available.push({servers[i], i});
        }

        long long time = 0;

        for (int i = 0; i < m; i++) {

            // Task i arrives at second i
            time = max(time, (long long)i);

            // Release all servers that have finished
            while (!busy.empty() &&
                   get<0>(busy.top()) <= time) {

                auto [freeTime, weight, idx] = busy.top();
                busy.pop();

                available.push({weight, idx});
            }

            // If no server is available, jump to
            // the earliest finishing time
            if (available.empty()) {

                time = get<0>(busy.top());

                while (!busy.empty() &&
                       get<0>(busy.top()) <= time) {

                    auto [freeTime, weight, idx] = busy.top();
                    busy.pop();

                    available.push({weight, idx});
                }
            }

            // Select the best available server
            auto [weight, idx] = available.top();
            available.pop();

            ans[i] = idx;

            // Server becomes free after task completion
            busy.push({
                time + tasks[i],
                weight,
                idx
            });
        }

        return ans;
    }
};
