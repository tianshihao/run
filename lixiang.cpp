#include <bits/stdc++.h>
using namespace std;

vector<int> MergeVector(const vector<int>& nums1, const vector<int>& nums2) {
  sort(nums1.begin(), nums1.end());
  sort(nums2.begin(), nums2.end());

  vector<int> result{};

  int i = 0, j = 0;
  while (i < nums1.size() && j < nums2.size()) {
    if (nums1[i] <= nums2[j]) {
      if (nums1[i] != result.back()) {
        result.emplace_back(nums1[i++]);
      } else {
        i++;
      }
    } else {
      if (nums1[j] != result.back()) {
        result.emplace_back(nums2[j++]);
      } else {
        j++;
      }
    }
  }

  while (i < nums1.size()) {
    if (nums1[i] != result.back()) {
      result.emplace_back(nums1[i++]);
    } else {
      i++;
    }
  }
  while (j < nums2.size()) {
    if (nums1[j] != result.back()) {
      result.emplace_back(nums2[j++]);
    } else {
      j++;
    }
  }

  return result;
}

int main() { return 0; }