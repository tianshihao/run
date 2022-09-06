/*
 * @lc app=leetcode.cn id=105 lang=cpp
 *
 * [105] Construct Binary Tree from Preorder and Inorder Traversal
 *
 * https://leetcode.cn/problems/construct-binary-tree-from-preorder-and-inorder-traversal/description/
 *
 * algorithms
 * Medium (71.25%)
 * Likes:    1675
 * Dislikes: 0
 * Total Accepted:    394.5K
 * Total Submissions: 553.8K
 * Testcase Example:  '[3,9,20,15,7]\n[9,3,15,20,7]'
 *
 * Given two integer arrays preorder and inorder where preorder is the preorder
 * traversal of a binary tree and inorder is the inorder traversal of the same
 * tree, construct and return the binary tree.
 *
 *
 * Example 1:
 *
 *
 * Input: preorder = [3,9,20,15,7], inorder = [9,3,15,20,7]
 * Output: [3,9,20,null,null,15,7]
 *
 *
 * Example 2:
 *
 *
 * Input: preorder = [-1], inorder = [-1]
 * Output: [-1]
 *
 *
 *
 * Constraints:
 *
 *
 * 1 <= preorder.length <= 3000
 * inorder.length == preorder.length
 * -3000 <= preorder[i], inorder[i] <= 3000
 * preorder and inorder consist of unique values.
 * Each value of inorder also appears in preorder.
 * preorder is guaranteed to be the preorder traversal of the tree.
 * inorder is guaranteed to be the inorder traversal of the tree.
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
  TreeNode *buildTree(vector<int> &preorder, vector<int> &inorder) {
    return preinCreate(preorder, 0, preorder.size() - 1, inorder, 0,
                       inorder.size() - 1);
  }

  TreeNode *preinCreate(vector<int> &preorder, int pre_l, int pre_r,
                        vector<int> &inorder, int in_l, int in_r) {
    TreeNode *root = new TreeNode;
    root->val = preorder[pre_l];

    int root_idx = in_l;
    while (inorder[root_idx] != root->val) {
      ++root_idx;
    }

    int lchild_len = root_idx - in_l;
    int rchild_len = in_r - root_idx;

    if (lchild_len > 0) {
      root->left = preinCreate(preorder, pre_l + 1, pre_l + lchild_len, inorder,
                               in_l, in_l + lchild_len - 1);
    } else {
      root->left = nullptr;
    }

    if (rchild_len > 0) {
      root->right = preinCreate(preorder, pre_r - rchild_len + 1, pre_r,
                                inorder, in_r - rchild_len + 1, in_r);
    } else {
      root->right = nullptr;
    }

    return root;
  }
};
// @lc code=end
