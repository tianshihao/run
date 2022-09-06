/*
 * @lc app=leetcode.cn id=47 lang=cpp
 *
 * [47] Permutations II
 *
 * https://leetcode.cn/problems/permutations-ii/description/
 *
 * algorithms
 * Medium (65.00%)
 * Likes:    1145
 * Dislikes: 0
 * Total Accepted:    352.9K
 * Total Submissions: 543K
 * Testcase Example:  '[1,1,2]'
 *
 * Given a collection of numbers, nums, that might contain duplicates, return
 * all possible unique permutations in any order.
 *
 *
 * Example 1:
 *
 *
 * Input: nums = [1,1,2]
 * Output:
 * [[1,1,2],
 * ⁠[1,2,1],
 * ⁠[2,1,1]]
 *
 *
 * Example 2:
 *
 *
 * Input: nums = [1,2,3]
 * Output: [[1,2,3],[1,3,2],[2,1,3],[2,3,1],[3,1,2],[3,2,1]]
 *
 *
 *
 * Constraints:
 *
 *
 * 1 <= nums.length <= 8
 * -10 <= nums[i] <= 10
 *
 *
 */

// @lc code=start
#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  vector<vector<int>> result{};

  vector<vector<int>> permuteUnique(vector<int>& nums) {
    sort(nums.begin(), nums.end());
    backtracking(nums, 0, nums.size() - 1);
    return result;
  }

  void backtracking(vector<int> nums, int cur_depth, int max_depth) {
    if (cur_depth == max_depth) {
      result.emplace_back(nums);
      return;
    }

    for (int depth{cur_depth}; depth <= max_depth; ++depth) {
      // make sure swap bewteen unique elements.
      if (depth != cur_depth && nums[cur_depth] == nums[depth]) {
        continue;
      }
      swap(nums[cur_depth], nums[depth]);
      backtracking(nums, cur_depth + 1, max_depth);
      // attention!
      // swap(nums[cur_depth], nums[depth]);
    }

    return;
  }
};

// @lc code=end
