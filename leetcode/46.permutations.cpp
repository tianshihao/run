/*
 * @lc app=leetcode.cn id=46 lang=cpp
 *
 * [46] Permutations
 *
 * https://leetcode.cn/problems/permutations/description/
 *
 * algorithms
 * Medium (78.66%)
 * Likes:    2136
 * Dislikes: 0
 * Total Accepted:    677.6K
 * Total Submissions: 861.5K
 * Testcase Example:  '[1,2,3]'
 *
 * Given an array nums of distinct integers, return all the possible
 * permutations. You can return the answer in any order.
 *
 *
 * Example 1:
 * Input: nums = [1,2,3]
 * Output: [[1,2,3],[1,3,2],[2,1,3],[2,3,1],[3,1,2],[3,2,1]]
 * Example 2:
 * Input: nums = [0,1]
 * Output: [[0,1],[1,0]]
 * Example 3:
 * Input: nums = [1]
 * Output: [[1]]
 *
 *
 * Constraints:
 *
 *
 * 1 <= nums.length <= 6
 * -10 <= nums[i] <= 10
 * All the integers of nums are unique.
 *
 *
 */

// @lc code=start
#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  vector<vector<int>> result{};
  vector<vector<int>> permute(vector<int>& nums) {
    backtracking(nums, 0, nums.size() - 1);

    return result;
  }

  void backtracking(vector<int>& nums, int cur_depth, int max_depth) {
    if (cur_depth == max_depth) {
      result.emplace_back(nums);
      return;
    }

    for (int depth{cur_depth}; depth <= max_depth; ++depth) {
      swap(nums[cur_depth], nums[depth]);
      backtracking(nums, cur_depth + 1, max_depth);
      // nums is a reference, so restore it.
      swap(nums[cur_depth], nums[depth]);
    }

    return;
  }
};
// @lc code=end
