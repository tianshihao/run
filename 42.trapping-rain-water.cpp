/*
 * @lc app=leetcode.cn id=42 lang=cpp
 *
 * [42] Trapping Rain Water
 *
 * https://leetcode.cn/problems/trapping-rain-water/description/
 *
 * algorithms
 * Hard (61.74%)
 * Likes:    3679
 * Dislikes: 0
 * Total Accepted:    545.3K
 * Total Submissions: 883K
 * Testcase Example:  '[0,1,0,2,1,0,1,3,2,1,2,1]'
 *
 * Given n non-negative integers representing an elevation map where the width
 * of each bar is 1, compute how much water it can trap after raining.
 *
 *
 * Example 1:
 *
 *
 * Input: height = [0,1,0,2,1,0,1,3,2,1,2,1]
 * Output: 6
 * Explanation: The above elevation map (black section) is represented by array
 * [0,1,0,2,1,0,1,3,2,1,2,1]. In this case, 6 units of rain water (blue
 * section) are being trapped.
 *
 *
 * Example 2:
 *
 *
 * Input: height = [4,2,0,3,2,5]
 * Output: 9
 *
 *
 *
 * Constraints:
 *
 *
 * n == height.length
 * 1 <= n <= 2 * 10^4
 * 0 <= height[i] <= 10^5
 *
 *
 */

// @lc code=start
#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  int trap(vector<int>& height) {
    // return dp(height);
    return doublepointer(height);
  }

  int dp(const vector<int>& height) {
    auto height_size{static_cast<int>(height.size())};
    if (0 == height_size) {
      return 0;
    }

    vector<int> max_height_of_left_boundary(height_size, height[0]);
    for (auto i{1}; i < height_size; ++i) {
      max_height_of_left_boundary[i] =
          max(height[i], max_height_of_left_boundary[i - 1]);
    }

    vector<int> max_height_of_right_boundary(height_size,
                                             height[height_size - 1]);
    for (auto i{height_size - 2}; i >= 0; --i) {
      max_height_of_right_boundary[i] =
          max(height[i], max_height_of_right_boundary[i + 1]);
    }

    int answer{0};
    for (auto i{0}; i < height_size; ++i) {
      answer +=
          min(max_height_of_left_boundary[i], max_height_of_right_boundary[i]) -
          height[i];
    }

    return answer;
  }

  int doublepointer(const vector<int> height) {
    int height_size{static_cast<int>(height.size())};
    // Double pointer.
    int left{0}, right{height_size - 1};
    // Max height of left and right boundaries.
    int max_height_of_left_boundary{height[0]},
        max_height_of_right_boundary{height[height_size - 1]};
    int answer{0};

    // Calculate the answer of left pointer and right pointer in turn.
    while (left < right) {
      // Update max left boundary height of left pointer, and right pointer is
      // similar.
      max_height_of_left_boundary =
          max(max_height_of_left_boundary, height[left]);
      max_height_of_right_boundary =
          max(max_height_of_right_boundary, height[right]);

      // The height of the trapped rain is detemined by the minimum height
      // between left and right.
      if (height[left] < height[right]) {
        answer += max_height_of_left_boundary - height[left];
        ++left;
      } else {
        answer += max_height_of_right_boundary - height[right];
        --right;
      }
    }

    return answer;
  }
};

// int main(int argc, char** argv) {
//   vector<int> height{0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1};

//   Solution s;
//   s.trap(height);

//   return 0;
// }

// @lc code=end
