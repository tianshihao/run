/*
 * @lc app=leetcode.cn id=35 lang=cpp
 *
 * [35] Search Insert Position
 *
 * https://leetcode.cn/problems/search-insert-position/description/
 *
 * algorithms
 * Easy (45.72%)
 * Likes:    2269
 * Dislikes: 0
 * Total Accepted:    1.4M
 * Total Submissions: 3M
 * Testcase Example:  '[1,3,5,6]\n5'
 *
 * Given a sorted array of distinct integers and a target value, return the
 * index if the target is found. If not, return the index where it would be if
 * it were inserted in order.
 *
 * You must write an algorithm with O(log n) runtime complexity.
 *
 *
 * Example 1:
 *
 *
 * Input: nums = [1,3,5,6], target = 5
 * Output: 2
 *
 *
 * Example 2:
 *
 *
 * Input: nums = [1,3,5,6], target = 2
 * Output: 1
 *
 *
 * Example 3:
 *
 *
 * Input: nums = [1,3,5,6], target = 7
 * Output: 4
 *
 *
 *
 * Constraints:
 *
 *
 * 1 <= nums.length <= 10^4
 * -10^4 <= nums[i] <= 10^4
 * nums contains distinct values sorted in ascending order.
 * -10^4 <= target <= 10^4
 *
 *
 */

// @lc code=start
#include <bits/c++config.h>
#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  int searchInsert(vector<int>& nums, int target) {
    // nums[pos - 1] < target <= nums[pos]

    int pos{static_cast<int>(nums.size())};
    int low{0}, high{static_cast<int>(nums.size() - 1)};

    while (low <= high) {
      auto mid{low + ((high - low) >> 1)};
      if (target <= nums[mid]) {
        high = mid - 1;
        pos = mid;
      } else {
        low = mid + 1;
      }
    }

    return pos;
  }
};

// int main() {
//   Solution s;

//   vector<int> vec{1, 3, 5, 6};
//   s.searchInsert(vec, 2);

//   return 0;
// }
// @lc code=end
