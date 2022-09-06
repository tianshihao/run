/*
 * @lc app=leetcode.cn id=103 lang=cpp
 *
 * [103] Binary Tree Zigzag Level Order Traversal
 *
 * https://leetcode.cn/problems/binary-tree-zigzag-level-order-traversal/description/
 *
 * algorithms
 * Medium (57.34%)
 * Likes:    677
 * Dislikes: 0
 * Total Accepted:    257.1K
 * Total Submissions: 448.4K
 * Testcase Example:  '[3,9,20,null,null,15,7]'
 *
 * Given the root of a binary tree, return the zigzag level order traversal of
 * its nodes' values. (i.e., from left to right, then right to left for the
 * next level and alternate between).
 *
 *
 * Example 1:
 *
 *
 * Input: root = [3,9,20,null,null,15,7]
 * Output: [[3],[20,9],[15,7]]
 *
 *
 * Example 2:
 *
 *
 * Input: root = [1]
 * Output: [[1]]
 *
 *
 * Example 3:
 *
 *
 * Input: root = []
 * Output: []
 *
 *
 *
 * Constraints:
 *
 *
 * The number of nodes in the tree is in the range [0, 2000].
 * -100 <= Node.val <= 100
 *
 *
 */

// @lc code=start
#include <bits/stdc++.h>
using namespace std;

// struct TreeNode {
//   int val;
//   TreeNode *left;
//   TreeNode *right;
//   TreeNode() : val(0), left(nullptr), right(nullptr) {}
//   TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
//   TreeNode(int x, TreeNode *left, TreeNode *right)
//       : val(x), left(left), right(right) {}
// };

class Solution {
 public:
  vector<vector<int>> zigzagLevelOrder(TreeNode *root) {
    return myZigzagLevelOrder(root);
  }

  vector<vector<int>> myZigzagLevelOrder(TreeNode *root) {
    if (nullptr == root) {
      return {};
    }

    vector<vector<int>> result{};

    queue<TreeNode *> q{};
    q.emplace(root);
    q.emplace(nullptr);

    vector<int> cur_level{};
    bool is_reverse{false};

    while (!q.empty()) {
      TreeNode *node{q.front()};
      q.pop();

      if (node != nullptr) {
        cur_level.emplace_back(node->val);

        if (node->left != nullptr) {
          q.emplace(node->left);
        }
        if (node->right != nullptr) {
          q.emplace(node->right);
        }
      } else {
        // zigzag here.
        if (true == is_reverse) {
          reverse(cur_level.begin(), cur_level.end());
        }
        // both
        // is_reverse ^= true;
        is_reverse = !is_reverse;

        result.emplace_back(cur_level);
        cur_level.resize(0);

        // ! add next level end mark
        if (q.size() > 0) {
          q.emplace(nullptr);
        }
      }
    }

    return result;
  }
};
// @lc code=end
