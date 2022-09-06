/*
 * @lc app=leetcode.cn id=14 lang=cpp
 *
 * [14] Longest Common Prefix
 *
 * https://leetcode.cn/problems/longest-common-prefix/description/
 *
 * algorithms
 * Easy (42.69%)
 * Likes:    2348
 * Dislikes: 0
 * Total Accepted:    883K
 * Total Submissions: 2.1M
 * Testcase Example:  '["flower","flow","flight"]'
 *
 * Write a function to find the longest common prefix string amongst an array
 * of strings.
 *
 * If there is no common prefix, return an empty string "".
 *
 *
 * Example 1:
 *
 *
 * Input: strs = ["flower","flow","flight"]
 * Output: "fl"
 *
 *
 * Example 2:
 *
 *
 * Input: strs = ["dog","racecar","car"]
 * Output: ""
 * Explanation: There is no common prefix among the input strings.
 *
 *
 *
 * Constraints:
 *
 *
 * 1 <= strs.length <= 200
 * 0 <= strs[i].length <= 200
 * strs[i] consists of only lowercase English letters.
 *
 *
 */

// @lc code=start
#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  string longestCommonPrefix(vector<string>& strs) {
    if (1 == strs.size()) {
      return strs[0];
    }

    sort(strs.begin(), strs.end());

    string& first_str = strs[0];
    string& last_str = strs[strs.size() - 1];
    string result{};
    for (size_t i{0}; i < first_str.size() && i < last_str.size(); ++i) {
      if (first_str[i] == last_str[i]) {
        result.push_back(first_str[i]);
        continue;
      } else {
        break;
      }
    }

    return result;
  }
};
// @lc code=end
