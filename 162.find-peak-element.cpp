/*
 * @lc app=leetcode.cn id=162 lang=cpp
 *
 * [162] Find Peak Element
 *
 * https://leetcode.cn/problems/find-peak-element/description/
 *
 * algorithms
 * Medium (49.48%)
 * Likes:    873
 * Dislikes: 0
 * Total Accepted:    251K
 * Total Submissions: 507.3K
 * Testcase Example:  '[1,2,3,1]'
 *
 * A peak element is an element that is strictly greater than its neighbors.
 *
 * Given a 0-indexed integer array nums, find a peak element, and return its
 * index. If the array contains multiple peaks, return the index to any of the
 * peaks.
 *
 * You may imagine that nums[-1] = nums[n] = -∞. In other words, an element is
 * always considered to be strictly greater than a neighbor that is outside the
 * array.
 *
 * You must write an algorithm that runs in O(log n) time.
 *
 *
 * Example 1:
 *
 *
 * Input: nums = [1,2,3,1]
 * Output: 2
 * Explanation: 3 is a peak element and your function should return the index
 * number 2.
 *
 * Example 2:
 *
 *
 * Input: nums = [1,2,1,3,5,6,4]
 * Output: 5
 * Explanation: Your function can return either index number 1 where the peak
 * element is 2, or index number 5 where the peak element is 6.
 *
 *
 * Constraints:
 *
 *
 * 1 <= nums.length <= 1000
 * -2^31 <= nums[i] <= 2^31 - 1
 * nums[i] != nums[i + 1] for all valid i.
 *
 *
 */

// @lc code=start
#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  int findPeakElement(vector<int>& nums) {
    int left = 0, right = nums.size() - 1;

    while (left < right - 1) {
      int middle = (left + right) / 2;
      if (nums[middle] > nums[middle - 1] && nums[middle] > nums[middle + 1]) {
        return middle;
      } else if (nums[middle] > nums[middle + 1]) {
        right = middle - 1;
      } else {
        left = middle + 1;
      }
    }

    if (nums[left] > nums[right]) {
      return left;
    } else {
      return right;
    }
  }
};
// @lc code=end
