/*
 * @lc app=leetcode.cn id=5 lang=cpp
 *
 * [5] Longest Palindromic Substring
 *
 * https://leetcode.cn/problems/longest-palindromic-substring/description/
 *
 * algorithms
 * Medium (36.91%)
 * Likes:    5491
 * Dislikes: 0
 * Total Accepted:    1.1M
 * Total Submissions: 3M
 * Testcase Example:  '"babad"'
 *
 * Given a string s, return the longest palindromic substring in s.
 *
 *
 * Example 1:
 *
 *
 * Input: s = "babad"
 * Output: "bab"
 * Explanation: "aba" is also a valid answer.
 *
 *
 * Example 2:
 *
 *
 * Input: s = "cbbd"
 * Output: "bb"
 *
 *
 *
 * Constraints:
 *
 *
 * 1 <= s.length <= 1000
 * s consist of only digits and English letters.
 *
 *
 */

// @lc code=start
#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  string longestPalindrome(string s) {
    int len = s.size();
    string result{};
    result += s[0];
    bitset<1000> dp[len];
    for (int i = 0; i < len; ++i) {
      dp[i][i] = true;
    }

    for (int i = len - 1; i >= 0; --i) {
      for (int j = i + 1; j < len; ++j) {
        if (s[i] == s[j]) {
          if (j == i + 1 || dp[i + 1][j - 1]) {
            dp[i][j] = true;
            if (result.size() < j - i + 1) {
              result = s.substr(i, j - i + 1);
            }
          }
        }
      }
    }

    return result;
  }
};
// @lc code=end
