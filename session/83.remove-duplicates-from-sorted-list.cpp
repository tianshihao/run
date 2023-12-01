/*
 * @lc app=leetcode.cn id=83 lang=cpp
 *
 * [83] Remove Duplicates from Sorted List
 *
 * https://leetcode.cn/problems/remove-duplicates-from-sorted-list/description/
 *
 * algorithms
 * Easy (53.22%)
 * Likes:    1076
 * Dislikes: 0
 * Total Accepted:    636.6K
 * Total Submissions: 1.2M
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
    auto p{head};

    while (nullptr != p) {
      if (nullptr != p->next) {
        if (p->val == p->next->val) {
          p->next = p->next->next;
        } else {
          p = p->next;
        }
      } else {
        p = p->next;
      }
    }

    return head;
  }
};
// @lc code=end
