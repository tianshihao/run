/*
 * @lc app=leetcode.cn id=128 lang=cpp
 *
 * [128] Longest Consecutive Sequence
 *
 * https://leetcode.cn/problems/longest-consecutive-sequence/description/
 *
 * algorithms
 * Medium (55.15%)
 * Likes:    1364
 * Dislikes: 0
 * Total Accepted:    305.5K
 * Total Submissions: 554K
 * Testcase Example:  '[100,4,200,1,3,2]'
 *
 * Given an unsorted array of integers nums, return the length of the longest
 * consecutive elements sequence.
 *
 * You must write an algorithm that runs in O(n) time.
 *
 *
 * Example 1:
 *
 *
 * Input: nums = [100,4,200,1,3,2]
 * Output: 4
 * Explanation: The longest consecutive elements sequence is [1, 2, 3, 4].
 * Therefore its length is 4.
 *
 *
 * Example 2:
 *
 *
 * Input: nums = [0,3,7,2,5,8,4,6,0,1]
 * Output: 9
 *
 *
 *
 * Constraints:
 *
 *
 * 0 <= nums.length <= 10^5
 * -10^9 <= nums[i] <= 10^9
 *
 *
 */

// @lc code=start
#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  int longestConsecutive(vector<int>& nums) {
    unordered_set<int> num_set{};
    for (const auto& num : nums) {
      num_set.insert(num);
    }

    int longest_streak = 0;

    for (const auto& num : nums) {
      // A new start.
      if (false == num_set.count(num - 1)) {
        int current_num = num;
        int current_streak = 1;

        // Traverse this interval.
        while (true == num_set.count(current_num + 1)) {
          ++current_num;
          ++current_streak;
        }

        longest_streak = max(longest_streak, current_streak);
      }
    }

    return longest_streak;
  }
};
// @lc code=end
