/*
 * @lc app=leetcode.cn id=102 lang=cpp
 *
 * [102] Binary Tree Level Order Traversal
 *
 * https://leetcode.cn/problems/binary-tree-level-order-traversal/description/
 *
 * algorithms
 * Medium (64.95%)
 * Likes:    1400
 * Dislikes: 0
 * Total Accepted:    627.2K
 * Total Submissions: 965.7K
 * Testcase Example:  '[3,9,20,null,null,15,7]'
 *
 * Given the root of a binary tree, return the level order traversal of its
 * nodes' values. (i.e., from left to right, level by level).
 *
 *
 * Example 1:
 *
 *
 * Input: root = [3,9,20,null,null,15,7]
 * Output: [[3],[9,20],[15,7]]
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
  vector<vector<int>> levelOrder(TreeNode *root) {
    if (nullptr == root) {
      return {};
    }
    queue<TreeNode *> q;
    vector<vector<int>> result{};

    q.push(root);
    q.push(nullptr);
    vector<int> cur_level{};
    while (!q.empty()) {
      TreeNode *node{q.front()};
      q.pop();

      // a level is end
      if (nullptr == node) {
        result.push_back(cur_level);
        cur_level.resize(0);
        // add next level end mark when current level is end
        if (q.size() > 0) {
          q.push(nullptr);
        }
      } else {
        cur_level.push_back(node->val);
        // add next level into queue
        if (node->left) {
          q.push(node->left);
        }
        if (node->right) {
          q.push(node->right);
        }
      }
    }
    return result;
  }
};
// @lc code=end
