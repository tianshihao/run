/*
 * @lc app=leetcode.cn id=74 lang=cpp
 *
 * [74] Search a 2D Matrix
 *
 * https://leetcode.cn/problems/search-a-2d-matrix/description/
 *
 * algorithms
 * Medium (47.98%)
 * Likes:    699
 * Dislikes: 0
 * Total Accepted:    259.9K
 * Total Submissions: 541.6K
 * Testcase Example:  '[[1,3,5,7],[10,11,16,20],[23,30,34,60]]\n3'
 *
 * Write an efficient algorithm that searches for a value target in an m x n
 * integer matrix matrix. This matrix has the following properties:
 *
 *
 * Integers in each row are sorted from left to right.
 * The first integer of each row is greater than the last integer of the
 * previous row.
 *
 *
 *
 * Example 1:
 *
 *
 * Input: matrix = [[1,3,5,7],[10,11,16,20],[23,30,34,60]], target = 3
 * Output: true
 *
 *
 * Example 2:
 *
 *
 * Input: matrix = [[1,3,5,7],[10,11,16,20],[23,30,34,60]], target = 13
 * Output: false
 *
 *
 *
 * Constraints:
 *
 *
 * m == matrix.length
 * n == matrix[i].length
 * 1 <= m, n <= 100
 * -10^4 <= matrix[i][j], target <= 10^4
 *
 *
 */

// @lc code=start
#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  bool searchMatrix(vector<vector<int>>& matrix, int target) {
    const int row_size = matrix.size();
    const int column_size = matrix[0].size();
    int start_idx = 0;
    int end_idx = row_size * column_size - 1;

    while (start_idx <= end_idx) {
      const int middle_idx = start_idx + (end_idx - start_idx) / 2;
      const int middle_elem =
          matrix[middle_idx / column_size][middle_idx % column_size];

      if (target == middle_elem) {
        return true;
      } else if (target < middle_elem) {
        end_idx = middle_idx - 1;
      } else {
        start_idx = middle_idx + 1;
      }
    }

    return false;
  }
};
// @lc code=end
