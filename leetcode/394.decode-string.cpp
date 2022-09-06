/*
 * @lc app=leetcode.cn id=394 lang=cpp
 *
 * [394] Decode String
 *
 * https://leetcode.cn/problems/decode-string/description/
 *
 * algorithms
 * Medium (56.59%)
 * Likes:    1266
 * Dislikes: 0
 * Total Accepted:    193.7K
 * Total Submissions: 342.3K
 * Testcase Example:  '"3[a]2[bc]"'
 *
 * Given an encoded string, return its decoded string.
 *
 * The encoding rule is: k[encoded_string], where the encoded_string inside the
 * square brackets is being repeated exactly k times. Note that k is guaranteed
 * to be a positive integer.
 *
 * You may assume that the input string is always valid; there are no extra
 * white spaces, square brackets are well-formed, etc. Furthermore, you may
 * assume that the original data does not contain any digits and that digits
 * are only for those repeat numbers, k. For example, there will not be input
 * like 3a or 2[4].
 *
 * The test cases are generated so that the length of the output will never
 * exceed 10^5.
 *
 *
 * Example 1:
 *
 *
 * Input: s = "3[a]2[bc]"
 * Output: "aaabcbc"
 *
 *
 * Example 2:
 *
 *
 * Input: s = "3[a2[c]]"
 * Output: "accaccacc"
 *
 *
 * Example 3:
 *
 *
 * Input: s = "2[abc]3[cd]ef"
 * Output: "abcabccdcdcdef"
 *
 *
 *
 * Constraints:
 *
 *
 * 1 <= s.length <= 30
 * s consists of lowercase English letters, digits, and square brackets
 * '[]'.
 * s is guaranteed to be a valid input.
 * All the integers in s are in the range [1, 300].
 *
 *
 */

// @lc code=start
#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  string decodeString(string s) {
    stack<int> number_stack{};
    stack<string> str_stack{};

    int number{0};
    string str{};

    for (const auto ch : s) {
      // Ignore '['.
      if ('[' == ch) {
        continue;
      }

      // Collect numbers and letters.
      if (isdigit(ch)) {
        number = number * 10 + atoi(&ch);

        if (str.empty() != true) {
          str_stack.push(str);
          str.clear();
        }

        continue;
      } else if (isalpha(ch)) {
        str += ch;

        if (number != 0) {
          number_stack.push(number);
          number = 0;
        }

        continue;
      }

      // Pop.
      if (']' == ch) {
        // Clear the previous string.
        if (str.empty() != true) {
          str_stack.push(str);
          str.clear();
        }

        // Repeat.

        const auto str_on_the_top{str_stack.top()};
        str_stack.pop();
        auto repeated_times{number_stack.top()};
        number_stack.pop();

        string repeated_str{getRepeatedString(str_on_the_top, repeated_times)};

        // Update str_stack.

        if (str_stack.empty() != true) {
          str_stack.top() = str_stack.top() + repeated_str;
          // str_stack.pop();
        } else {
          str_stack.push(repeated_str);
        }
      }
    }

    // Trailing string.
    return str_stack.top() + str;
  }

  string getRepeatedString(string str, int times) {
    string repeated_str{};
    while (times--) {
      repeated_str += str;
    }

    return repeated_str;
  }
};

int main(int argc, char** argv) {
  Solution s;
  // string test_case{"3[a2[c]]"};
  string test_case{"2[abc]3[cd]ef"};
  // string test_case{"8[z3[a]6[a2[bc]]4[as]]"};
  // string test_case{"abc3[cd]xyz"};

  cout << s.decodeString(test_case);

  return 0;
}

// @lc code=end
