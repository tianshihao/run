/*
 * @lc app=leetcode.cn id=20 lang=cpp
 *
 * [20] Valid Parentheses
 *
 * https://leetcode.cn/problems/valid-parentheses/description/
 *
 * algorithms
 * Easy (44.63%)
 * Likes:    3393
 * Dislikes: 0
 * Total Accepted:    1.2M
 * Total Submissions: 2.6M
 * Testcase Example:  '"()"'
 *
 * Given a string s containing just the characters '(', ')', '{', '}', '[' and
 * ']', determine if the input string is valid.
 *
 * An input string is valid if:
 *
 *
 * Open brackets must be closed by the same type of brackets.
 * Open brackets must be closed in the correct order.
 *
 *
 *
 * Example 1:
 *
 *
 * Input: s = "()"
 * Output: true
 *
 *
 * Example 2:
 *
 *
 * Input: s = "()[]{}"
 * Output: true
 *
 *
 * Example 3:
 *
 *
 * Input: s = "(]"
 * Output: false
 *
 *
 *
 * Constraints:
 *
 *
 * 1 <= s.length <= 10^4
 * s consists of parentheses only '()[]{}'.
 *
 *
 */

// @lc code=start
#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  bool isValid(string s) {
    stack<char> stack;

    for (auto const& bracket : s) {
      if (bracket == '(' || bracket == '[' || bracket == '{') {
        stack.push(bracket);
      } else {
        if (stack.empty()) {
          return false;
        } else if (stack.top() != bracket - 1 && stack.top() != bracket - 2) {
          return false;
        } else {
          stack.pop();
        }
      }
    }
    if (stack.size() > 0) {
      return false;
    } else {
      return true;
    }
  }
};
// @lc code=end
