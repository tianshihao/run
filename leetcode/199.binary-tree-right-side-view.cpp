/*
 * @lc app=leetcode.cn id=199 lang=cpp
 *
 * [199] Binary Tree Right Side View
 *
 * https://leetcode.cn/problems/binary-tree-right-side-view/description/
 *
 * algorithms
 * Medium (65.65%)
 * Likes:    732
 * Dislikes: 0
 * Total Accepted:    226.1K
 * Total Submissions: 344.4K
 * Testcase Example:  '[1,2,3,null,5,null,4]'
 *
 * Given the root of a binary tree, imagine yourself standing on the right side
 * of it, return the values of the nodes you can see ordered from top to
 * bottom.
 *
 *
 * Example 1:
 *
 *
 * Input: root = [1,2,3,null,5,null,4]
 * Output: [1,3,4]
 *
 *
 * Example 2:
 *
 *
 * Input: root = [1,null,3]
 * Output: [1,3]
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
 * The number of nodes in the tree is in the range [0, 100].
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
  vector<int> rightSideView(TreeNode *root) {
    if (nullptr == root){
      return {};
    }
    queue<TreeNode *> q;
    q.push(root);
    q.push(nullptr);
    vector<int> result{};
    TreeNode *prev{nullptr};

    while (!q.empty()) {
      TreeNode *node{q.front()};
      q.pop();

      if (nullptr == node) {
        // add next level end mark when current level is end
        if (q.size() > 0) {
          q.push(nullptr);
        }
        result.emplace_back(prev->val);
      } else {
        prev = node;
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
