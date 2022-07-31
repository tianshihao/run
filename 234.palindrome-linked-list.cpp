/*
 * @lc app=leetcode.cn id=234 lang=cpp
 *
 * [234] Palindrome Linked List
 *
 * https://leetcode.cn/problems/palindrome-linked-list/description/
 *
 * algorithms
 * Easy (52.17%)
 * Likes:    1457
 * Dislikes: 0
 * Total Accepted:    475.7K
 * Total Submissions: 911.9K
 * Testcase Example:  '[1,2,2,1]'
 *
 * Given the head of a singly linked list, return true if it is a
 * palindrome.
 *
 *
 * Example 1:
 *
 *
 * Input: head = [1,2,2,1]
 * Output: true
 *
 *
 * Example 2:
 *
 *
 * Input: head = [1,2]
 * Output: false
 *
 *
 *
 * Constraints:
 *
 *
 * The number of nodes in the list is in the range [1, 10^5].
 * 0 <= Node.val <= 9
 *
 *
 *
 * Follow up: Could you do it in O(n) time and O(1) space?
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
  bool isPalindrome(ListNode *head) {
    ListNode *fast{head}, *slow{head};

    while (fast->next && fast->next->next) {
      fast = fast->next->next;
      slow = slow->next;
    }

    ListNode *second_half{slow->next};
    slow->next = nullptr;

    second_half = reverse(second_half);

    while (head && second_half) {
      if (head->val == second_half->val) {
        head = head->next;
        second_half = second_half->next;
      } else {
        return false;
      }
    }

    return true;
  }

  ListNode *reverse(ListNode *root) {
    ListNode *prev{nullptr};
    while (root) {
      ListNode *follow{root->next};
      root->next = prev;
      prev = root;
      root = follow;
    }
    return prev;
  }
};
// @lc code=end
