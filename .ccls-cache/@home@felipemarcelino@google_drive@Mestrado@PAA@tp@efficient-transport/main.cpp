#include <bits/stdc++.h>
#include <iostream>
#include <limits>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

#define _                                                                      \
  ios_base::sync_with_stdio(0);                                                \
  cin.tie(0);

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

// VectorHasher is a struct that transform a vector 1D into a hash key for
// unordered_map 1
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

struct comparator_queue {
  // queue elements are vectors so we need to compare those
  bool operator()(std::pair<std::vector<int>, int> const &a,
                  std::pair<std::vector<int>, int> const &b) const {

    // reverse sort puts the lowest value at the top
    return a.second > b.second;
  }
};

using queue_graph =
    std::priority_queue<std::pair<std::vector<int>, int>,
                        std::vector<std::pair<std::vector<int>, int>>,
                        comparator_queue>;

void create_neighbors(std::vector<int> mat, int i, int n, int m,
                      std::vector<std::pair<std::vector<int>, int>> &moves,
                      std::vector<int> weights) {

  std::vector<int> first_mat(mat);
  std::vector<int> second_mat(mat);
  std::vector<int> third_mat(mat);
  std::vector<int> fourth_mat(mat);

  if ((i % m) + 1 < m) {
    // int energy = mat[i] + mat[(i % m) + 1];
    int energy = weights[mat[i] - 1] + weights[mat[(i + 1)] - 1];
    swap(first_mat[i], first_mat[(i + 1)]);
    moves.push_back(std::make_pair(first_mat, energy));
  }

  if ((i % m) + -1 >= 0) {
    // int energy = mat[i] + mat[(i % m) - 1];
    int energy = weights[mat[i] - 1] + weights[mat[(i - 1)] - 1];
    swap(second_mat[i], second_mat[(i - 1)]);
    moves.push_back(std::make_pair(second_mat, energy));
  }

  if ((i - m) >= 0) {
    // int energy = mat[i] + mat[(i - m)];
    int energy = weights[mat[i] - 1] + weights[mat[(i - m)] - 1];
    swap(third_mat[i], third_mat[(i - m)]);
    moves.push_back(std::make_pair(third_mat, energy));
  }

  if ((i + m) < mat.size()) {
    // int energy = mat[i] + mat[(i + m)];
    int energy = weights[mat[i] - 1] + weights[mat[(i + m)] - 1];
    swap(fourth_mat[i], fourth_mat[(i + m)]);
    moves.push_back(std::make_pair(fourth_mat, energy));
  }
}

int reverse_order(
    std::unordered_map<std::vector<int>, std::pair<std::vector<int>, int>,
                       VectorHasher>
        graph,
    std::vector<int> final_state, std::vector<int> initial_state) {

  if (graph.find(final_state) != graph.end()) {
    int energy = 0;
    auto u = graph[final_state];
    energy += u.second;
    print(u.first);
    std::cout << u.second << std::endl;

    while (true) {
      auto z = graph.at(u.first);
      print(z.first);
      std::cout << z.second << std::endl;

      if (std::equal(z.first.begin(), z.first.end(), initial_state.begin()) ==
          true) // Target vertex found
        break;

      u = z;

      energy += u.second;
    }

    return energy;

  } else
    return -1;
}

int dijkstra(std::vector<int> initial_state, std::vector<int> final_state,
             int n, int m, std::vector<int> weights) {

  int energy = 0; // Distance to reach final state using the graph

  std::unordered_map<std::vector<int>, std::pair<std::vector<int>, int>,
                     VectorHasher>
      graph;

  std::vector<int> null_vector;

  // Adding source vertex into graph
  graph[initial_state] = std::make_pair(null_vector, 0);

  queue_graph q_graph;

  q_graph.push(std::make_pair(initial_state, 0));

  while (q_graph.empty() == false) {

    auto u = q_graph.top().first;
    q_graph.pop(); // Remove the smallest priority element

    if (std::equal(u.begin(), u.end(), final_state.begin()) ==
        true) // Target vertex found
      break;

    auto vertex_u_property = graph[u];

    for (int i = 0; i < u.size(); ++i) {
      std::vector<std::pair<std::vector<int>, int>> moves;

      create_neighbors(u, i, n, m, moves,
                       weights); // u = vertex, i = element in vertex, n =
                                 // height, m = width, moves = possible moves

      for (auto v : moves) {
        int alt = vertex_u_property.second + v.second;

        if (graph.find(v.first) == graph.end()) {

          graph[v.first] = std::make_pair(u, alt);
          q_graph.push(std::make_pair(v.first, alt));

        } else {
          auto vertex_v_property = graph[v.first];
          int dist_v = vertex_v_property.second;

          if (alt < dist_v) {
            graph[v.first] = std::make_pair(u, alt);
            // q_graph.push(std::make_pair(v.first, alt));
          }
        }
      }
    }
  }

  energy = graph[final_state].second;

  return energy;
}

int main() {
  _ int n, m, aux;
  cin >> n >> m;
  std::vector<int> weights;

  // Matrix flattened using a 1D vector
  std::vector<int> initial_state;
  std::vector<int> final_state;

  std::unordered_map<std::vector<int>, std::pair<std::vector<int>, int>,
                     VectorHasher>
      graph;

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
