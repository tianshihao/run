#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  /**
   * 代码中的类名、方法名、参数名已经指定，请勿修改，直接返回方法规定的值即可
   * Check if 1D spaces can cover all of the testing one
   * @param existings int整型vector<vector<>> existing areas
   * @param target int整型vector target area
   * @return bool布尔型
   */
  bool Is1DSpaceCover(vector<vector<int>>& existings, vector<int>& target) {
    auto comparer{[](const vector<int> a, const vector<int> b) {
      if (a[0] < b[0]) {
        return true;
      } else {
        return false;
      }
    }};
    sort(existings.begin(), existings.end(), comparer);

    vector<vector<int>> merged_interval{};
    merged_interval.emplace_back(existings[0]);

    for (int i = 1; i < existings.size(); ++i) {
      if (existings[i][0] <= merged_interval.back()[1] + 1) {
        merged_interval.back()[1] = existings[i][1];
      } else {
        merged_interval.emplace_back(existings[i]);
      }
    }

    bool is_1d_space_cover{false};
    for (auto interval : merged_interval) {
      if (target[0] >= interval[0] && target[1] <= interval[1]) {
        is_1d_space_cover = true;
      }
    }

    return is_1d_space_cover;
  }
};