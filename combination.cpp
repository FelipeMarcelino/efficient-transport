// C++ program to display all permutations
// of an array using STL in C++

#include <bits/stdc++.h>
#include <functional>
#include <iostream>
#include <limits>
#include <numeric>
#include <vector>
using namespace std;

// VectorHasher is a struct that transform a vector 1D into a hash key for
// unordered_map 1

std::unordered_map<int, int> graph;
// Function to display the array
void display(std::vector<int> a, int n) {
  for (int i = 0; i < n; i++) {
    cout << a[i] << " ";
  }
  cout << endl;
}

class uint32_vector_hasher {
public:
  std::size_t operator()(std::vector<int> const &vec) const {
    std::size_t seed = vec.size();
    for (auto &i : vec) {
      seed ^= i + 0x9e3779b9 + (seed << 6) + (seed >> 2);
    }
    return seed;
  };
};

// Function to find the permutations
void findPermutations(std::vector<int> a, int n) {

  // Sort the given array
  std::sort(a.begin(), a.end());
  int contador = 0;

  uint32_vector_hasher hasher;

  auto key_first = hasher(a);

  // int key_first = std::inner_product(a.begin(), a.end(), total_n.begin(),
  // 0);

  graph[key_first] = std::numeric_limits<int>::max();

  // Find all possible permutations
  do {
    // display(a, n);

    auto key_g = hasher(a);

    graph[key_g] = std::numeric_limits<int>::max();
    contador += 1;
  } while (next_permutation(a.begin(), a.end()));

  std::cout << contador << std::endl;
  std::cout << graph.size() << std::endl;
}

// Driver code
int main() {

  std::vector<int> a = {10, 20, 30, 40, 50, 60, 70, 80, 90};

  int n = sizeof(a) / sizeof(a[0]);

  findPermutations(a, 9);

  return 0;
}
