/*
 * @lc app=leetcode.cn id=19 lang=cpp
 *
 * [19] Remove Nth Node From End of List
 *
 * https://leetcode.cn/problems/remove-nth-node-from-end-of-list/description/
 *
 * algorithms
 * Medium (44.40%)
 * Likes:    2142
 * Dislikes: 0
 * Total Accepted:    865.8K
 * Total Submissions: 1.9M
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
  ListNode* removeNthFromEnd(ListNode* head, int n) {
    if (nullptr == head) {
      return nullptr;
    }
    ListNode dummy(-1, head);
    ListNode *fast{&dummy}, *slow{&dummy};

    while (fast->next && n--) {
      fast = fast->next;
    }

    while (fast->next) {
      fast = fast->next;
      slow = slow->next;
    }

    ListNode* to_be_deleted = slow->next;

    slow->next = slow->next->next;

    delete to_be_deleted;

    return dummy.next;
  }
};
// @lc code=end
