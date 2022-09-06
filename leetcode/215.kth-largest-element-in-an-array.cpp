/*
 * @lc app=leetcode.cn id=215 lang=cpp
 *
 * [215] Kth Largest Element in an Array
 *
 * https://leetcode.cn/problems/kth-largest-element-in-an-array/description/
 *
 * algorithms
 * Medium (64.73%)
 * Likes:    1767
 * Dislikes: 0
 * Total Accepted:    687.4K
 * Total Submissions: 1.1M
 * Testcase Example:  '[3,2,1,5,6,4]\n2'
 *
 * Given an integer array nums and an integer k, return the k^th largest
 * element in the array.
 *
 * Note that it is the k^th largest element in the sorted order, not the k^th
 * distinct element.
 *
 * You must solve it in O(n) time complexity.
 *
 *
 * Example 1:
 * Input: nums = [3,2,1,5,6,4], k = 2
 * Output: 5
 * Example 2:
 * Input: nums = [3,2,3,1,2,4,5,5,6], k = 4
 * Output: 4
 *
 *
 * Constraints:
 *
 *
 * 1 <= k <= nums.length <= 10^5
 * -10^4 <= nums[i] <= 10^4
 *
 *
 */

// @lc code=start
#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  int findKthLargest(vector<int>& nums, int k) {
    // return findKthLargestPartition(nums, 0, nums.size() - 1, k);
    // return findKthLargestPQ(nums, k);
    // return findKthLargestMaxHeap(nums, k);
  }

  int findKthLargestPartition(vector<int>& nums, int left, int right, int k) {
    int kth{numeric_limits<int>::max()};
    while (true) {
      int pivot{partition(nums, left, right)};

      if (pivot == k - 1) {
        kth = nums[pivot];
        break;
      }

      if (pivot >= k - 1) {
        right = pivot - 1;
      } else {
        left = pivot + 1;
      }
    }
    return kth;
  }

  int partition(vector<int>& nums, int left, int right) {
    int pivot{nums[left]};
    while (left < right) {
      while (left < right && nums[right] <= pivot) {
        --right;
      }
      nums[left] = nums[right];
      while (left < right && nums[left] >= pivot) {
        ++left;
      }
      nums[right] = nums[left];
    }
    nums[left] = pivot;

    return left;
  }

  int findKthLargestPQ(vector<int>& nums, int k) {
    priority_queue<int> max_heap{nums.begin(), nums.end()};
    for (int i{0}; i < k - 1; ++i) {
      max_heap.pop();
    }
    return max_heap.top();
  }

  int findKthLargestMaxHeap(vector<int>& nums, int k) {
    buildMaxHeap(nums);
    size_t len{nums.size() - 1};
    for (size_t i{len}, j{0}; i >= 0 && j < static_cast<size_t>(k - 1);
         --i, ++j) {
      swap(nums[i], nums[0]);
      heapAdjust(nums, 0, static_cast<int>(i - 1));
    }

    return nums[0];
  }

  void buildMaxHeap(vector<int>& nums) {
    for (int i = nums.size() / 2; i >= 0; --i) {
      heapAdjust(nums, i, nums.size() - 1);
    }

    return;
  }

  void heapAdjust(vector<int>& nums, int root, size_t len) {
    int backup{nums[root]};
    for (size_t child = root; child <= len; child *= 2) {
      if (child + 1 <= len && nums[child] < nums[child + 1]) {
        ++child;
      }
      if (nums[root] > nums[child]) {
        break;
      } else {
        // move down to child.
        nums[root] = nums[child];
        root = child;
      }
    }
    nums[root] = backup;

    return;
  }
};

// int main(int argc, char** argv) {
//   Solution s;
//   vector<int> nums{3, 2, 1, 5, 6, 4};
//   s.findKthLargest(nums, 2);

//   return 0;
// }

// @lc code=end
