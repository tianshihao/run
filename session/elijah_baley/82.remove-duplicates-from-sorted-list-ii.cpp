/*
 * @lc app=leetcode.cn id=82 lang=cpp
 *
 * [82] Remove Duplicates from Sorted List II
 *
 * https://leetcode.cn/problems/remove-duplicates-from-sorted-list-ii/description/
 *
 * algorithms
 * Medium (53.44%)
 * Likes:    947
 * Dislikes: 0
 * Total Accepted:    274.8K
 * Total Submissions: 514.3K
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
  ListNode* deleteDuplicates(ListNode* head) {
    if (nullptr == head) {
      return nullptr;
    }

    ListNode* dummy = new ListNode(numeric_limits<int>::min(), head);

    ListNode* pivot{nullptr};
    ListNode* prev{nullptr};
    ListNode* cur{dummy};
    ListNode* next{dummy->next};
    while (next != nullptr) {
      if (cur->val == next->val) {
        pivot = prev;
        next = next->next;
      } else if (nullptr != pivot) {
        pivot->next = next;
        cur = next;
        next = next->next;
        pivot = nullptr;
      } else {
        prev = cur;
        cur = cur->next;
        next = next->next;
      }
    }

    if (pivot != nullptr) {
      pivot->next = next;
    }

    return dummy->next;
  }
};

// int main(int argc, char** argv) {
//   ListNode* node1 = new ListNode(1);
//   ListNode* node2 = new ListNode(1);
// //   ListNode* node3 = new ListNode(3);
// //   ListNode* node4 = new ListNode(3);
// //   ListNode* node5 = new ListNode(4);
// //   ListNode* node6 = new ListNode(4);
// //   ListNode* node7 = new ListNode(5);
//   node1->next = node2;
// //   node2->next = node3;
// //   node3->next = node4;
// //   node4->next = node5;
// //   node5->next = node6;
// //   node6->next = node7;
//   Solution s;
//   s.deleteDuplicates(node1);

//   return 0;
// }

// @lc code=end
