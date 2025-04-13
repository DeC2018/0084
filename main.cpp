#include <iostream>
#include <vector>
#include <stack>

using namespace std;

class Solution {
public:
    int largestRectangleArea(vector<int>& heights) {
        int maxArea = 0;
        heights.push_back(0); // Add a sentinel value to ensure all bars are processed
        vector<int> indexStack; // Stack to store indices of the bars

        for (int i = 0; i < heights.size(); i++) {
            // Process bars in the stack while the current bar is shorter
            while (!indexStack.empty() && heights[indexStack.back()] >= heights[i]) {
                int height = heights[indexStack.back()];
                indexStack.pop_back();

                int width = indexStack.empty() ? i : i - indexStack.back() - 1;
                maxArea = max(maxArea, height * width);
            }
            indexStack.push_back(i);
        }

        return maxArea;
    }
};

int main() {
    Solution solution;

    // Example 1
    vector<int> heights1 = {2, 1, 5, 6, 2, 3};
    cout << "Input: heights = [2,1,5,6,2,3]" << endl;
    cout << "Output: " << solution.largestRectangleArea(heights1) << endl;

    // Example 2
    vector<int> heights2 = {2, 4};
    cout << "Input: heights = [2,4]" << endl;
    cout << "Output: " << solution.largestRectangleArea(heights2) << endl;

    return 0;
}
