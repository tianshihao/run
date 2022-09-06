/*
 * @lc app=leetcode.cn id=101 lang=cpp
 *
 * [101] Symmetric Tree
 *
 * https://leetcode.cn/problems/symmetric-tree/description/
 *
 * algorithms
 * Easy (58.08%)
 * Likes:    2037
 * Dislikes: 0
 * Total Accepted:    650.9K
 * Total Submissions: 1.1M
 * Testcase Example:  '[1,2,2,3,4,4,3]'
 *
 * Given the root of a binary tree, check whether it is a mirror of itself
 * (i.e., symmetric around its center).
 *
 *
 * Example 1:
 *
 *
 * Input: root = [1,2,2,3,4,4,3]
 * Output: true
 *
 *
 * Example 2:
 *
 *
 * Input: root = [1,2,2,null,3,null,3]
 * Output: false
 *
 *
 *
 * Constraints:
 *
 *
 * The number of nodes in the tree is in the range [1, 1000].
 * -100 <= Node.val <= 100
 *
 *
 *
 * Follow up: Could you solve it both recursively and iteratively?
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
  bool isSymmetric(TreeNode *root) {
    if (nullptr == root) {
      return true;
    }

    return isSymmetricRecursively(root->left, root->right);
  }

  bool isSymmetricRecursively(TreeNode *left, TreeNode *right) {
    if (nullptr == left && nullptr == right) {
      return true;
    } else if (nullptr == left || nullptr == right) {
      return false;
    } else if (left->val != right->val) {
      return false;
    } else {
      return isSymmetricRecursively(left->left, right->right) &&
             isSymmetricRecursively(left->right, right->left);
    }
  }
};
// @lc code=end
