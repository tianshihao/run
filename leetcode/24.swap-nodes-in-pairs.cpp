/*
 * @lc app=leetcode.cn id=24 lang=cpp
 *
 * [24] Swap Nodes in Pairs
 *
 * https://leetcode.cn/problems/swap-nodes-in-pairs/description/
 *
 * algorithms
 * Medium (71.14%)
 * Likes:    1534
 * Dislikes: 0
 * Total Accepted:    502.8K
 * Total Submissions: 706.8K
 * Testcase Example:  '[1,2,3,4]'
 *
 * Given a linked list, swap every two adjacent nodes and return its head. You
 * must solve the problem without modifying the values in the list's nodes
 * (i.e., only nodes themselves may be changed.)
 *
 *
 * Example 1:
 *
 *
 * Input: head = [1,2,3,4]
 * Output: [2,1,4,3]
 *
 *
 * Example 2:
 *
 *
 * Input: head = []
 * Output: []
 *
 *
 * Example 3:
 *
 *
 * Input: head = [1]
 * Output: [1]
 *
 *
 *
 * Constraints:
 *
 *
 * The number of nodes in the list is in the range [0, 100].
 * 0 <= Node.val <= 100
 *
 *
 */

// @lc code=start
#include <bits/stdc++.h>
using namespace std;

// struct ListNode {
//   int val;
//   ListNode* next;
//   ListNode() : val(0), next(nullptr) {}
//   ListNode(int x) : val(x), next(nullptr) {}
//   ListNode(int x, ListNode* next) : val(x), next(next) {}
// };

class Solution {
 public:
  ListNode* swapPairs(ListNode* head) {
    // What we manipulate is pointer.
    using NodeLink = ListNode*;
    NodeLink* pointer_to_link{&head};
    NodeLink link_to_current_node{nullptr}, link_to_next_node{nullptr};

    while ((link_to_current_node = *pointer_to_link) &&
           (link_to_next_node = link_to_current_node->next)) {
      // Swap the pair {current_node -> next_node} is easy to understand.
      link_to_current_node->next = link_to_next_node->next;
      link_to_next_node->next = link_to_current_node;
      // Make previous link point to the {next_node -> current_node}.
      // And when first loop, this will ensure the head point to the beginning
      // of new list.
      *pointer_to_link = link_to_next_node;
      // Point to the link after the pair.
      pointer_to_link = &(link_to_current_node->next);
    }

    return head;
  }
};

// @lc code=end
