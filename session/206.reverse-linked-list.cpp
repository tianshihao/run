/*
 * @lc app=leetcode.cn id=206 lang=cpp
 *
 * [206] Reverse Linked List
 *
 * https://leetcode.cn/problems/reverse-linked-list/description/
 *
 * algorithms
 * Easy (73.78%)
 * Likes:    3455
 * Dislikes: 0
 * Total Accepted:    1.7M
 * Total Submissions: 2.3M
 * Testcase Example:  '[1,2,3,4,5]'
 *
 * Given the head of a singly linked list, reverse the list, and return the
 * reversed list.
 *
 *
 * Example 1:
 *
 *
 * Input: head = [1,2,3,4,5]
 * Output: [5,4,3,2,1]
 *
 *
 * Example 2:
 *
 *
 * Input: head = [1,2]
 * Output: [2,1]
 *
 *
 * Example 3:
 *
 *
 * Input: head = []
 * Output: []
 *
 *
 *
 * Constraints:
 *
 *
 * The number of nodes in the list is the range [0, 5000].
 * -5000 <= Node.val <= 5000
 *
 *
 *
 * Follow up: A linked list can be reversed either iteratively or recursively.
 * Could you implement both?
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
  ListNode* reverseList(ListNode* head) {
    auto dummy{new ListNode(0, head)};
    auto p{head};

    auto old_head{nullptr};
    auto next{p->next};

    while (nullptr != p) {
      dummy->next = p;
      p->next = old_head;

      p = next;
      next = p->next;
      old_head = dummy->next;
    }

    return dummy->next;
  }
};
// @lc code=end
