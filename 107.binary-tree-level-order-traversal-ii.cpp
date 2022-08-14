/*
 * @lc app=leetcode.cn id=107 lang=cpp
 *
 * [107] Binary Tree Level Order Traversal II
 *
 * https://leetcode.cn/problems/binary-tree-level-order-traversal-ii/description/
 *
 * algorithms
 * Medium (71.69%)
 * Likes:    607
 * Dislikes: 0
 * Total Accepted:    228.7K
 * Total Submissions: 319.1K
 * Testcase Example:  '[3,9,20,null,null,15,7]'
 *
 * Given the root of a binary tree, return the bottom-up level order traversal
 * of its nodes' values. (i.e., from left to right, level by level from leaf to
 * root).
 *
 *
 * Example 1:
 *
 *
 * Input: root = [3,9,20,null,null,15,7]
 * Output: [[15,7],[9,20],[3]]
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
 * -1000 <= Node.val <= 1000
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
  vector<vector<int>> levelOrderBottom(TreeNode *root) {
    return levelOrderBottomBFS(root);
  }

  vector<vector<int>> levelOrderBottomBFS(TreeNode *root) {
    if (nullptr == root) {
      return {};
    }

    vector<vector<int>> level_order_bottom{};
    vector<int> cur_level{};
    stack<vector<int>> level_stack{};

    queue<TreeNode *> node_queue{};
    node_queue.emplace(root);
    node_queue.emplace(nullptr);

    while (false == node_queue.empty()) {
      const auto node{node_queue.front()};
      node_queue.pop();

      // A level is up.
      if (nullptr == node) {
        level_stack.emplace(cur_level);
        cur_level.resize(0);

        if (node_queue.size() > 0) {
          node_queue.emplace(nullptr);
        }
      } else {
        cur_level.emplace_back(node->val);

        if (node->left != nullptr) {
          node_queue.emplace(node->left);
        }
        if (node->right != nullptr) {
          node_queue.emplace(node->right);
        }
      }
    }

    // Pour out.
    while (false == level_stack.empty()) {
      level_order_bottom.emplace_back(level_stack.top());
      level_stack.pop();
    }

    return level_order_bottom;
  }
};
// @lc code=end
