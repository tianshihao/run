/*
 * @lc app=leetcode.cn id=92 lang=cpp
 *
 * [92] Reverse Linked List II
 *
 * https://leetcode.cn/problems/reverse-linked-list-ii/description/
 *
 * algorithms
 * Medium (55.46%)
 * Likes:    1348
 * Dislikes: 0
 * Total Accepted:    319K
 * Total Submissions: 575.1K
 * Testcase Example:  '[1,2,3,4,5]\n2\n4'
 *
 * Given the head of a singly linked list and two integers left and right where
 * left <= right, reverse the nodes of the list from position left to position
 * right, and return the reversed list.
 *
 *
 * Example 1:
 *
 *
 * Input: head = [1,2,3,4,5], left = 2, right = 4
 * Output: [1,4,3,2,5]
 *
 *
 * Example 2:
 *
 *
 * Input: head = [5], left = 1, right = 1
 * Output: [5]
 *
 *
 *
 * Constraints:
 *
 *
 * The number of nodes in the list is n.
 * 1 <= n <= 500
 * -500 <= Node.val <= 500
 * 1 <= left <= right <= n
 *
 *
 *
 * Follow up: Could you do it in one pass?
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
  // Index from 1.
  ListNode* reverseBetween(ListNode* head, int left, int right) {
    ListNode* dummy = new ListNode(0, head);
    ListNode* prev{dummy};
    for (int i = 0; i < left - 1; ++i) {
      prev = prev->next;
    }

    // working pointer.
    ListNode* cur{prev->next};
    // reverse.
    for (int i = 0; i < right - left; ++i) {
      // 1. backup
      //        follow 
      //          ⬇
      // prev -> cur -> node1 -> node2 -> node3 -> ...
      ListNode* follow = prev->next;
      // 2. point to cur next
      // follow -> cur
      //          ⬇
      // prev -> node1 -> node2 -> node3 -> ...
      prev->next = cur->next;
      // 3. insert cur
      //          follow -> cur
      //                    ⬇
      // prev -> node1 -> node2 -> node3 -> ...
      cur->next = cur->next->next;
      // 4. restore
      //                 follow 
      //                   ⬇
      // prev -> node1 -> cur -> node2 -> node3 -> ...
      prev->next->next = follow;
    }

    return dummy->next;
  }
};
// @lc code=end