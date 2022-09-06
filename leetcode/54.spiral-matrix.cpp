/*
 * @lc app=leetcode.cn id=54 lang=cpp
 *
 * [54] Spiral Matrix
 *
 * https://leetcode.cn/problems/spiral-matrix/description/
 *
 * algorithms
 * Medium (48.98%)
 * Likes:    1156
 * Dislikes: 0
 * Total Accepted:    288.2K
 * Total Submissions: 588.4K
 * Testcase Example:  '[[1,2,3],[4,5,6],[7,8,9]]'
 *
 * Given an m x n matrix, return all elements of the matrix in spiral order.
 *
 *
 * Example 1:
 *
 *
 * Input: matrix = [[1,2,3],[4,5,6],[7,8,9]]
 * Output: [1,2,3,6,9,8,7,4,5]
 *
 *
 * Example 2:
 *
 *
 * Input: matrix = [[1,2,3,4],[5,6,7,8],[9,10,11,12]]
 * Output: [1,2,3,4,8,12,11,10,9,5,6,7]
 *
 *
 *
 * Constraints:
 *
 *
 * m == matrix.length
 * n == matrix[i].length
 * 1 <= m, n <= 10
 * -100 <= matrix[i][j] <= 100
 *
 *
 */

// @lc code=start
#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  vector<int> spiralOrder(vector<vector<int>>& matrix) {
    return printSpiralOrder(matrix);
  }

  vector<int> printSpiralOrder(vector<vector<int>>& matrix) {
    vector<int> result{};
    int column_number{static_cast<int>(matrix[0].size())};
    int row_number{static_cast<int>(matrix.size())};
    int start{0};
    while (start * 2 < column_number && start * 2 < row_number) {
      printSpiralOrderRecursively(matrix, start++, result);
    }

    return result;
  }

  void printSpiralOrderRecursively(vector<vector<int>>& matrix, int start,
                                   vector<int>& result) {
    int end_column{static_cast<int>(matrix[0].size() - start - 1)};
    int end_row{static_cast<int>(matrix.size() - start - 1)};

    // left to right.
    for (int column{start}; column <= end_column; ++column) {
      result.emplace_back(matrix[start][column]);
    }

    // top to bottom.
    for (int row{start + 1}; row <= end_row; ++row) {
      result.emplace_back(matrix[row][end_column]);
    }

    // right to left.
    // end_row > start, make sure it won't go back.
    for (int column{end_column - 1}; column >= start && end_row > start;
         --column) {
      result.emplace_back(matrix[end_row][column]);
    }

    // bottom to top.
    for (int row{end_row - 1}; row >= start + 1 && end_column > start; --row) {
      result.emplace_back(matrix[row][start]);
    }

    return;
  }
};

// @lc code=end
