/*
 * @lc app=leetcode.cn id=25 lang=cpp
 *
 * [25] Reverse Nodes in k-Group
 *
 * https://leetcode.cn/problems/reverse-nodes-in-k-group/description/
 *
 * algorithms
 * Hard (67.67%)
 * Likes:    1772
 * Dislikes: 0
 * Total Accepted:    388.1K
 * Total Submissions: 573.5K
 * Testcase Example:  '[1,2,3,4,5]\n2'
 *
 * Given the head of a linked list, reverse the nodes of the list k at a time,
 * and return the modified list.
 *
 * k is a positive integer and is less than or equal to the length of the
 * linked list. If the number of nodes is not a multiple of k then left-out
 * nodes, in the end, should remain as it is.
 *
 * You may not alter the values in the list's nodes, only nodes themselves may
 * be changed.
 *
 *
 * Example 1:
 *
 *
 * Input: head = [1,2,3,4,5], k = 2
 * Output: [2,1,4,3,5]
 *
 *
 * Example 2:
 *
 *
 * Input: head = [1,2,3,4,5], k = 3
 * Output: [3,2,1,4,5]
 *
 *
 *
 * Constraints:
 *
 *
 * The number of nodes in the list is n.
 * 1 <= k <= n <= 5000
 * 0 <= Node.val <= 1000
 *
 *
 *
 * Follow-up: Can you solve the problem in O(1) extra memory space?
 *
 */

// @lc code=start
#include <bits/stdc++.h>
using namespace std;

struct ListNode {
  int val;
  ListNode* next;
  ListNode() : val(0), next(nullptr) {}
  ListNode(int x) : val(x), next(nullptr) {}
  ListNode(int x, ListNode* next) : val(x), next(next) {}
};

class Solution {
 public:
  ListNode* reverseKGroup(ListNode* head, int k) {
    // Always give linked list a dummy head.
    ListNode* dummy{new ListNode{0, head}};

    //   Previous interval    Next interval
    // ... -> e -> f -> g] -> [h -> i -> j -> ...
    //                  ⬆      ⬆
    //      end_of_last_k      start_of_next_k

    // Point to the last node of the previous k nodes.
    ListNode* end_of_prev_k{dummy};
    // Point to the first node of the next k nodes.
    ListNode* start_of_next_k{dummy->next};

    // Loop all time.
    while (true) {
      // Cursor move on linked list.
      ListNode* cursor{start_of_next_k};
      // Move forward k nodes.
      for (int i{0}; i < k; ++i) {
        // The nodes remain are less than k, return. This is bound to happen!
        if (nullptr == cursor) {
          return dummy->next;
        }
        cursor = cursor->next;
      }

      // Reverse k node. Make curr point back to prev.

      // Workers.
      ListNode *curr{start_of_next_k}, *prev{end_of_prev_k};

      // Do k times of the order reversing.
      for (int i{0}; i < k; ++i) {
        // 1. Store the next.
        ListNode* the_next{curr->next};

        // 2. Reverse.
        curr->next = prev;

        // 3. Move forward.
        prev = curr;
        curr = the_next;
      }

      // ! Inlay the reversed sub linked list in to the origin linked list.
      start_of_next_k->next = curr;
      end_of_prev_k->next = prev;

      // Markers moving forward.
      end_of_prev_k = start_of_next_k;
      start_of_next_k = curr;
    }

    // Exactly ends.
    return dummy->next;
  }
};
// @lc code=end
