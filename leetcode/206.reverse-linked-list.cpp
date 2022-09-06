/*
 * @lc app=leetcode.cn id=206 lang=cpp
 *
 * [206] Reverse Linked List
 *
 * https://leetcode.cn/problems/reverse-linked-list/description/
 *
 * algorithms
 * Easy (73.17%)
 * Likes:    2638
 * Dislikes: 0
 * Total Accepted:    1.1M
 * Total Submissions: 1.5M
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
  ListNode* reverseList(ListNode* head) {
    ListNode* prev{nullptr};
    while (head) {
      // backup head.
      ListNode* next{head->next};
      // head point to prev.
      head->next = prev;
      // update prev.
      prev = head;
      // restore head.
      head = next;
    }

    return prev;
  }
};

// int main(int argc, char** argv) {
//   ListNode node1(1);
//   ListNode node2(2);
//   ListNode node3(3);
//   ListNode node4(4);
//   ListNode node5(5);
//   node1.next = &node2;
//   node2.next = &node3;
//   node3.next = &node4;
//   node4.next = &node5;

//   Solution s;
//   s.reverseList(&node1);

//   return 0;
// }

// @lc code=end
