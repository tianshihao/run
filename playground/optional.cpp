#include <iostream>
#include <map>
#include <string>

int main() {
  std::map<int, std::string> m;

  m.emplace(1, "one");
  m.emplace(3, "three");
  m.emplace(2, "two");

  std::for_each(m.begin(), m.end(), [](const auto& p) {
    std::cout << p.first << " => " << p.second << '\n';
  });
  return 0;
}