/*
 * @lc app=leetcode.cn id=529 lang=cpp
 *
 * [529] Minesweeper
 *
 * https://leetcode.cn/problems/minesweeper/description/
 *
 * algorithms
 * Medium (64.29%)

 * Likes:    305
 * Dislikes: 0
 * Total Accepted:    46.6K
 * Total Submissions: 72.4K
 * Testcase Example:
 '[["E","E","E","E","E"],["E","E","M","E","E"],["E","E","E","E","E"],["E","E","E","E","E"]]\n'
 +
  '[3,0]'
 *
 * Let's play the minesweeper game (Wikipedia, online game)!
 *
 * You are given an m x n char matrix board representing the game board
 * where:
 *
 *
 * 'M' represents an unrevealed mine,
 * 'E' represents an unrevealed empty square,
 * 'B' represents a revealed blank square that has no adjacent mines (i.e.,
 * above, below, left, right, and all 4 diagonals),
 * digit ('1' to '8') represents how many mines are adjacent to this revealed
 * square, and
 * 'X' represents a revealed mine.
 *
 *
 * You are also given an integer array click where click = [clickr, clickc]
 * represents the next click position among all the unrevealed squares ('M' or
 * 'E').
 *
 * Return the board after revealing this position according to the following
 * rules:
 *
 *
 * If a mine 'M' is revealed, then the game is over. You should change it to
 * 'X'.
 * If an empty square 'E' with no adjacent mines is revealed, then change it to
 * a revealed blank 'B' and all of its adjacent unrevealed squares should be
 * revealed recursively.
 * If an empty square 'E' with at least one adjacent mine is revealed, then
 * change it to a digit ('1' to '8') representing the number of adjacent
 * mines.
 * Return the board when no more squares will be revealed.
 *
 *
 *
 * Example 1:
 *
 *
 * Input: board =
 * [["E","E","E","E","E"],["E","E","M","E","E"],["E","E","E","E","E"],["E","E","E","E","E"]],
 * click = [3,0]
 * Output:
 * [["B","1","E","1","B"],["B","1","M","1","B"],["B","1","1","1","B"],["B","B","B","B","B"]]
 *
 *
 * Example 2:
 *
 *
 * Input: board =
 * [["B","1","E","1","B"],["B","1","M","1","B"],["B","1","1","1","B"],["B","B","B","B","B"]],
 * click = [1,2]
 * Output:
 * [["B","1","E","1","B"],["B","1","X","1","B"],["B","1","1","1","B"],["B","B","B","B","B"]]
 *
 *
 *
 * Constraints:
 *
 *
 * m == board.length
 * n == board[i].length
 * 1 <= m, n <= 50
 * board[i][j] is either 'M', 'E', 'B', or a digit from '1' to '8'.
 * click.length == 2
 * 0 <= clickr < m
 * 0 <= clickc < n
 * board[clickr][clickc] is either 'M' or 'E'.
 *
 *
 */

// @lc code=start
#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  vector<vector<char>> updateBoard(vector<vector<char>>& board,
                                   vector<int>& click) {
    return updateBoardBFS(board, click);
  }

  vector<vector<char>> updateBoardBFS(vector<vector<char>>& board,
                                      const vector<int>& click) {
    // Hit the bull's eye.

    const pair<int, int> click_cell{click[0], click[1]};
    if ('M' == board[click_cell.first][click_cell.second]) {
      board[click_cell.first][click_cell.second] = 'X';
      return board;
    }

    // BFS.

    queue<pair<int, int>> cell_queue{};
    cell_queue.emplace(click_cell);

    vector<vector<bool>> visited_board(
        static_cast<size_t>(board.size()),
        vector<bool>(static_cast<size_t>(board[0].size()), false));
    visited_board[click_cell.first][click_cell.second] = true;

    const array<pair<int, int>, 8> directions{
        pair<int, int>{-1, 0}, pair<int, int>{1, 0},   pair<int, int>{0, -1},
        pair<int, int>{0, 1},  pair<int, int>{-1, -1}, pair<int, int>{-1, 1},
        pair<int, int>{1, -1}, pair<int, int>{1, 1}};

    while (false == cell_queue.empty()) {
      const auto cell{cell_queue.front()};
      cell_queue.pop();

      // Traverse neighbors.

      int neighbor_mine_cnt{0};
      vector<pair<int, int>> valid_neighbor_cells{};
      for (const auto& direction : directions) {
        const pair<int, int> neighbor_cell{cell.first + direction.first,
                                           cell.second + direction.second};
        if (true == isValidCell(board, neighbor_cell)) {
          valid_neighbor_cells.emplace_back(neighbor_cell);
          if ('M' == board[neighbor_cell.first][neighbor_cell.second]) {
            ++neighbor_mine_cnt;
          } else {
            continue;
          }
        }
      }

      if (0 == neighbor_mine_cnt) {
        board[cell.first][cell.second] = 'B';

        // Extend.
        for (const auto& valid_neighbor_cell : valid_neighbor_cells) {
          if (true == visited_board[valid_neighbor_cell.first]
                                   [valid_neighbor_cell.second]) {
            continue;
          }

          cell_queue.emplace(valid_neighbor_cell);
          visited_board[valid_neighbor_cell.first][valid_neighbor_cell.second] =
              true;
        }
      } else {
        board[cell.first][cell.second] = neighbor_mine_cnt + '0';
      }
    }

    return board;
  }

  bool isValidCell(const vector<vector<char>>& board,
                   const pair<int, int>& click) {
    if (click.first >= 0 && click.first < board.size() && click.second >= 0 &&
        click.second < board[0].size()) {
      return true;
    } else {
      return false;
    }
  }
};
// @lc code=end
