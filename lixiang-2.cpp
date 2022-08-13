#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  int KthElement(vector<int>& nums, int k) {
    return KthElementQuickSort(nums, 0, nums.size() - 1);
  }

  int KthElementQuickSort(vector<int>& nums, int left, int right) {
    if (left < right) {
      int pivot = Partition(nums, left, right);

      if (pivot == k) {
        return nums[k];
      }

      KthElementQuickSort(nums, left, pivot - 1);
      KthElementQuickSort(nums, pivot + 1, right);
    }

    return -1;
  }

  int Partition(vector<int>& nums, int left, int right) {
    int pivot = nums[left];
    while (left <= right) {
      while (left < right && nums[right] > pivot) {
        right--;
      }
      nums[right] = nums[left];

      while (left < right && nums[left] < pivot) {
        left++;
      }
      nums[left] = nums[right];
    }

    nums[left] = pivot;

    return left;
  }
};
