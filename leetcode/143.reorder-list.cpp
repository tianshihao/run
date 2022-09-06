/*
 * @lc app=leetcode.cn id=143 lang=cpp
 *
 * [143] Reorder List
 *
 * https://leetcode.cn/problems/reorder-list/description/
 *
 * algorithms
 * Medium (64.12%)
 * Likes:    969
 * Dislikes: 0
 * Total Accepted:    197.1K
 * Total Submissions: 307.4K
 * Testcase Example:  '[1,2,3,4]'
 *
 * You are given the head of a singly linked-list. The list can be represented
 * as:
 *
 *
 * L0 → L1 → … → Ln - 1 → Ln
 *
 *
 * Reorder the list to be on the following form:
 *
 *
 * L0 → Ln → L1 → Ln - 1 → L2 → Ln - 2 → …
 *
 *
 * You may not modify the values in the list's nodes. Only nodes themselves may
 * be changed.
 *
 *
 * Example 1:
 *
 *
 * Input: head = [1,2,3,4]
 * Output: [1,4,2,3]
 *
 *
 * Example 2:
 *
 *
 * Input: head = [1,2,3,4,5]
 * Output: [1,5,2,4,3]
 *
 *
 *
 * Constraints:
 *
 *
 * The number of nodes in the list is in the range [1, 5 * 10^4].
 * 1 <= Node.val <= 1000
 *
 *
 */

// @lc code=start
#include <bits/stdc++.h>
using namespace std;

// struct ListNode {
//   int val;
//   ListNode *next;
//   ListNode() : val(0), next(nullptr) {}
//   ListNode(int x) : val(x), next(nullptr) {}
//   ListNode(int x, ListNode *next) : val(x), next(next) {}
// };

class Solution {
 public:
  void reorderList(ListNode *head) {
    if (nullptr == head) {
      return;
    }

    // 1. find post half list.
    ListNode *fast{head}, *slow{head};
    while (fast->next && fast->next->next) {
      fast = fast->next->next;
      slow = slow->next;
    }
    ListNode *backup{slow->next};
    slow->next = nullptr;

    // 2. reverse the post half list.
    ListNode *second_half{reverse(backup)};

    // 3. merge two list.
    while (head && second_half) {
      ListNode *head_follow{head->next};
      ListNode *second_follow{second_half->next};

      second_half->next = head_follow;
      head->next = second_half;

      head = head_follow;
      second_half = second_follow;
    }

    // 4. process bad case.
    if (head && head->next) {
      head->next->next = nullptr;
    }
  }

  ListNode *reverse(ListNode *head) {
    ListNode *prev{nullptr};
    while (head) {
      ListNode *follow{head->next};
      head->next = prev;
      prev = head;
      head = follow;
    }
    return prev;
  }
};

// int main(int argc, char const *argv[]) {
//   // ListNode node5(5);
//   // ListNode node4(4, &node5);
//   ListNode node4(4);
//   ListNode node3(3, &node4);
//   ListNode node2(2, &node3);
//   ListNode node1(1, &node2);

//   Solution s;
//   s.reorderList(&node1);

//   return 0;
// }

// @lc code=end
