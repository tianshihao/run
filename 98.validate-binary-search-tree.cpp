/*
 * @lc app=leetcode.cn id=98 lang=cpp
 *
 * [98] Validate Binary Search Tree
 *
 * https://leetcode.cn/problems/validate-binary-search-tree/description/
 *
 * algorithms
 * Medium (36.39%)
 * Likes:    1694
 * Dislikes: 0
 * Total Accepted:    564.5K
 * Total Submissions: 1.6M
 * Testcase Example:  '[2,1,3]'
 *
 * Given the root of a binary tree, determine if it is a valid binary search
 * tree (BST).
 *
 * A valid BST is defined as follows:
 *
 *
 * The left subtree of a node contains only nodes with keys less than the
 * node's key.
 * The right subtree of a node contains only nodes with keys greater than the
 * node's key.
 * Both the left and right subtrees must also be binary search trees.
 *
 *
 *
 * Example 1:
 *
 *
 * Input: root = [2,1,3]
 * Output: true
 *
 *
 * Example 2:
 *
 *
 * Input: root = [5,1,4,null,null,3,6]
 * Output: false
 * Explanation: The root node's value is 5 but its right child's value is
 * 4.
 *
 *
 *
 * Constraints:
 *
 *
 * The number of nodes in the tree is in the range [1, 10^4].
 * -2^31 <= Node.val <= 2^31 - 1
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
  bool isValidBST(TreeNode *root) {
    vector<int> inorder{};
    stack<TreeNode *> s;
    TreeNode *node{root};

    while (node != nullptr || s.empty() == false) {
      if (node != nullptr) {
        s.push(node);
        node = node->left;
      } else {
        node = s.top();
        s.pop();
        inorder.emplace_back(node->val);
        node = node->right;
      }
    }

    bool is_validate{true};
    for (size_t i{0}; i < inorder.size() - 1; ++i) {
      size_t j{i + 1};
      if (inorder[i] < inorder[j]) {
        continue;
      } else {
        is_validate = false;
        break;
      }
    }

    return is_validate;
  }
};
// @lc code=end
