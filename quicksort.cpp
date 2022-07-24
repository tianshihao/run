#include <bits/stdc++.h>
using namespace std;

void QuickSort(vector<int> nums);
void QuickSort(vector<int> nums, size_t left, size_t right);
size_t Partition(vector<int> nums, size_t left, size_t right);

int main(int argc, char** argv) {
  vector<int> nums{1, 5, 7, 2, 9, 2, 8, 4, 1, 7};
  QuickSort(nums);

  return 0;
}

void QuickSort(vector<int> nums) {
  QuickSort(nums, 0, nusm.size() - 1);
  return;
}

void QuickSort(vector<int> nums, size_t left, size_t right) {
  if (left < right) {
    size_t pivot{Partition(nums, left, right)};
    QuickSort(nums, left, pivot - 1);
    QuickSort(nums, pivot + 1, right);
  }
  return;
}

size_t Partition(vector<int> nums, size_t left, size_t right) {
  int pivot{nums[left]};
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
