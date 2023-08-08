/*
Task Description
interval_map<K,V> is a data structure that efficiently associates intervals of
keys of type K with values of type V. Your task is to implement the assign
member function of this data structure, which is outlined below. interval_map<K,
V> is implemented on top of std::map. In case you are not entirely sure which
functions std::map provides, what they do and which guarantees they provide, we
provide an excerpt of the C++ standard here: Each key-value-pair (k,v) in the
std::map means that the value v is associated with the interval from k
(including) to the next key (excluding) in the std::map. Example: the std::map
(0,'A'), (3,'B'), (5,'A') represents the mapping 0 -> 'A' 1 -> 'A' 2 -> 'A' 3 ->
'B' 4 -> 'B' 5 -> 'A' 6 -> 'A' 7 -> 'A'
... all the way to numeric_limits<int>::max()
The representation in the std::map must be canonical, that is, consecutive map
entries must not have the same value: ..., (0,'A'), (3,'A'), ... is not allowed.
Initially, the whole range of K is associated with a given initial value, passed
to the constructor of the interval_map<K,V> data structure. Key type K besides
being copyable and assignable, is less-than comparable via operator< is bounded
below, with the lowest value being std::numeric_limits<K>::lowest() does not
implement any other operations, in particular no equality comparison or
arithmetic operators Value type V besides being copyable and assignable, is
equality-comparable via operator== does not implement any other operations
*/

#include <iostream>
#include <map>
#include <vector>

void IntervalMapTest();

template <typename K, typename V>
class interval_map {
  friend void IntervalMapTest();
  friend void IntervalMapTest1();
  friend void IntervalMapTest2();
  // Value for all keys smaller than the first key in the map.
  V m_valBegin;
  std::map<K, V> m_map;

 public:
  // constructor associates whole range of K with val
  interval_map(V const& val) : m_valBegin(val) {}

  // Assign value val to interval [keyBegin, keyEnd).
  // Overwrite previous values in this interval.
  // Conforming to the C++ Standard Library conventions, the interval
  // includes keyBegin, but excludes keyEnd.
  // If !( keyBegin < keyEnd ), this designates an empty interval,
  // and assign must do nothing.
  void assign(K const& keyBegin, K const& keyEnd, V const& val) {
    // INSERT YOUR SOLUTION HERE
    if (!(keyBegin < keyEnd)) {
      return;
    }

    // The iterator that points to the first element that is greater than or
    // equal to keyBegin, which represents the first interval that considered to
    // be merged.
    auto it{m_map.lower_bound(keyBegin)};

    // The interval starts from the keyEnd never will be merged, so backup it.
    auto backup{this->operator[](keyEnd)};

    // Start to merge.

    // If an interval could be merged, then erase it.
    while ((it != m_map.end()) && (it->first < keyEnd)) {
      it = m_map.erase(it);
    }

    // No interval could be merged.

    // Then set the new interval.
    // m_map[keyBegin] = val;
    m_map.insert_or_assign(keyEnd, backup);
    // Update the old interval.
    // m_map[keyEnd] = backup;
    m_map.insert_or_assign(keyEnd, backup);

    // Delete the adjacent duplicated intervals.
    // Maybe optional?
    auto it1{m_map.begin()};
    auto it2{m_map.begin()};
    ++it2;
    while (it2 != m_map.end()) {
      if (it1->second == it2->second) {
        it2 = m_map.erase(it2);
      } else {
        ++it1;
        ++it2;
      }
    }
  }

  // look-up of the value associated with key
  V const& operator[](K const& key) const {
    auto it = m_map.upper_bound(key);
    // The key is greater than all keys, or the map is empty.
    if (it == m_map.begin()) {
      return m_valBegin;
    } else {
      return (--it)->second;
    }
  }
};

void IntervalMapTest1() {
  interval_map<int, char> m('A');

  m.assign(1, 10, 'B');

  for (auto const& [k, v] : m.m_map) {
    std::cout << k << " " << v << std::endl;
  }
  std::cout << std::endl << std::endl;

  m.assign(2, 5, 'C');

  std::vector<char> res;
  std::vector<char> ans{'A', 'A', 'A', 'B', 'C', 'C', 'C',
                        'B', 'B', 'B', 'B', 'B', 'A', 'A'};

  for (int i{-2}; i < 12; ++i) {
    res.push_back(m[i]);
  }

  for (int i{0}; i < res.size(); ++i) {
    std::cout << "res: " << res[i] << " ans: " << ans[i] << std::endl;
  }
}

void IntervalMapTest2() {
  interval_map<int, char> m('A');

  // m.m_map = {{1, 'B'}, {5, 'A'}, {8, 'B'}};
  // m.assign(2, 7, 'B');

  // m.m_map = {{1, 'B'}, {5, 'A'}, {8, 'B'}, {10, 'A'}};
  // m.assign(-8, 24, 'B');

  m.m_map = {{1, 'B'}, {5, 'C'}, {8, 'D'}, {16, 'E'}, {21, 'A'}};
  m.assign(-8, -3, 'E');

  // m.m_map = {{1, 'B'}, {5, 'C'}, {8, 'D'}, {16, 'E'}, {21, 'B'}};
  // m.assign(-4, 9, 'B');

  for (auto const& [k, v] : m.m_map) {
    std::cout << k << " " << v << std::endl;
  }
}

void IntervalMapTest() {
  // IntervalMapTest1();
  IntervalMapTest2();
  // INSERT YOUR SOLUTION HERE
}

// Many solutions we receive are incorrect. Consider using a randomized test
// to discover the cases that your implementation does not handle correctly.
// We recommend to implement a test function that tests the functionality of
// the interval_map, for example using a map of int intervals to char.

int main(int argc, char** argv) {
  IntervalMapTest();
  return 0;
}
