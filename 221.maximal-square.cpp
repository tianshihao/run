/*
 * @lc app=leetcode.cn id=221 lang=cpp
 *
 * [221] Maximal Square
 *
 * https://leetcode.cn/problems/maximal-square/description/
 *
 * algorithms
 * Medium (49.13%)
 * Likes:    1228
 * Dislikes: 0
 * Total Accepted:    218.9K
 * Total Submissions: 445.6K
 * Testcase Example:
 * '[["1","0","1","0","0"],["1","0","1","1","1"],["1","1","1","1","1"],["1","0","0","1","0"]]'
 *
 * Given an m x n binary matrix filled with 0's and 1's, find the largest
 * square containing only 1's and return its area.
 *
 *
 * Example 1:
 *
 *
 * Input: matrix =
 * [["1","0","1","0","0"],["1","0","1","1","1"],["1","1","1","1","1"],["1","0","0","1","0"]]
 * Output: 4
 *
 *
 * Example 2:
 *
 *
 * Input: matrix = [["0","1"],["1","0"]]
 * Output: 1
 *
 *
 * Example 3:
 *
 *
 * Input: matrix = [["0"]]
 * Output: 0
 *
 *
 *
 * Constraints:
 *
 *
 * m == matrix.length
 * n == matrix[i].length
 * 1 <= m, n <= 300
 * matrix[i][j] is '0' or '1'.
 *
 *
 */

// @lc code=start
#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  int maximalSquare(vector<vector<char>>& matrix) {
    return maximalSquareDP(matrix);
  }

  int maximalSquareDP(vector<vector<char>>& matrix) {
    size_t row_size{matrix.size()}, column_size{matrix[0].size()};
    vector<vector<int>> dp(row_size, vector<int>(column_size, matrix[0][0]));
    int size{0};

    for (size_t row{static_cast<size_t>(0)}; row < row_size; ++row) {
      for (size_t column{static_cast<size_t>(0)}; column < column_size;
           ++column) {
        if (0 == row || 0 == column || '0' == matrix[row][column]) {
          dp[row][column] = matrix[row][column] - '0';
        } else {
          dp[row][column] = min(dp[row - 1][column - 1],
                                min(dp[row - 1][column], dp[row][column - 1])) +
                            1;
        }
        size = max(size, dp[row][column]);
      }
    }

    return size * size;
  };
};
// @lc code=end
