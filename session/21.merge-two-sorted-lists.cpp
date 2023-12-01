/*
 * @lc app=leetcode.cn id=21 lang=cpp
 *
 * [21] Merge Two Sorted Lists
 *
 * https://leetcode.cn/problems/merge-two-sorted-lists/description/
 *
 * algorithms
 * Easy (66.20%)
 * Likes:    3392
 * Dislikes: 0
 * Total Accepted:    1.6M
 * Total Submissions: 2.4M
 * Testcase Example:  '[1,2,4]\n[1,3,4]'
 *
 * You are given the heads of two sorted linked lists list1 and list2.
 *
 * Merge the two lists into one sorted list. The list should be made by
 * splicing together the nodes of the first two lists.
 *
 * Return the head of the merged linked list.
 *
 *
 * Example 1:
 *
 *
 * Input: list1 = [1,2,4], list2 = [1,3,4]
 * Output: [1,1,2,3,4,4]
 *
 *
 * Example 2:
 *
 *
 * Input: list1 = [], list2 = []
 * Output: []
 *
 *
 * Example 3:
 *
 *
 * Input: list1 = [], list2 = [0]
 * Output: [0]
 *
 *
 *
 * Constraints:
 *
 *
 * The number of nodes in both lists is in the range [0, 50].
 * -100 <= Node.val <= 100
 * Both list1 and list2 are sorted in non-decreasing order.
 *
 *
 */

// @lc code=start
// struct ListNode {
//   int val;
//   ListNode* next;
//   ListNode() : val(0), next(nullptr) {}
//   ListNode(int x) : val(x), next(nullptr) {}
//   ListNode(int x, ListNode* next) : val(x), next(next) {}
// };

class Solution {
 public:
  ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
    if (nullptr == list1 && nullptr == list2) {
      return nullptr;
    } else if (nullptr == list1) {
      return list2;
    } else if (nullptr == list2) {
      return list1;
    } else {
    }

    // insert sort.
    ListNode *p1{list1}, *p2{list2};
    ListNode *dummy{new ListNode()}, *p{dummy};

    while (nullptr != p1 && nullptr != p2) {
      ListNode* new_node{new ListNode()};
      if (p1->val <= p2->val) {
        new_node->val = p1->val;
        p1 = p1->next;
      } else {
        new_node->val = p2->val;
        p2 = p2->next;
      }
      p->next = new_node;
      p = p->next;
    }
    while (nullptr != p1) {
      ListNode* new_node{new ListNode(p1->val)};
      p1 = p1->next;
      p->next = new_node;
      p = p->next;
    }
    while (nullptr != p2) {
      ListNode* new_node{new ListNode(p2->val)};
      p2 = p2->next;
      p->next = new_node;
      p = p->next;
    }

    return dummy->next;
  }
};
// @lc code=end
