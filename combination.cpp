// C++ program to display all permutations
// of an array using STL in C++

#include <bits/stdc++.h>
using namespace std;

// Function to display the array
void display(int a[], int n) {
  for (int i = 0; i < n; i++) {
    // cout << a[i] << " ";
  }
  // cout << endl;
}

// Function to find the permutations
void findPermutations(int a[], int n) {

  // Sort the given array
  sort(a, a + n);
  int contador = 0;

  // Find all possible permutations
  do {
    display(a, n);
    contador += 1;
  } while (next_permutation(a, a + n));

  std::cout << contador << std::endl;
}

// Driver code
int main() {

  int a[] = {10, 20, 30, 40, 50, 60, 70, 80, 90};

  int n = sizeof(a) / sizeof(a[0]);

  findPermutations(a, n);

  return 0;
}
