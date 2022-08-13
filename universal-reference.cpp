#include <bits/stdc++.h>
using namespace std;

template <typename T>
void f(T&& param);

int main(int argc, char** argv) {
  int a{1000};
  auto&& ra{999};

  cout << "rvalue reference of a: " << ra << endl;

  return 0;
}
