/*
 * @lc app=leetcode.cn id=78 lang=cpp
 *
 * [78] Subsets
 *
 * https://leetcode.cn/problems/subsets/description/
 *
 * algorithms
 * Medium (80.70%)
 * Likes:    1724
 * Dislikes: 0
 * Total Accepted:    492.2K
 * Total Submissions: 609.9K
 * Testcase Example:  '[1,2,3]'
 *
 * Given an integer array nums of unique elements, return all possible subsets
 * (the power set).
 *
 * The solution set must not contain duplicate subsets. Return the solution in
 * any order.
 *
 *
 * Example 1:
 *
 *
 * Input: nums = [1,2,3]
 * Output: [[],[1],[2],[1,2],[3],[1,3],[2,3],[1,2,3]]
 *
 *
 * Example 2:
 *
 *
 * Input: nums = [0]
 * Output: [[],[0]]
 *
 *
 *
 * Constraints:
 *
 *
 * 1 <= nums.length <= 10
 * -10 <= nums[i] <= 10
 * All the numbers of nums are unique.
 *
 *
 */

// @lc code=start
#include <bits/stdc++.h>
using namespace std;

class Solution {
 private:
  vector<vector<int>> result{};
  vector<int> sub{};

 public:
  vector<vector<int>> subsets(vector<int>& nums) {
    backtracking(nums, 0, nums.size() - 1);
    return result;
  }

  void backtracking(vector<int>& nums, int cur_depth, int max_depth) {
    result.push_back(sub);

    for (int depth = cur_depth; depth <= max_depth; ++depth) {
      sub.push_back(nums[depth]);
      backtracking(nums, depth + 1, max_depth);
      sub.pop_back();
    }

    return;
  }
};
// @lc code=end
