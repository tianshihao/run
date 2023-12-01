/*
 * @lc app=leetcode.cn id=9 lang=cpp
 *
 * [9] Palindrome Number
 *
 * https://leetcode.cn/problems/palindrome-number/description/
 *
 * algorithms
 * Easy (55.84%)
 * Likes:    2756
 * Dislikes: 0
 * Total Accepted:    1.5M
 * Total Submissions: 2.7M
 * Testcase Example:  '121'
 *
 * Given an integer x, return true if x is a palindrome, and false
 * otherwise.
 *
 *
 * Example 1:
 *
 *
 * Input: x = 121
 * Output: true
 * Explanation: 121 reads as 121 from left to right and from right to left.
 *
 *
 * Example 2:
 *
 *
 * Input: x = -121
 * Output: false
 * Explanation: From left to right, it reads -121. From right to left, it
 * becomes 121-. Therefore it is not a palindrome.
 *
 *
 * Example 3:
 *
 *
 * Input: x = 10
 * Output: false
 * Explanation: Reads 01 from right to left. Therefore it is not a
 * palindrome.
 *
 *
 *
 * Constraints:
 *
 *
 * -2^31 <= x <= 2^31 - 1
 *
 *
 *
 * Follow up: Could you solve it without converting the integer to a string?
 */

// @lc code=start
class Solution {
 public:
  bool isPalindrome(int x) {
    if (x < 0 || (x != 0 && x % 10 == 0)) {
      return false;
    }

    int sum{0};
    while (x > sum) {
      sum = sum * 10 + x % 10;
      x = x / 10;
    }

    if (x == sum || x == sum / 10) {
      return true;
    } else {
      return false;
    }
  }
};
// @lc code=end
