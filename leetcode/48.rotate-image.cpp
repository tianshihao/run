/*
 * @lc app=leetcode.cn id=48 lang=cpp
 *
 * [48] Rotate Image
 *
 * https://leetcode.cn/problems/rotate-image/description/
 *
 * algorithms
 * Medium (74.34%)
 * Likes:    1382
 * Dislikes: 0
 * Total Accepted:    360.2K
 * Total Submissions: 484.5K
 * Testcase Example:  '[[1,2,3],[4,5,6],[7,8,9]]'
 *
 * You are given an n x n 2D matrix representing an image, rotate the image by
 * 90 degrees (clockwise).
 *
 * You have to rotate the image in-place, which means you have to modify the
 * input 2D matrix directly. DO NOT allocate another 2D matrix and do the
 * rotation.
 *
 *
 * Example 1:
 *
 *
 * Input: matrix = [[1,2,3],[4,5,6],[7,8,9]]
 * Output: [[7,4,1],[8,5,2],[9,6,3]]
 *
 * Example 2:
 *
 *
 * Input: matrix = [[5,1,9,11],[2,4,8,10],[13,3,6,7],[15,14,12,16]]
 * Output: [[15,13,2,5],[14,3,4,1],[12,6,8,9],[16,7,10,11]]
 *
 *
 *
 * Constraints:
 *
 *
 * n == matrix.length == matrix[i].length
 * 1 <= n <= 20
 * -1000 <= matrix[i][j] <= 1000
 *
 *
 */

// @lc code=start
#include <bits/stdc++.h>
using namespace std;
/**
 * A
 * [1,2,3]
 * [4,5,6]
 * [7,8,9]
 *
 * Transpose of A
 * [1,4,7]
 * [2,5,8]
 * [3,6,9]
 *
 * Take mirror image of middle vertical line
 * [7,4,1]
 * [8,5,2]
 * [9,6,3]
 * 
 * very elegant
 */
class Solution {
 public:
  void rotate(vector<vector<int>>& matrix) {
    auto n{matrix.size()};

    // get transpose.
    for (size_t row{0}; row < n; ++row) {
      for (size_t column{row}; column < n; ++column) {
        swap(matrix[row][column], matrix[column][row]);
      }
    }

    // take mirror image of middle vertical line
    for (size_t row{0}; row < n; ++row) {
      reverse(matrix[row].begin(), matrix[row].end());
    }

    return;
  }
};
// @lc code=end
