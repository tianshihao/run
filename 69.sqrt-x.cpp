/*
 * @lc app=leetcode.cn id=69 lang=cpp
 *
 * [69] Sqrt(x)
 *
 * https://leetcode.cn/problems/sqrtx/description/
 *
 * algorithms
 * Easy (38.80%)
 * Likes:    1082
 * Dislikes: 0
 * Total Accepted:    578.9K
 * Total Submissions: 1.5M
 * Testcase Example:  '4'
 *
 * Given a non-negative integer x, compute and return the square root of x.
 *
 * Since the return type is an integer, the decimal digits are truncated, and
 * only the integer part of the result is returned.
 *
 * Note: You are not allowed to use any built-in exponent function or operator,
 * such as pow(x, 0.5) or x ** 0.5.
 *
 *
 * Example 1:
 *
 *
 * Input: x = 4
 * Output: 2
 *
 *
 * Example 2:
 *
 *
 * Input: x = 8
 * Output: 2
 * Explanation: The square root of 8 is 2.82842..., and since the decimal part
 * is truncated, 2 is returned.
 *
 *
 * Constraints:
 *
 *
 * 0 <= x <= 2^31 - 1
 *
 *
 */

// @lc code=start
class Solution {
 public:
  int mySqrt(int x) {
    // return newtonMethod(x);

    return mySqrtBinarySearch(x);
  }

  int newtonMethod(int x) {
    long r{x};
    while (r * r > x) {
      r = (r + x / r) / 2;
    }
    return r;
  }

  int mySqrtBinarySearch(int x) {
    int left{0}, right{x}, result{-1};
    while (left <= right) {
      long long middle{static_cast<long long>(left + (right - left) / 2)};
      long long square{middle * middle};

      if (square <= x) {
        result = middle;
        left = middle + 1;
      } else {
        right = middle - 1;
      }
    }

    return result;
  }
};
// @lc code=end
