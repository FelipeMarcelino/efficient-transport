#include <bits/stdc++.h>
#include <iostream>
#include <limits>
#include <string>
#include <tuple>
#include <unordered_map>
#include <vector>

using namespace std;

void print(std::vector<int> const &input) {
  for (int i = 0; i < input.size(); i++) {
    std::cout << input.at(i) << ' ';
  }
  std::cout << std::endl;
}

void print2D(std::vector<std::vector<int>> const &input) {
  for (int i = 0; i < input.size(); i++) {
    for (int j = 0; j < input[i].size(); j++) {
      std::cout << input.at(i).at(j) << ' ';
    }
    std::cout << std::endl;
  }

  std::cout << std::endl;
}

class int32_vector_hasher {
public:
  std::size_t operator()(std::vector<int> const &vec) const {
    std::size_t seed = vec.size();
    for (auto &i : vec) {
      seed ^= i + 0x9e3779b9 + (seed << 6) + (seed >> 2);
    }
    return seed;
  };
};

struct comparator_queue {
  // queue elements are vectors so we need to compare those
  bool operator()(std::pair<std::vector<int>, int> const &a,
                  std::pair<std::vector<int>, int> const &b) const {

    // reverse sort puts the lowest value at the top
    return a.second > b.second;
  }
};

void find_all_permutations(std::unordered_map<int, int> &graph,
                           std::vector<int> initial_state) {

  std::sort(initial_state.begin(), initial_state.end());
  int32_vector_hasher hasher;

  do {
    auto key_g = hasher(initial_state);
    graph[key_g] = std::numeric_limits<int>::max();
  } while (next_permutation(initial_state.begin(), initial_state.end()));
}

using queue_graph =
    std::priority_queue<std::pair<std::vector<int>, int>,
                        std::vector<std::pair<std::vector<int>, int>>,
                        comparator_queue>;

void create_neighbors(std::vector<int> mat, int i, int n, int m,
                      std::vector<std::pair<std::vector<int>, int>> &moves,
                      std::vector<int> weights) {

  if ((i % m) + 1 < m) {
    int energy = weights[mat[i] - 1] + weights[mat[(i + 1)] - 1];
    swap(mat[i], mat[(i + 1)]);
    moves.push_back(std::make_pair(mat, energy));
    swap(mat[i + 1], mat[(i)]);
  }

  if ((i % m) + -1 >= 0) {
    int energy = weights[mat[i] - 1] + weights[mat[(i - 1)] - 1];
    swap(mat[i], mat[(i - 1)]);
    moves.push_back(std::make_pair(mat, energy));
    swap(mat[i - 1], mat[(i)]);
  }

  if ((i - m) >= 0) {
    int energy = weights[mat[i] - 1] + weights[mat[(i - m)] - 1];
    swap(mat[i], mat[(i - m)]);
    moves.push_back(std::make_pair(mat, energy));
    swap(mat[i - m], mat[(i)]);
  }

  if ((i + m) < mat.size()) {
    int energy = weights[mat[i] - 1] + weights[mat[(i + m)] - 1];
    swap(mat[i], mat[(i + m)]);
    moves.push_back(std::make_pair(mat, energy));
    swap(mat[i + m], mat[(i)]);
  }
}

int dijkstra(std::vector<int> initial_state, std::vector<int> final_state,
             int n, int m, std::vector<int> weights) {

  int energy = 0; // Distance to reach final state using the graph

  std::unordered_map<int, int> graph;
  int32_vector_hasher hasher;
  auto copy_initital_state = initial_state;

  find_all_permutations(graph, copy_initital_state);

  // Adding source vertex into graph
  auto key_first = hasher(initial_state);
  graph[key_first] = 0;

  queue_graph q_graph;

  q_graph.push(std::make_pair(initial_state, 0));

  while (q_graph.empty() == false) {

    auto u = q_graph.top().first;
    q_graph.pop(); // Remove the smallest priority element

    if (u == final_state) // Target vertex found
      break;

    int dist = graph[hasher(u)];

    for (int i = 0; i < n * m; ++i) {
      std::vector<std::pair<std::vector<int>, int>> moves;

      create_neighbors(u, i, n, m, moves,
                       weights); // u = vertex, i = element in vertex, n =
                                 // height, m = width, moves = possible moves

      for (auto v : moves) {
        int alt = dist + v.second;

        auto actual_value = graph[hasher(v.first)];
        if (alt < actual_value) {
          graph[hasher(v.first)] = alt;
          q_graph.push(std::make_pair(v.first, alt));
        }
      }
    }
  }

  energy = graph[hasher(final_state)];
  return energy;
}

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  int n, m, aux;
  cin >> n >> m;
  std::vector<int> weights;

  // Matrix flattened using a 1D vector
  std::vector<int> initial_state;
  std::vector<int> final_state;

  // Reading standard input
  for (int i = 0; i < n * m; i++) {
    cin >> aux;
    weights.push_back(aux);
  }

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      cin >> aux;
      initial_state.push_back(aux);
    }
  }

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      cin >> aux;
      final_state.push_back(aux);
    }
  }

  int energy = dijkstra(initial_state, final_state, n, m, weights);

  std::cout << energy << std::endl;

  return 0;
}
