/*
 * @lc app=leetcode.cn id=146 lang=cpp
 *
 * [146] LRU Cache
 *
 * https://leetcode.cn/problems/lru-cache/description/
 *
 * algorithms
 * Medium (53.04%)
 * Likes:    2287
 * Dislikes: 0
 * Total Accepted:    380.2K
 * Total Submissions: 716.7K
 * Testcase Example:
 '["LRUCache","put","put","get","put","get","put","get","get","get"]\n' +
  '[[2],[1,1],[2,2],[1],[3,3],[2],[4,4],[1],[3],[4]]'
 *
 * Design a data structure that follows the constraints of a Least Recently
 * Used (LRU) cache.
 *
 * Implement the LRUCache class:
 *
 *
 * LRUCache(int capacity) Initialize the LRU cache with positive size
 * capacity.
 * int get(int key) Return the value of the key if the key exists, otherwise
 * return -1.
 * void put(int key, int value) Update the value of the key if the key exists.
 * Otherwise, add the key-value pair to the cache. If the number of keys
 * exceeds the capacity from this operation, evict the least recently used
 * key.
 *
 *
 * The functions get and put must each run in O(1) average time complexity.
 *
 *
 * Example 1:
 *
 *
 * Input
 * ["LRUCache", "put", "put", "get", "put", "get", "put", "get", "get", "get"]
 * [[2], [1, 1], [2, 2], [1], [3, 3], [2], [4, 4], [1], [3], [4]]
 * Output
 * [null, null, null, 1, null, -1, null, -1, 3, 4]
 *
 * Explanation
 * LRUCache lRUCache = new LRUCache(2);
 * lRUCache.put(1, 1); // cache is {1=1}
 * lRUCache.put(2, 2); // cache is {1=1, 2=2}
 * lRUCache.get(1);    // return 1
 * lRUCache.put(3, 3); // LRU key was 2, evicts key 2, cache is {1=1, 3=3}
 * lRUCache.get(2);    // returns -1 (not found)
 * lRUCache.put(4, 4); // LRU key was 1, evicts key 1, cache is {4=4, 3=3}
 * lRUCache.get(1);    // return -1 (not found)
 * lRUCache.get(3);    // return 3
 * lRUCache.get(4);    // return 4
 *
 *
 *
 * Constraints:
 *
 *
 * 1 <= capacity <= 3000
 * 0 <= key <= 10^4
 * 0 <= value <= 10^5
 * At most 2 * 10^5 calls will be made to get and put.
 *
 *
 */

// @lc code=start
#include <bits/stdc++.h>
using namespace std;

class LRUCache {
 public:
  // Cache.
  list<pair<int, int>> l;
  // Index.
  unordered_map<int, list<pair<int, int>>::iterator> m;
  int size;
  LRUCache(int capacity) { size = capacity; }

  int get(int key) {
    if (m.find(key) == m.end()) {
      return -1;
    }
    // Transfer m[key] into the container l, inserting it at position l.begin().
    // Update recently used.
    l.splice(l.begin(), l, m[key]);
    return m[key]->second;
  }

  void put(int key, int value) {
    // Key exists.
    if (m.find(key) != m.end()) {
      l.splice(l.begin(), l, m[key]);
      m[key]->second = value;
      return;
    }
    // List is full.
    if (l.size() == size) {
      // This is the least recently used key.
      auto delete_key{l.back().first};
      // Delete {key, value}.
      l.pop_back();
      // Erase key.
      m.erase(delete_key);
    }
    // Put new element in the front.
    l.push_front({key, value});
    // Update index.
    m[key] = l.begin();
  }
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */
// @lc code=end
