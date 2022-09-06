/*
 * @lc app=leetcode.cn id=165 lang=cpp
 *
 * [165] Compare Version Numbers
 *
 * https://leetcode.cn/problems/compare-version-numbers/description/
 *
 * algorithms
 * Medium (51.94%)
 * Likes:    311
 * Dislikes: 0
 * Total Accepted:    122K
 * Total Submissions: 234.8K
 * Testcase Example:  '"1.01"\n"1.001"'
 *
 * Given two version numbers, version1 and version2, compare them.
 *
 *
 *
 *
 * Version numbers consist of one or more revisions joined by a dot '.'. Each
 * revision consists of digits and may contain leading zeros. Every revision
 * contains at least one character. Revisions are 0-indexed from left to right,
 * with the leftmost revision being revision 0, the next revision being
 * revision 1, and so on. For example 2.5.33 and 0.1 are valid version
 * numbers.
 *
 * To compare version numbers, compare their revisions in left-to-right order.
 * Revisions are compared using their integer value ignoring any leading zeros.
 * This means that revisions 1 and 001 are considered equal. If a version
 * number does not specify a revision at an index, then treat the revision as
 * 0. For example, version 1.0 is less than version 1.1 because their revision
 * 0s are the same, but their revision 1s are 0 and 1 respectively, and 0 < 1.
 *
 * Return the following:
 *
 *
 * If version1 < version2, return -1.
 * If version1 > version2, return 1.
 * Otherwise, return 0.
 *
 *
 *
 * Example 1:
 *
 *
 * Input: version1 = "1.01", version2 = "1.001"
 * Output: 0
 * Explanation: Ignoring leading zeroes, both "01" and "001" represent the same
 * integer "1".
 *
 *
 * Example 2:
 *
 *
 * Input: version1 = "1.0", version2 = "1.0.0"
 * Output: 0
 * Explanation: version1 does not specify revision 2, which means it is treated
 * as "0".
 *
 *
 * Example 3:
 *
 *
 * Input: version1 = "0.1", version2 = "1.1"
 * Output: -1
 * Explanation: version1's revision 0 is "0", while version2's revision 0 is
 * "1". 0 < 1, so version1 < version2.
 *
 *
 *
 * Constraints:
 *
 *
 * 1 <= version1.length, version2.length <= 500
 * version1 and version2 only contain digits and '.'.
 * version1 and version2 are valid version numbers.
 * All the given revisions in version1 and version2 can be stored in a 32-bit
 * integer.
 *
 *
 */

// @lc code=start
#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  int compareVersion(string version1, string version2) {
    queue<int> version1_numbers{};
    queue<int> version2_numbers{};

    string delimiter{"."};
    size_t pos{0};

    // split
    while ((pos = version1.find(delimiter, pos)) != string::npos) {
      version1_numbers.emplace(stoi(version1.substr(0, pos)));
      version1.erase(0, pos + 1);
      pos = 0;
    }
    version1_numbers.emplace(stoi(version1));

    pos = 0;
    while ((pos = version2.find(delimiter, pos)) != string::npos) {
      version2_numbers.emplace(stoi(version2.substr(0, pos)));
      version2.erase(0, pos + 1);
      pos = 0;
    }
    version2_numbers.emplace(stoi(version2));

    // align
    while (version1_numbers.size() < version2_numbers.size()) {
      version1_numbers.emplace(0);
    }
    while (version1_numbers.size() > version2_numbers.size()) {
      version2_numbers.emplace(0);
    }

    // compare
    while (!version1_numbers.empty() && !version2_numbers.empty()) {
      if (version1_numbers.front() > version2_numbers.front()) {
        return 1;
      } else if (version1_numbers.front() < version2_numbers.front()) {
        return -1;
      } else {
        version1_numbers.pop();
        version2_numbers.pop();
      }
    }

    return 0;
  }
};

// int main(int argc, char const *argv[]) {
//   Solution s;
//   // s.compareVersion("10.6.5", "10.6");
//   s.compareVersion("1.01", "1.001");
//   return 0;
// }

// @lc code=end
