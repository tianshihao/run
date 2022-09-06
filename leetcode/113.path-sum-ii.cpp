/*
 * @lc app=leetcode.cn id=113 lang=cpp
 *
 * [113] Path Sum II
 *
 * https://leetcode.cn/problems/path-sum-ii/description/
 *
 * algorithms
 * Medium (63.24%)
 * Likes:    810
 * Dislikes: 0
 * Total Accepted:    282K
 * Total Submissions: 445.9K
 * Testcase Example:  '[5,4,8,11,null,13,4,7,2,null,null,5,1]\n22'
 *
 * Given the root of a binary tree and an integer targetSum, return all
 * root-to-leaf paths where the sum of the node values in the path equals
 * targetSum. Each path should be returned as a list of the node values, not
 * node references.
 *
 * A root-to-leaf path is a path starting from the root and ending at any leaf
 * node. A leaf is a node with no children.
 *
 *
 * Example 1:
 *
 *
 * Input: root = [5,4,8,11,null,13,4,7,2,null,null,5,1], targetSum = 22
 * Output: [[5,4,11,2],[5,8,4,5]]
 * Explanation: There are two paths whose sum equals targetSum:
 * 5 + 4 + 11 + 2 = 22
 * 5 + 8 + 4 + 5 = 22
 *
 *
 * Example 2:
 *
 *
 * Input: root = [1,2,3], targetSum = 5
 * Output: []
 *
 *
 * Example 3:
 *
 *
 * Input: root = [1,2], targetSum = 0
 * Output: []
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
 private:
  vector<vector<int>> result{};
  vector<int> path{};

 public:
  vector<vector<int>> pathSum(TreeNode *root, int target_sum) {
    pathSumRecursively(root, path, target_sum);
    return result;
  }

  void pathSumRecursively(TreeNode *root, vector<int> path, int remains) {
    if (nullptr == root) {
      return;
    }

    remains -= root->val;
    path.emplace_back(root->val);

    if (0 == remains && nullptr == root->left && nullptr == root->right) {
      result.emplace_back(path);
      return;
    }

    pathSumRecursively(root->left, path, remains);
    pathSumRecursively(root->right, path, remains);

    return;
  }
};
// @lc code=end
