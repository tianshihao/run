/*
 * @lc app=leetcode.cn id=64 lang=cpp
 *
 * [64] Minimum Path Sum
 *
 * https://leetcode.cn/problems/minimum-path-sum/description/
 *
 * algorithms
 * Medium (69.32%)
 * Likes:    1314
 * Dislikes: 0
 * Total Accepted:    399.4K
 * Total Submissions: 576.2K
 * Testcase Example:  '[[1,3,1],[1,5,1],[4,2,1]]'
 *
 * Given a m x n grid filled with non-negative numbers, find a path from top
 * left to bottom right, which minimizes the sum of all numbers along its
 * path.
 *
 * Note: You can only move either down or right at any point in time.
 *
 *
 * Example 1:
 *
 *
 * Input: grid = [[1,3,1],[1,5,1],[4,2,1]]
 * Output: 7
 * Explanation: Because the path 1 → 3 → 1 → 1 → 1 minimizes the sum.
 *
 *
 * Example 2:
 *
 *
 * Input: grid = [[1,2,3],[4,5,6]]
 * Output: 12
 *
 *
 *
 * Constraints:
 *
 *
 * m == grid.length
 * n == grid[i].length
 * 1 <= m, n <= 200
 * 0 <= grid[i][j] <= 100
 *
 *
 */

// @lc code=start
#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  int minPathSum(vector<vector<int>>& grid) { return minPathSumDP(grid); }

  int minPathSumDP(vector<vector<int>>& grid) {
    size_t row_size{grid.size()}, column_size{grid[0].size()};
    vector<vector<int>> dp(row_size, vector<int>(column_size, grid[0][0]));

    // init
    for (size_t row{static_cast<size_t>(1)}; row < row_size; ++row) {
      dp[row][0] = dp[row - 1][0] + grid[row][0];
    }
    for (size_t column{static_cast<size_t>(1)}; column < column_size;
         ++column) {
      dp[0][column] = dp[0][column - 1] + grid[0][column];
    }

    // dp
    for (size_t row{static_cast<size_t>(1)}; row < row_size; ++row) {
      for (size_t column{static_cast<size_t>(1)}; column < column_size;
           ++column) {
        dp[row][column] =
            min(dp[row - 1][column], dp[row][column - 1]) + grid[row][column];
      }
    }

    return dp[row_size - 1][column_size - 1];
  }
};
// @lc code=end
