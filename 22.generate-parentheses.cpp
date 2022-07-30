/*
 * @lc app=leetcode.cn id=22 lang=cpp
 *
 * [22] Generate Parentheses
 *
 * https://leetcode.cn/problems/generate-parentheses/description/
 *
 * algorithms
 * Medium (77.50%)
 * Likes:    2783
 * Dislikes: 0
 * Total Accepted:    556K
 * Total Submissions: 717.4K
 * Testcase Example:  '3'
 *
 * Given n pairs of parentheses, write a function to generate all combinations
 * of well-formed parentheses.
 *
 *
 * Example 1:
 * Input: n = 3
 * Output: ["((()))","(()())","(())()","()(())","()()()"]
 * Example 2:
 * Input: n = 1
 * Output: ["()"]
 *
 *
 * Constraints:
 *
 *
 * 1 <= n <= 8
 *
 *
 */

// @lc code=start
#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  vector<string> result;

  vector<string> generateParenthesis(int n) {
    backtracking(0, 0, n, "");
    return result;
  }

  void backtracking(int open, int close, int n, string cur) {
    if (cur.size() == 2 * n) {
      result.push_back(cur);
      return;
    }
    if (open < n) {
      backtracking(open + 1, close, n, cur + "(");
    }
    if (close < open) {
      backtracking(open, close + 1, n, cur + ")");
    }
  }
};
// @lc code=end
