// C++ program to display all permutations
// of an array using STL in C++

#include <bits/stdc++.h>
#include <iostream>
#include <vector>
using namespace std;

// VectorHasher is a struct that transform a vector 1D into a hash key for
// unordered_map 1

std::unordered_map<std::string, std::pair<std::vector<int>, int>> graph;
// Function to display the array
void display(std::vector<int> a, int n) {
  for (int i = 0; i < n; i++) {
    // cout << a[i] << " ";
  }
  // cout << endl;
}

// Function to find the permutations
void findPermutations(std::vector<int> a, int n) {

  // Sort the given array
  std::sort(a.begin(), a.end());
  int contador = 0;

  std::ostringstream vts;
  // Convert all but the last element to avoid a trailing ","
  std::copy(a.begin(), a.end() - 1, std::ostream_iterator<int>(vts, "-"));

  // Now add the last element with no delimiter
  vts << a.back();
  graph[vts.str()] = std::make_pair(a, 1);

  // Find all possible permutations
  do {
    display(a, n);

    std::ostringstream vts;
    // Convert all but the last element to avoid a trailing ","
    std::copy(a.begin(), a.end() - 1, std::ostream_iterator<int>(vts, "-"));
    vts << a.back();
    graph[vts.str()] = std::make_pair(a, 1);
    contador += 1;
  } while (next_permutation(a.begin(), a.end()));

  std::cout << contador << std::endl;
  std::cout << graph.size() << std::endl;
}

// Driver code
int main() {

  std::vector<int> a = {10, 20, 30, 40, 50, 60, 70, 80, 90};

  int n = sizeof(a) / sizeof(a[0]);

  findPermutations(a, n);

  return 0;
}
