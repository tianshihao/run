/*
 * @lc app=leetcode.cn id=35 lang=cpp
 *
 * [35] Search Insert Position
 *
 * https://leetcode.cn/problems/search-insert-position/description/
 *
 * algorithms
 * Easy (45.18%)
 * Likes:    1627
 * Dislikes: 0
 * Total Accepted:    869.4K
 * Total Submissions: 1.9M
 * Testcase Example:  '[1,3,5,6]\n5'
 *
 * Given a sorted array of distinct integers and a target value, return the
 * index if the target is found. If not, return the index where it would be if
 * it were inserted in order.
 *
 * You must write an algorithm with O(log n) runtime complexity.
 *
 *
 * Example 1:
 *
 *
 * Input: nums = [1,3,5,6], target = 5
 * Output: 2
 *
 *
 * Example 2:
 *
 *
 * Input: nums = [1,3,5,6], target = 2
 * Output: 1
 *
 *
 * Example 3:
 *
 *
 * Input: nums = [1,3,5,6], target = 7
 * Output: 4
 *
 *
 *
 * Constraints:
 *
 *
 * 1 <= nums.length <= 10^4
 * -10^4 <= nums[i] <= 10^4
 * nums contains distinct values sorted in ascending order.
 * -10^4 <= target <= 10^4
 *
 *
 */

// @lc code=start
#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  int searchInsert(vector<int>& nums, int target) {
    if (target <= nums[0]) {
      return 0;
    }
    if (target > nums[nums.size() - 1]) {
      return nums.size();
    }

    size_t i{0};
    for (; i < nums.size(); ++i) {
      if (target > nums[i] && target <= nums[i + 1]) {
        break;
      }
    }

    return static_cast<int>(i + 1);
  }
};
// @lc code=end
