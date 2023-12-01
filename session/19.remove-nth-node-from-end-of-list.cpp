/*
 * @lc app=leetcode.cn id=19 lang=cpp
 *
 * [19] Remove Nth Node From End of List
 *
 * https://leetcode.cn/problems/remove-nth-node-from-end-of-list/description/
 *
 * algorithms
 * Medium (46.80%)
 * Likes:    2771
 * Dislikes: 0
 * Total Accepted:    1.3M
 * Total Submissions: 2.7M
 * Testcase Example:  '[1,2,3,4,5]\n2'
 *
 * Given the head of a linked list, remove the n^th node from the end of the
 * list and return its head.
 *
 *
 * Example 1:
 *
 *
 * Input: head = [1,2,3,4,5], n = 2
 * Output: [1,2,3,5]
 *
 *
 * Example 2:
 *
 *
 * Input: head = [1], n = 1
 * Output: []
 *
 *
 * Example 3:
 *
 *
 * Input: head = [1,2], n = 1
 * Output: [1]
 *
 *
 *
 * Constraints:
 *
 *
 * The number of nodes in the list is sz.
 * 1 <= sz <= 30
 * 0 <= Node.val <= 100
 * 1 <= n <= sz
 *
 *
 *
 * Follow up: Could you do this in one pass?
 *
 */

// @lc code=start
// struct ListNode {
//   int val;
//   ListNode *next;
//   ListNode() : val(0), next(nullptr) {}
//   ListNode(int x) : val(x), next(nullptr) {}
//   ListNode(int x, ListNode *next) : val(x), next(next) {}
// };

class Solution {
 public:
  ListNode *removeNthFromEnd(ListNode *head, int n) {
    auto length{getLength(head)};
    auto dummy{new ListNode(0, head)};
    auto p{dummy};
    auto step{length - n};

    while (0 < step--) {
      p = p->next;
    }
    if (nullptr != p->next) {
      p->next = p->next->next;
    } else {
      p->next = nullptr;
    }

    return dummy->next;
  }

  int getLength(ListNode *head) {
    int len{0};
    while (nullptr != head) {
      ++len;
      head = head->next;
    }
    return len;
  }
};
// @lc code=end
