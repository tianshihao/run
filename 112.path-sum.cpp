/*
 * @lc app=leetcode.cn id=112 lang=cpp
 *
 * [112] Path Sum
 *
 * https://leetcode.cn/problems/path-sum/description/
 *
 * algorithms
 * Easy (53.44%)
 * Likes:    961
 * Dislikes: 0
 * Total Accepted:    431.4K
 * Total Submissions: 807.3K
 * Testcase Example:  '[5,4,8,11,null,13,4,7,2,null,null,null,1]\n22'
 *
 * Given the root of a binary tree and an integer targetSum, return true if the
 * tree has a root-to-leaf path such that adding up all the values along the
 * path equals targetSum.
 *
 * A leaf is a node with no children.
 *
 *
 * Example 1:
 *
 *
 * Input: root = [5,4,8,11,null,13,4,7,2,null,null,null,1], targetSum = 22
 * Output: true
 * Explanation: The root-to-leaf path with the target sum is shown.
 *
 *
 * Example 2:
 *
 *
 * Input: root = [1,2,3], targetSum = 5
 * Output: false
 * Explanation: There two root-to-leaf paths in the tree:
 * (1 --> 2): The sum is 3.
 * (1 --> 3): The sum is 4.
 * There is no root-to-leaf path with sum = 5.
 *
 *
 * Example 3:
 *
 *
 * Input: root = [], targetSum = 0
 * Output: false
 * Explanation: Since the tree is empty, there are no root-to-leaf paths.
 *
 *
 *
 * Constraints:
 *
 *
 * The number of nodes in the tree is in the range [0, 5000].
 * -1000 <= Node.val <= 1000
 * -1000 <= targetSum <= 1000
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
  bool hasPathSum(TreeNode *root, int target_sum) {
    return hasPathSumRecursively(root, 0, target_sum);
  }

  bool hasPathSumRecursively(TreeNode *root, int cur_sum, int target_sum) {
    if (nullptr == root) {
      return false;
    }

    cur_sum += root->val;

    if (cur_sum == target_sum && nullptr == root->left &&
        nullptr == root->right) {
      return true;
    }

    return hasPathSumRecursively(root->left, cur_sum, target_sum) ||
           hasPathSumRecursively(root->right, cur_sum, target_sum);
  }
};
// @lc code=end
