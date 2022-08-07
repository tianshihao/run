#include <bits/stdc++.h>
using namespace std;

class Solution {
 private:
  stack<string> s;

 public:
  /**
   * 代码中的类名、方法名、参数名已经指定，请勿修改，直接返回方法规定的值即可
   * Reverse a string includes symbols from ASCII, keep words with right order.
   * @param str string字符串
   * @return string字符串
   */
  string Reverse(string str) {
    string word{};
    string non_word_char{};

    char c;
    for (int i = 0; i < str.size(); ++i) {
      c = str[i];
      if (IsNonSpace(c)) {
        s.push(non_word_char);
        word += c;
      } else {
        non_word_char = c;
        s.push(word);
        s.push(non_word_char);
        word = "";
        non_word_char = "";
      }
    }

    if (word.size() != 0) {
      s.push(word);
    }

    string result{};
    while (!s.empty()) {
      result += s.top();
      s.pop();
    }

    return result;
  }

  bool IsNonSpace(char c) {
    if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) {
      return true;
    } else {
      return false;
    }
  }
};