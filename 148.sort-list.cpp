/*
 * @lc app=leetcode.cn id=148 lang=cpp
 *
 * [148] Sort List
 *
 * https://leetcode.cn/problems/sort-list/description/
 *
 * algorithms
 * Medium (66.33%)
 * Likes:    1724
 * Dislikes: 0
 * Total Accepted:    325.3K
 * Total Submissions: 490.4K
 * Testcase Example:  '[4,2,1,3]'
 *
 * Given the head of a linked list, return the list after sorting it in
 * ascending order.
 *
 *
 * Example 1:
 *
 *
 * Input: head = [4,2,1,3]
 * Output: [1,2,3,4]
 *
 *
 * Example 2:
 *
 *
 * Input: head = [-1,5,3,4,0]
 * Output: [-1,0,3,4,5]
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
 * The number of nodes in the list is in the range [0, 5 * 10^4].
 * -10^5 <= Node.val <= 10^5
 *
 *
 *
 * Follow up: Can you sort the linked list in O(n logn) time and O(1) memory
 * (i.e. constant space)?
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
  ListNode* sortList(ListNode* head) {
    if (head == NULL || head->next == NULL) return head;

    ListNode* slow = head;
    ListNode* fast = head->next;

    while (nullptr != fast && nullptr != fast->next) {
      slow = slow->next;
      fast = fast->next->next;
    }
    // divide the list into two parts
    fast = slow->next;
    slow->next = NULL;

    return merge(sortList(head), sortList(fast));
  }

  ListNode* merge(ListNode* l1, ListNode* l2) {
    ListNode dump(0);
    ListNode* cur = &dump;

    while (l1 != NULL && l2 != NULL) {
      if (l1->val < l2->val) {
        cur->next = l1;
        l1 = l1->next;
      } else {
        cur->next = l2;
        l2 = l2->next;
      }

      cur = cur->next;
    }

    if (l1 != NULL)
      cur->next = l1;
    else
      cur->next = l2;

    return dump.next;
  }
};

// int main(int argc, char** argv) {
//   ListNode node4(3);
//   ListNode node3(1, &node4);
//   ListNode node2(2, &node3);
//   ListNode node1(4, &node2);

//   Solution s;
//   s.sortList(&node1);

//   return 0;
// }

// @lc code=end
