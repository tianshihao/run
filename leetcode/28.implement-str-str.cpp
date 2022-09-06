/*
 * @lc app=leetcode.cn id=28 lang=cpp
 *
 * [28] Implement strStr()
 *
 * https://leetcode.cn/problems/implement-strstr/description/
 *
 * algorithms
 * Easy (41.03%)
 * Likes:    1502
 * Dislikes: 0
 * Total Accepted:    688.9K
 * Total Submissions: 1.7M
 * Testcase Example:  '"hello"\n"ll"'
 *
 * Implement strStr().
 *
 * Given two strings needle and haystack, return the index of the first
 * occurrence of needle in haystack, or -1 if needle is not part of haystack.
 *
 * Clarification:
 *
 * What should we return when needle is an empty string? This is a great
 * question to ask during an interview.
 *
 * For the purpose of this problem, we will return 0 when needle is an empty
 * string. This is consistent to C's strstr() and Java's indexOf().
 *
 *
 * Example 1:
 *
 *
 * Input: haystack = "hello", needle = "ll"
 * Output: 2
 *
 *
 * Example 2:
 *
 *
 * Input: haystack = "aaaaa", needle = "bba"
 * Output: -1
 *
 *
 *
 * Constraints:
 *
 *
 * 1 <= haystack.length, needle.length <= 10^4
 * haystack and needle consist of only lowercase English characters.
 *
 *
 */

// @lc code=start
#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  int strStr(string haystack, string needle) {
    int m = haystack.size();
    int n = needle.size();

    for (int i{0}; i <= m - n; ++i) {
      int j{0};
      for (; j < n; ++j) {
        if (haystack[i + j] != needle[j]) {
          break;
        }
      }
      if (j == n) {
        return static_cast<int>(i);
      }
    }

    return -1;
  }
};
// @lc code=end
