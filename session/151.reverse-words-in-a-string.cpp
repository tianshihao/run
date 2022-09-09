/*
 * @lc app=leetcode.cn id=151 lang=cpp
 *
 * [151] Reverse Words in a String
 *
 * https://leetcode.cn/problems/reverse-words-in-a-string/description/
 *
 * algorithms
 * Medium (50.73%)
 * Likes:    619
 * Dislikes: 0
 * Total Accepted:    284.7K
 * Total Submissions: 561.3K
 * Testcase Example:  '"the sky is blue"'
 *
 * Given an input string s, reverse the order of the words.
 *
 * A word is defined as a sequence of non-space characters. The words in s will
 * be separated by at least one space.
 *
 * Return a string of the words in reverse order concatenated by a single
 * space.
 *
 * Note that s may contain leading or trailing spaces or multiple spaces
 * between two words. The returned string should only have a single space
 * separating the words. Do not include any extra spaces.
 *
 *
 * Example 1:
 *
 *
 * Input: s = "the sky is blue"
 * Output: "blue is sky the"
 *
 *
 * Example 2:
 *
 *
 * Input: s = "  hello world  "
 * Output: "world hello"
 * Explanation: Your reversed string should not contain leading or trailing
 * spaces.
 *
 *
 * Example 3:
 *
 *
 * Input: s = "a good   example"
 * Output: "example good a"
 * Explanation: You need to reduce multiple spaces between two words to a
 * single space in the reversed string.
 *
 *
 *
 * Constraints:
 *
 *
 * 1 <= s.length <= 10^4
 * s contains English letters (upper-case and lower-case), digits, and spaces '
 * '.
 * There is at least one word in s.
 *
 *
 *
 * Follow-up: If the string data type is mutable in your language, can you
 * solve it in-place with O(1) extra space?
 *
 */

// @lc code=start
#include <bits/stdc++.h>
using namespace std;

class Solution {
 private:
  stack<string> words_stack;

 public:
  string reverseWords(string str) {
    // peel
    str.erase(0, str.find_first_not_of(' '));
    str.erase(str.find_last_not_of(' ') + 1);

    // reverse
    string word{};
    bool need_space_here{true};

    for (auto c : str) {
      if (true == IsNonSpace(c)) {
        word += c;
        need_space_here = true;
      } else {
        words_stack.push(word);
        if (true == need_space_here) {
          words_stack.push(" ");
          need_space_here = false;
        }
        word = "";
      }
    }

    // deal trailing word
    if (word.size() != 0) {
      words_stack.push(word);
    }

    // pour out
    string result{};
    while (!words_stack.empty()) {
      result += words_stack.top();
      words_stack.pop();
    }

    return result;
  }

  bool IsNonSpace(char c) {
    if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') ||
        (c >= '0' && c <= '9')) {
      return true;
    } else {
      return false;
    }
  }
};
// @lc code=end
