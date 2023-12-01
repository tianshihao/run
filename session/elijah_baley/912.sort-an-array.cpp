/*
 * @lc app=leetcode.cn id=912 lang=cpp
 *
 * [912] Sort an Array
 *
 * https://leetcode.cn/problems/sort-an-array/description/
 *
 * algorithms
 * Medium (55.70%)
 * Likes:    647
 * Dislikes: 0
 * Total Accepted:    428.5K
 * Total Submissions: 769.3K
 * Testcase Example:  '[5,2,3,1]'
 *
 * Given an array of integers nums, sort the array in ascending order.
 *
 *
 * Example 1:
 * Input: nums = [5,2,3,1]
 * Output: [1,2,3,5]
 * Example 2:
 * Input: nums = [5,1,1,2,0,0]
 * Output: [0,0,1,1,2,5]
 *
 *
 * Constraints:
 *
 *
 * 1 <= nums.length <= 5 * 10^4
 * -5 * 10^4 <= nums[i] <= 5 * 10^4
 *
 *
 */

// @lc code=start
#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  vector<int> sortArray(vector<int>& nums) {
    // return QuickSort(nums);
    return HeapSort(nums);
    // return MergeSort(nums);
  }

 private:
  vector<int> HeapSort(vector<int>& nums) {
    BuildHeap(nums);

    for (int i = 1; i < nums.size(); ++i) {
      swap(nums[0], nums[nums.size() - i]);
      AdjustHeap(nums, 0, nums.size() - i);
    }

    return nums;
  }

  void BuildHeap(vector<int>& nums) {
    const int length = nums.size();

    for (int i = length / 2; i >= 0; --i) {
      AdjustHeap(nums, i, length);
    }

    return;
  }

  void AdjustHeap(vector<int>& nums, int parent, const int length) {
    // Attention index start by 0.
    for (int child = parent * 2 + 1; child < length; child = child * 2 + 1) {
      // Find the greater child.
      if (child + 1 < length && nums[child] < nums[child + 1]) {
        ++child;
      }

      // There needs swap between root and child.
      if (nums[parent] <= nums[child]) {
        // Swap.
        swap(nums[parent], nums[child]);

        // Parent shift down.
        parent = child;
      } else {
        // Nothing to do.
        break;
      }
    }

    return;
  }

  // TODO: 1. Non-cursively.  2. Quick sort for linked list.
  vector<int> QuickSort(vector<int>& nums) {
    QuickSort(nums, 0, nums.size() - 1);
    return nums;
  }

  void QuickSort(vector<int>& nums, int left, int right) {
    if (left < right) {
      int pivot = Partition(nums, left, right);
      QuickSort(nums, left, pivot - 1);
      QuickSort(nums, pivot + 1, right);
    }

    return;
  }

  int Partition(vector<int>& nums, int left, int right) {
    int random_idx = left + (right - left) % rand();
    int pivot = nums[random_idx];
    swap(nums[left], nums[random_idx]);

    while (left < right) {
      while (left < right && nums[right] >= pivot) {
        --right;
      }
      nums[left] = nums[right];

      while (left < right && nums[left] <= pivot) {
        ++left;
      }
      nums[right] = nums[left];
    }

    nums[left] = pivot;
    return left;
  }

  vector<int> MergeSort(vector<int>& nums) {
    MergeSort(nums, 0, nums.size() - 1);
    return nums;
  }

  void MergeSort(vector<int>& nums, int left, int right) {
    if (left < right) {
      int middle = (left + right) / 2;

      // Divide and conquer.
      MergeSort(nums, left, middle);
      MergeSort(nums, middle + 1, right);

      // Merge.
      Merge(nums, left, middle, right);
    } else {
      return;
    }
  }

  void Merge(vector<int>& nums, int left, int middle, int right) {
    vector<int> buffer(nums);

    int i = left, j = middle + 1, write_ptr = left;

    while (i <= middle && j <= right) {
      if (buffer[i] <= buffer[j]) {
        nums[write_ptr++] = buffer[i++];
      } else {
        nums[write_ptr++] = buffer[j++];
      }
    }

    while (i <= middle) {
      nums[write_ptr++] = buffer[i++];
    }
    while (j <= right) {
      nums[write_ptr++] = buffer[j++];
    }

    return;
  }
};
// @lc code=end
