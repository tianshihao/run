/*
 * @lc app=leetcode.cn id=82 lang=cpp
 *
 * [82] Remove Duplicates from Sorted List II
 *
 * https://leetcode.cn/problems/remove-duplicates-from-sorted-list-ii/description/
 *
 * algorithms
 * Medium (53.62%)
 * Likes:    1218
 * Dislikes: 0
 * Total Accepted:    380.3K
 * Total Submissions: 709.3K
 * Testcase Example:  '[1,2,3,3,4,4,5]'
 *
 * Given the head of a sorted linked list, delete all nodes that have duplicate
 * numbers, leaving only distinct numbers from the original list. Return the
 * linked list sorted as well.
 *
 *
 * Example 1:
 *
 *
 * Input: head = [1,2,3,3,4,4,5]
 * Output: [1,2,5]
 *
 *
 * Example 2:
 *
 *
 * Input: head = [1,1,1,2,3]
 * Output: [2,3]
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
struct ListNode {
  int val;
  ListNode* next;
  ListNode() : val(0), next(nullptr) {}
  ListNode(int x) : val(x), next(nullptr) {}
  ListNode(int x, ListNode* next) : val(x), next(next) {}
};

class Solution {
 public:
  ListNode* deleteDuplicates(ListNode* head) {
    auto dummy{new ListNode(0, head)};
    auto prev{dummy};
    auto p{head};

    while (nullptr != p) {
      if (nullptr != p->next && p->val == p->next->val) {
        while (nullptr != p->next && p->val == p->next->val) {
          p = p->next;
        }
        prev->next = p->next;
      } else {
        prev = prev->next;
      }
      p = p->next;
    }

    return dummy->next;
  }
};
// @lc code=end
