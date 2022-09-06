/*
 * @lc app=leetcode.cn id=56 lang=cpp
 *
 * [56] Merge Intervals
 *
 * https://leetcode.cn/problems/merge-intervals/description/
 *
 * algorithms
 * Medium (48.91%)
 * Likes:    1575
 * Dislikes: 0
 * Total Accepted:    493.8K
 * Total Submissions: 1M
 * Testcase Example:  '[[1,3],[2,6],[8,10],[15,18]]'
 *
 * Given an array of intervals where intervals[i] = [starti, endi], merge all
 * overlapping intervals, and return an array of the non-overlapping intervals
 * that cover all the intervals in the input.
 *
 *
 * Example 1:
 *
 *
 * Input: intervals = [[1,3],[2,6],[8,10],[15,18]]
 * Output: [[1,6],[8,10],[15,18]]
 * Explanation: Since intervals [1,3] and [2,6] overlap, merge them into
 * [1,6].
 *
 *
 * Example 2:
 *
 *
 * Input: intervals = [[1,4],[4,5]]
 * Output: [[1,5]]
 * Explanation: Intervals [1,4] and [4,5] are considered overlapping.
 *
 *
 *
 * Constraints:
 *
 *
 * 1 <= intervals.length <= 10^4
 * intervals[i].length == 2
 * 0 <= starti <= endi <= 10^4
 *
 *
 */

// @lc code=start
#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  vector<vector<int>> merge(vector<vector<int>>& intervals) {
    sort(intervals.begin(), intervals.end());

    vector<vector<int>> result;
    result.emplace_back(intervals[0]);

    for (auto interval : intervals) {
      if (result.back()[1] >= interval[0]) {
        result.back()[1] = max(result.back()[1], interval[1]);
      } else {
        result.emplace_back(interval);
      }
    }

    return result;
  }
};
// @lc code=end
