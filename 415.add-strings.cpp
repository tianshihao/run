/*
 * @lc app=leetcode.cn id=415 lang=cpp
 *
 * [415] Add Strings
 *
 * https://leetcode.cn/problems/add-strings/description/
 *
 * algorithms
 * Easy (54.98%)
 * Likes:    597
 * Dislikes: 0
 * Total Accepted:    219.2K
 * Total Submissions: 398.8K
 * Testcase Example:  '"11"\n"123"'
 *
 * Given two non-negative integers, num1 and num2 represented as string, return
 * the sum of num1 and num2 as a string.
 *
 * You must solve the problem without using any built-in library for handling
 * large integers (such as BigInteger). You must also not convert the inputs to
 * integers directly.
 *
 *
 * Example 1:
 *
 *
 * Input: num1 = "11", num2 = "123"
 * Output: "134"
 *
 *
 * Example 2:
 *
 *
 * Input: num1 = "456", num2 = "77"
 * Output: "533"
 *
 *
 * Example 3:
 *
 *
 * Input: num1 = "0", num2 = "0"
 * Output: "0"
 *
 *
 *
 * Constraints:
 *
 *
 * 1 <= num1.length, num2.length <= 10^4
 * num1 and num2 consist of only digits.
 * num1 and num2 don't have any leading zeros except for the zero itself.
 *
 *
 */

// @lc code=start
#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  string addStrings(string num1, string num2) {
    if (num1.size() > num2.size()) {
      swap(num1, num2);
    }
    int len1 = num1.size(), len2 = num2.size(), sum = 0;
    string result(len2 + 1, '0');
    for (int i = len1 - 1, j = len2 - 1, k = 0; j >= 0;) {
      sum = (i >= 0 ? num1[i--] - 48 : 0) + (num2[j--] - 48) + sum;
      result[k++] = (sum > 9 ? sum - 10 : sum) + 48;
      sum = sum > 9;
    }
    if (sum){
      result.back() = 49;
    }else{
      result.pop_back();
    }

    reverse(begin(result), end(result));
    return result;
  }
};
// @lc code=end
