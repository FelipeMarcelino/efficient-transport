#include <functional>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
using namespace std;

std::vector<std::vector<int>> make_move(std::vector<int> mat, int i, int n,
                                        int m) {

  std::vector<std::vector<int>> moves(4);

  std::vector<int> first_mat(mat);
  std::vector<int> second_mat(mat);
  std::vector<int> third_mat(mat);
  std::vector<int> fourth_mat(mat);
  if ((i % m) + 1 < m) {
    int energy = mat[i] + mat[(i % m) + 1];
    swap(first_mat[i], first_mat[(i % m) + 1]);
    // std::cout << energy << std::endl;
  }

  if ((i % m) + -1 >= 0) {
    int energy = mat[i] + mat[(i % m) - 1];
    swap(second_mat[i], second_mat[(i % m) - 1]);
    //  std::cout << energy << std::endl;
  }

  if ((i - m) >= 0) {
    int energy = mat[i] + mat[(i - m)];
    swap(third_mat[i], third_mat[(i - m)]);
    //   std::cout << energy << std::endl;
  }

  if ((i + m) < mat.size()) {
    int energy = mat[i] + mat[(i + m)];
    swap(fourth_mat[i], fourth_mat[(i + m)]);
    //    std::cout << energy << std::endl;
  }

  moves[0] = first_mat;
  moves[1] = second_mat;
  moves[2] = third_mat;
  moves[3] = fourth_mat;

  return moves;
}

void print_mat(std::vector<int> aux_mat) {
  for (auto i : aux_mat)
    std::cout << i << ' ';

  std::cout << std::endl;
}

struct VectorHasher {
  int operator()(const vector<int> &V) const {
    int hash_output = 0;
    std::hash<int> hash_int;
    for (int i = 0; i < V.size(); i++) {
      hash_output += hash_int(V[i] * i); // Can be anything
    }
    return hash_output;
  }
};

int main() {

  int x_moves[4] = {1, -1, 0, 0};
  int y_moves[4] = {0, 0, 1, -1};

  int n = 2;
  int m = 4;
  std::vector<int> mat{1, 2, 3, 4, 5, 6, 7, 8};
  std::vector<int> mat2{1, 2, 3, 4, 5, 6, 8, 7};
  std::unordered_map<vector<int>, std::pair<std::vector<int>, int>,
                     VectorHasher>
      hash_graph;

  hash_graph[mat] = std::make_pair(mat2, 1);

  for (int j = 0; j < 370000; j++) {
    for (int i = 0; i < 8; i++) {
      auto moves = make_move(mat, 2, n, m);
      hash_graph[moves[0]] = std::make_pair(mat2, 1);
      hash_graph[moves[1]] = 1;
      hash_graph[moves[2]] = 1;
      hash_graph[moves[3]] = 1;
    }
  }
}
