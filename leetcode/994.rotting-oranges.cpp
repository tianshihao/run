/*
 * @lc app=leetcode.cn id=994 lang=cpp
 *
 * [994] Rotting Oranges
 *
 * https://leetcode.cn/problems/rotting-oranges/description/
 *
 * algorithms
 * Medium (51.05%)
 * Likes:    585
 * Dislikes: 0
 * Total Accepted:    91K
 * Total Submissions: 178.3K
 * Testcase Example:  '[[2,1,1],[1,1,0],[0,1,1]]'
 *
 * You are given an m x n grid where each cell can have one of three
 * values:
 *
 *
 * 0 representing an empty cell,
 * 1 representing a fresh orange, or
 * 2 representing a rotten orange.
 *
 *
 * Every minute, any fresh orange that is 4-directionally adjacent to a rotten
 * orange becomes rotten.
 *
 * Return the minimum number of minutes that must elapse until no cell has a
 * fresh orange. If this is impossible, return -1.
 *
 *
 * Example 1:
 *
 *
 * Input: grid = [[2,1,1],[1,1,0],[0,1,1]]
 * Output: 4
 *
 *
 * Example 2:
 *
 *
 * Input: grid = [[2,1,1],[0,1,1],[1,0,1]]
 * Output: -1
 * Explanation: The orange in the bottom left corner (row 2, column 0) is never
 * rotten, because rotting only happens 4-directionally.
 *
 *
 * Example 3:
 *
 *
 * Input: grid = [[0,2]]
 * Output: 0
 * Explanation: Since there are already no fresh oranges at minute 0, the
 * answer is just 0.
 *
 *
 *
 * Constraints:
 *
 *
 * m == grid.length
 * n == grid[i].length
 * 1 <= m, n <= 10
 * grid[i][j] is 0, 1, or 2.
 *
 *
 */

// @lc code=start
#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  int orangesRotting(vector<vector<int>>& grid) {
    return orangesRottingBFS(grid);
  }

  int orangesRottingBFS(vector<vector<int>>& grid) {
    // Special case.
    if (true == grid.empty()) {
      return 0;
    }

    int minute{0};

    // Init.

    queue<pair<int, int>> cell_queue{};
    int fresh_orange_cnt{0};
    for (int row{0}; row < grid.size(); ++row) {
      for (int column{0}; column < grid[0].size(); ++column) {
        if (2 == grid[row][column]) {
          cell_queue.emplace(row, column);
        } else if (1 == grid[row][column]) {
          ++fresh_orange_cnt;
        } else {
          continue;
        }
      }
    }

    // BFS.

    array<pair<int, int>, 4> directions{
        pair<int, int>{-1, 0}, pair<int, int>{1, 0}, pair<int, int>{0, -1},
        pair<int, int>{0, 1}};

    while (false == cell_queue.empty() && fresh_orange_cnt != 0) {
      auto rotten_orange_cnt{cell_queue.size()};

      while (rotten_orange_cnt--) {
        auto cell{cell_queue.front()};
        cell_queue.pop();

        for (auto direction : directions) {
          pair<int, int> neighbor_cell{cell.first + direction.first,
                                       cell.second + direction.second};
          if (isValidCell(grid, neighbor_cell) &&
              1 == grid[neighbor_cell.first][neighbor_cell.second]) {
            grid[neighbor_cell.first][neighbor_cell.second] = 2;
            --fresh_orange_cnt;
            cell_queue.emplace(neighbor_cell);
          }
        }
      }

      // Another minute passed.
      ++minute;
    }

    if (0 == fresh_orange_cnt) {
      return minute;
    } else {
      return -1;
    }
  }

  bool isValidCell(vector<vector<int>>& grid, pair<int, int>& cell) {
    if (cell.first >= 0 && cell.first < grid.size() && cell.second >= 0 &&
        cell.second < grid[0].size()) {
      return true;
    } else {
      return false;
    }
  }
};
// @lc code=end
