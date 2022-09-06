/*
 * @lc app=leetcode.cn id=662 lang=cpp
 *
 * [662] Maximum Width of Binary Tree
 *
 * https://leetcode.cn/problems/maximum-width-of-binary-tree/description/
 *
 * algorithms
 * Medium (41.18%)
 * Likes:    392
 * Dislikes: 0
 * Total Accepted:    50.9K
 * Total Submissions: 123.6K
 * Testcase Example:  '[1,3,2,5,3,null,9]'
 *
 * Given the root of a binary tree, return the maximum width of the given
 * tree.
 *
 * The maximum width of a tree is the maximum width among all levels.
 *
 * The width of one level is defined as the length between the end-nodes (the
 * leftmost and rightmost non-null nodes), where the null nodes between the
 * end-nodes that would be present in a complete binary tree extending down to
 * that level are also counted into the length calculation.
 *
 * It is guaranteed that the answer will in the range of a 32-bit signed
 * integer.
 *
 *
 * Example 1:
 *
 *
 * Input: root = [1,3,2,5,3,null,9]
 * Output: 4
 * Explanation: The maximum width exists in the third level with length 4
 * (5,3,null,9).
 *
 *
 * Example 2:
 *
 *
 * Input: root = [1,3,2,5,null,null,9,6,null,7]
 * Output: 7
 * Explanation: The maximum width exists in the fourth level with length 7
 * (6,null,null,null,null,null,7).
 *
 *
 * Example 3:
 *
 *
 * Input: root = [1,3,2,5]
 * Output: 2
 * Explanation: The maximum width exists in the second level with length 2
 * (3,2).
 *
 *
 *
 * Constraints:
 *
 *
 * The number of nodes in the tree is in the range [1, 3000].
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
  int widthOfBinaryTree(TreeNode *root) {
    if (nullptr == root) {
      return 0;
    }
    queue<pair<TreeNode *, long>> q;
    long max_width = 0;

    q.push({root, 1});

    while (!q.empty()) {
      int level_size = q.size();

      long start_pos = q.front().second;
      long end_pos = q.back().second;

      max_width = max(max_width, end_pos - start_pos + 1);

      for (int i = 0; i < level_size; ++i) {
        auto p = q.front();
        q.pop();

        auto node = p.first;
        long pos = p.second;
        long offset_pos = pos - start_pos;

        if (node->left) {
          q.push({node->left, 2 * offset_pos});
        }
        if (node->right) {
          q.push({node->right, 2 * offset_pos + 1});
        }
      }
    }

    return max_width;
  }
};
// @lc code=end
