class Solution {
public:
    int sortableIntegers(vector<int>& nums) {
        int n = nums.size();
        int ans = 0;

        for (int k = 1; k <= n; k++) {
            if (n % k != 0)
                continue;

            bool valid = true;

            for (int i = 0; i < n && valid; i += k) {
                int descents = 0;

                for (int j = i; j < i + k - 1; j++) {
                    if (nums[j] > nums[j + 1])
                        descents++;
                }

                if (descents > 1)
                    valid = false;
            }

            if (!valid)
                continue;

            vector<int> arr = nums;

            for (int i = 0; i < n; i += k) {
                int descents = 0, pos = -1;

                for (int j = i; j < i + k - 1; j++) {
                    if (arr[j] > arr[j + 1]) {
                        descents++;
                        pos = j;
                    }
                }

                if (descents == 1) {
                    rotate(arr.begin() + i, arr.begin() + pos + 1,
                           arr.begin() + i + k);
                }

                if (!is_sorted(arr.begin() + i, arr.begin() + i + k)) {
                    valid = false;
                    break;
                }
            }

            if (valid && is_sorted(arr.begin(), arr.end()))
                ans += k;
        }

        return ans;
    }
};