/*
 * @lc app=leetcode.cn id=67 lang=cpp
 *
 * [67] Add Binary
 *
 * https://leetcode.cn/problems/add-binary/description/
 *
 * algorithms
 * Easy (53.79%)
 * Likes:    847
 * Dislikes: 0
 * Total Accepted:    261.3K
 * Total Submissions: 485.8K
 * Testcase Example:  '"11"\n"1"'
 *
 * Given two binary strings a and b, return their sum as a binary string.
 *
 *
 * Example 1:
 * Input: a = "11", b = "1"
 * Output: "100"
 * Example 2:
 * Input: a = "1010", b = "1011"
 * Output: "10101"
 *
 *
 * Constraints:
 *
 *
 * 1 <= a.length, b.length <= 10^4
 * a and b consist only of '0' or '1' characters.
 * Each string does not contain leading zeros except for the zero itself.
 *
 *
 */

// @lc code=start
#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  string addBinary(string a, string b) {
    string result{};
    bool carry{false};
    for (auto it_a{a.end() - 1}, it_b{b.end() - 1};
         it_a >= a.begin() && it_b >= b.begin(); --it_a, --it_b) {
      if (*it_a == *it_b) {
        if (*it_a == '1') {
          if (carry) {
            // result.insert(result.begin(), '1');
            result.push_back('1');
          } else {
            // result.insert(result.begin(), '0');
            result.push_back('0');
            carry = true;
          }
        } else {
          //   result.insert(result.begin(), '0');
          result.push_back('0');
          carry = false;
        }
      } else {
        if (carry) {
          //   result.insert(result.begin(), '0');
          result.push_back('0');
        } else {
          //   result.insert(result.begin(), '1');
          result.push_back('1');
        }
      }
    }
    std::reverse(result.begin(), result.end());
    return result;
  }
};
// @lc code=end
