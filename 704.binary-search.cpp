/*
 * @lc app=leetcode.cn id=704 lang=cpp
 *
 * [704] Binary Search
 *
 * https://leetcode.cn/problems/binary-search/description/
 *
 * algorithms
 * Easy (54.45%)
 * Likes:    914
 * Dislikes: 0
 * Total Accepted:    686.6K
 * Total Submissions: 1.3M
 * Testcase Example:  '[-1,0,3,5,9,12]\n9'
 *
 * Given an array of integers nums which is sorted in ascending order, and an
 * integer target, write a function to search target in nums. If target exists,
 * then return its index. Otherwise, return -1.
 *
 * You must write an algorithm with O(log n) runtime complexity.
 *
 *
 * Example 1:
 *
 *
 * Input: nums = [-1,0,3,5,9,12], target = 9
 * Output: 4
 * Explanation: 9 exists in nums and its index is 4
 *
 *
 * Example 2:
 *
 *
 * Input: nums = [-1,0,3,5,9,12], target = 2
 * Output: -1
 * Explanation: 2 does not exist in nums so return -1
 *
 *
 *
 * Constraints:
 *
 *
 * 1 <= nums.length <= 10^4
 * -10^4 < nums[i], target < 10^4
 * All the integers in nums are unique.
 * nums is sorted in ascending order.
 *
 *
 */

// @lc code=start
#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  int search(vector<int>& nums, int target) {
    return binarySearch(nums, target);
  }

  int binarySearch(vector<int>& nums, int target) {
    return binarySearchRecursively(nums, target, 0, nums.size() - 1);
  }

  int binarySearchRecursively(vector<int>& nums, int target, int left,
                              int right) {
    if (left > right) {
      return -1;
    }

    int mid{(left + right) / 2};
    if (target == nums[mid]) {
      return mid;
    } else if (target < nums[mid]) {
      return binarySearchRecursively(nums, target, left, mid - 1);
    } else {
      return binarySearchRecursively(nums, target, mid + 1, right);
    }
  }
};
// @lc code=end
