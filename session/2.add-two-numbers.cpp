/*
 * @lc app=leetcode.cn id=2 lang=cpp
 *
 * [2] Add Two Numbers
 *
 * https://leetcode.cn/problems/add-two-numbers/description/
 *
 * algorithms
 * Medium (43.01%)
 * Likes:    10275
 * Dislikes: 0
 * Total Accepted:    1.9M
 * Total Submissions: 4.5M
 * Testcase Example:  '[2,4,3]\n[5,6,4]'
 *
 * You are given two non-empty linked lists representing two non-negative
 * integers. The digits are stored in reverse order, and each of their nodes
 * contains a single digit. Add the two numbers and return the sum as a linked
 * list.
 *
 * You may assume the two numbers do not contain any leading zero, except the
 * number 0 itself.
 *
 *
 * Example 1:
 *
 *
 * Input: l1 = [2,4,3], l2 = [5,6,4]
 * Output: [7,0,8]
 * Explanation: 342 + 465 = 807.
 *
 *
 * Example 2:
 *
 *
 * Input: l1 = [0], l2 = [0]
 * Output: [0]
 *
 *
 * Example 3:
 *
 *
 * Input: l1 = [9,9,9,9,9,9,9], l2 = [9,9,9,9]
 * Output: [8,9,9,9,0,0,0,1]
 *
 *
 *
 * Constraints:
 *
 *
 * The number of nodes in each linked list is in the range [1, 100].
 * 0 <= Node.val <= 9
 * It is guaranteed that the list represents a number that does not have
 * leading zeros.
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
  ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
    if (nullptr == l1 && nullptr == l2) {
      return nullptr;
    }
    if (nullptr == l1) {
      return l2;
    }
    if (nullptr == l2) {
      return l1;
    }

    auto sum{l1->val + l2->val};
    auto p{new ListNode(sum % 10)};
    p->next = addTwoNumbers(l1->next, l2->next);
    if (sum >= 10) {
      p->next = addTwoNumbers(p->next, new ListNode(1));
    }
    return p;
  }
};

// @lc code=end
