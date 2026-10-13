class Solution {
public:
    int maxArea(vector<int>& height) {
        int l = 0, r = height.size() - 1;
        int best = 0;

        while (l < r) {
            int h = min(height[l], height[r]);
            best = max(best, h * (r - l));

            if (height[l] < height[r]) l++;
            else r--;
        }
        return best;
    }
};