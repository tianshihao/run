/*
 * @lc app=leetcode.cn id=110 lang=cpp
 *
 * [110] Balanced Binary Tree
 *
 * https://leetcode.cn/problems/balanced-binary-tree/description/
 *
 * algorithms
 * Easy (57.25%)
 * Likes:    1091
 * Dislikes: 0
 * Total Accepted:    394.9K
 * Total Submissions: 689.7K
 * Testcase Example:  '[3,9,20,null,null,15,7]'
 *
 * Given a binary tree, determine if it is height-balanced.
 *
 * For this problem, a height-balanced binary tree is defined as:
 *
 *
 * a binary tree in which the left and right subtrees of every node differ in
 * height by no more than 1.
 *
 *
 *
 * Example 1:
 *
 *
 * Input: root = [3,9,20,null,null,15,7]
 * Output: true
 *
 *
 * Example 2:
 *
 *
 * Input: root = [1,2,2,3,3,null,null,4,4]
 * Output: false
 *
 *
 * Example 3:
 *
 *
 * Input: root = []
 * Output: true
 *
 *
 *
 * Constraints:
 *
 *
 * The number of nodes in the tree is in the range [0, 5000].
 * -10^4 <= Node.val <= 10^4
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
 private:
  bool ans{true};

 public:
  bool isBalanced(TreeNode *root) {
    checkBlanced(root);
    return ans;
  }

  int checkBlanced(TreeNode *root) {
    if (nullptr == root) {
      return 0;
    }
    if (!ans) {
      return 0;
    }

    int left_subtree{checkBlanced(root->left)};
    int right_subtree{checkBlanced(root->right)};

    if (abs(left_subtree - right_subtree) > 1) {
      ans = false;
    }

    return max(left_subtree, right_subtree) + 1;
  }
};
// @lc code=end
