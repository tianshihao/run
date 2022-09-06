/*
 * @lc app=leetcode.cn id=53 lang=cpp
 *
 * [53] Maximum Subarray
 *
 * https://leetcode.cn/problems/maximum-subarray/description/
 *
 * algorithms
 * Easy (54.77%)
 * Likes:    5118
 * Dislikes: 0
 * Total Accepted:    1.1M
 * Total Submissions: 2M
 * Testcase Example:  '[-2,1,-3,4,-1,2,1,-5,4]'
 *
 * Given an integer array nums, find the contiguous subarray (containing at
 * least one number) which has the largest sum and return its sum.
 *
 * A subarray is a contiguous part of an array.
 *
 *
 * Example 1:
 *
 *
 * Input: nums = [-2,1,-3,4,-1,2,1,-5,4]
 * Output: 6
 * Explanation: [4,-1,2,1] has the largest sum = 6.
 *
 *
 * Example 2:
 *
 *
 * Input: nums = [1]
 * Output: 1
 *
 *
 * Example 3:
 *
 *
 * Input: nums = [5,4,-1,7,8]
 * Output: 23
 *
 *
 *
 * Constraints:
 *
 *
 * 1 <= nums.length <= 10^5
 * -10^4 <= nums[i] <= 10^4
 *
 *
 *
 * Follow up: If you have figured out the O(n) solution, try coding another
 * solution using the divide and conquer approach, which is more subtle.
 *
 */

// @lc code=start
#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  int maxSubArray(vector<int>& nums) {
    // return dp(nums);
    return DivideAndConquer(nums, 0, nums.size() - 1);
  }

  int dp(vector<int> const& nums) {
    int max_sum{numeric_limits<int>::min()};
    int sum{0};
    for (auto num : nums) {
      sum += num;
      max_sum = std::max(max_sum, sum);
      // Reset subarray sum when it is less than 0.
      if (sum < 0) {
        sum = 0;
      }
    }

    return max_sum;
  }

  // Easy, divide into 3 sections. [..., mid - 1], [mid], [mid + 1, ...].

  int DivideAndConquer(vector<int>& nums, int left, int right) {
    if (left > right) {
      return numeric_limits<int>::min();
    }
    int mid{left + (right - left) / 2};
    int mid2left_max{0}, mid2right_max{0};
    int left_max{DivideAndConquer(nums, left, mid - 1)};
    int right_max{DivideAndConquer(nums, mid + 1, right)};

    for (int i{mid - 1}, sum{0}; i >= left; --i) {
      sum += nums[i];
      mid2left_max = std::max(sum, mid2left_max);
    }
    for (int i{mid + 1}, sum{0}; i <= right; ++i) {
      sum += nums[i];
      mid2right_max = std::max(sum, mid2right_max);
    }

    return std::max(std::max(left_max, right_max),
                    mid2left_max + nums[mid] + mid2right_max);
  }
};
// @lc code=end
