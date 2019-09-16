#include <bits/stdc++.h>
#include <iostream>
#include <limits>
#include <string>
#include <unordered_map>
#include <vector>

struct my_comparator {
  // queue elements are vectors so we need to compare those
  bool operator()(std::pair<std::vector<int>, int> const &a,
                  std::pair<std::vector<int>, int> const &b) const {

    // reverse sort puts the lowest value at the top
    return a.second > b.second;
  }
};

void print(std::vector<int> const &input) {
  for (int i = 0; i < input.size(); i++) {
    std::cout << input.at(i) << ' ';
  }
  std::cout << std::endl;
}

using my_priority_queue =
    std::priority_queue<std::pair<std::vector<int>, int>,
                        std::vector<std::pair<std::vector<int>, int>>,
                        my_comparator>;
int main() {

  std::vector<int> a = {1, 3, 4};
  std::vector<int> b = {1, 3, 5};

  my_priority_queue mpq;
  mpq.push(std::make_pair(a, 1));
  mpq.push(std::make_pair(b, 2));

  auto u = mpq.top();

  print(u.first);
};
