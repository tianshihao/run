/*
 * @lc app=leetcode.cn id=226 lang=cpp
 *
 * [226] Invert Binary Tree
 *
 * https://leetcode.cn/problems/invert-binary-tree/description/
 *
 * algorithms
 * Easy (79.33%)
 * Likes:    1373
 * Dislikes: 0
 * Total Accepted:    511K
 * Total Submissions: 644.2K
 * Testcase Example:  '[4,2,7,1,3,6,9]'
 *
 * Given the root of a binary tree, invert the tree, and return its root.
 *
 *
 * Example 1:
 *
 *
 * Input: root = [4,2,7,1,3,6,9]
 * Output: [4,7,2,9,6,3,1]
 *
 *
 * Example 2:
 *
 *
 * Input: root = [2,1,3]
 * Output: [2,3,1]
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
  TreeNode *invertTree(TreeNode *root) { return invertTreeRecursively(root); }

  TreeNode *invertTreeRecursively(TreeNode *root) {
    if (root != nullptr) {
      invertTreeRecursively(root->left);
      invertTreeRecursively(root->right);

      TreeNode *tmp{root->left};
      root->left = root->right;
      root->right = tmp;

      return root;
    } else {
      return nullptr;
    }
  }
};
// @lc code=end
