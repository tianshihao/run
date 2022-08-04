/*
 * @lc app=leetcode.cn id=39 lang=cpp
 *
 * [39] Combination Sum
 *
 * https://leetcode.cn/problems/combination-sum/description/
 *
 * algorithms
 * Medium (72.69%)
 * Likes:    2086
 * Dislikes: 0
 * Total Accepted:    565.6K
 * Total Submissions: 778.2K
 * Testcase Example:  '[2,3,6,7]\n7'
 *
 * Given an array of distinct integers candidates and a target integer target,
 * return a list of all unique combinations of candidates where the chosen
 * numbers sum to target. You may return the combinations in any order.
 *
 * The same number may be chosen from candidates an unlimited number of times.
 * Two combinations are unique if the frequency of at least one of the chosen
 * numbers is different.
 *
 * It is guaranteed that the number of unique combinations that sum up to
 * target is less than 150 combinations for the given input.
 *
 *
 * Example 1:
 *
 *
 * Input: candidates = [2,3,6,7], target = 7
 * Output: [[2,2,3],[7]]
 * Explanation:
 * 2 and 3 are candidates, and 2 + 2 + 3 = 7. Note that 2 can be used multiple
 * times.
 * 7 is a candidate, and 7 = 7.
 * These are the only two combinations.
 *
 *
 * Example 2:
 *
 *
 * Input: candidates = [2,3,5], target = 8
 * Output: [[2,2,2,2],[2,3,3],[3,5]]
 *
 *
 * Example 3:
 *
 *
 * Input: candidates = [2], target = 1
 * Output: []
 *
 *
 *
 * Constraints:
 *
 *
 * 1 <= candidates.length <= 30
 * 1 <= candidates[i] <= 200
 * All elements of candidates are distinct.
 * 1 <= target <= 500
 *
 *
 */

// @lc code=start
#include <bits/stdc++.h>
using namespace std;

class Solution {
 private:
  vector<vector<int>> result{};
  vector<int> combination{};

 public:
  vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
    sort(candidates.begin(), candidates.end());
    backtracking(candidates, 0, target);
    return result;
  }

  void backtracking(vector<int>& candidates, int cur_depth, int remains) {
    if (0 == remains) {
      result.emplace_back(combination);
      return;
    }

    for (auto depth{cur_depth}; depth < candidates.size(); ++depth) {
      if (candidates[depth] > remains) {
        return;
      }

      if (depth > 0 && candidates[depth] == candidates[depth - 1]) {
        continue;
      }

      combination.emplace_back(candidates[depth]);
      backtracking(candidates, depth, remains - candidates[depth]);
      combination.pop_back();
    }

    return;
  }

  int sum(vector<int> nums) {
    return accumulate(nums.begin(), nums.end(), decltype(nums)::value_type(0));
  }
};
// @lc code=end
