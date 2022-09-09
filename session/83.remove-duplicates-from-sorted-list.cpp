/*
 * @lc app=leetcode.cn id=83 lang=cpp
 *
 * [83] Remove Duplicates from Sorted List
 *
 * https://leetcode.cn/problems/remove-duplicates-from-sorted-list/description/
 *
 * algorithms
 * Easy (53.51%)
 * Likes:    825
 * Dislikes: 0
 * Total Accepted:    458.9K
 * Total Submissions: 857.5K
 * Testcase Example:  '[1,1,2]'
 *
 * Given the head of a sorted linked list, delete all duplicates such that each
 * element appears only once. Return the linked list sorted as well.
 *
 *
 * Example 1:
 *
 *
 * Input: head = [1,1,2]
 * Output: [1,2]
 *
 *
 * Example 2:
 *
 *
 * Input: head = [1,1,2,3,3]
 * Output: [1,2,3]
 *
 *
 *
 * Constraints:
 *
 *
 * The number of nodes in the list is in the range [0, 300].
 * -100 <= Node.val <= 100
 * The list is guaranteed to be sorted in ascending order.
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
  ListNode* deleteDuplicates(ListNode* head) {
    if (nullptr == head) {
      return nullptr;
    }
    ListNode* p{head};
    ListNode* q{head->next};
    while (q) {
      if (p->val == q->val) {
        ListNode* tmp{q->next};
        p->next = tmp;
        // delete q;
        q = tmp;
      } else {
        q = q->next;
        p = p->next;
      }
    }
    return head;
  }
};
// @lc code=end
