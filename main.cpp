#include <bits/stdc++.h>
#include <iostream>
#include <limits>
#include <string>
#include <tuple>
#include <unordered_map>
#include <vector>

using namespace std;

#define _                                                                      \
  ios_base::sync_with_stdio(0);                                                \
  cin.tie(0);

void transform_vector_to_string(std::vector<int> vec, std::string &vec_str) {
  std::ostringstream vts;
  // Convert all but the last element to avoid a trailing ","
  std::copy(vec.begin(), vec.end() - 1, std::ostream_iterator<int>(vts, "-"));

  // Now add the last element with no delimiter
  vts << vec.back();

  vec_str = vts.str();
}

std::vector<int> transform_string_to_vector(std::string vec_str,
                                            char delimiter) {

  std::stringstream ss(vec_str);
  std::string item;
  std::vector<int> splittedStrings;
  while (std::getline(ss, item, delimiter)) {
    splittedStrings.push_back(std::atoi(item.c_str()));
  }

  return splittedStrings;
}

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

struct comparator_queue {
  // queue elements are vectors so we need to compare those
  bool operator()(std::pair<std::string, int> const &a,
                  std::pair<std::string, int> const &b) const {

    // reverse sort puts the lowest value at the top
    return a.second > b.second;
  }
};

using queue_graph =
    std::priority_queue<std::pair<std::string, int>,
                        std::vector<std::pair<std::string, int>>,
                        comparator_queue>;

void create_neighbors(
    std::vector<int> mat, int i, int n, int m,
    std::vector<std::tuple<std::vector<int>, std::string, int>> &moves,
    std::vector<int> weights) {

  std::vector<int> first_mat(mat);
  std::vector<int> second_mat(mat);
  std::vector<int> third_mat(mat);
  std::vector<int> fourth_mat(mat);

  if ((i % m) + 1 < m) {
    int energy = weights[mat[i] - 1] + weights[mat[(i + 1)] - 1];
    swap(first_mat[i], first_mat[(i + 1)]);
    std::string first_str;
    transform_vector_to_string(first_mat, first_str);
    moves.push_back(std::make_tuple(first_mat, first_str, energy));
  }

  if ((i % m) + -1 >= 0) {
    int energy = weights[mat[i] - 1] + weights[mat[(i - 1)] - 1];
    swap(second_mat[i], second_mat[(i - 1)]);
    std::string second_str;
    transform_vector_to_string(second_mat, second_str);
    moves.push_back(std::make_tuple(second_mat, second_str, energy));
  }

  if ((i - m) >= 0) {
    int energy = weights[mat[i] - 1] + weights[mat[(i - m)] - 1];
    swap(third_mat[i], third_mat[(i - m)]);
    std::string third_str;
    transform_vector_to_string(third_mat, third_str);
    moves.push_back(std::make_tuple(third_mat, third_str, energy));
  }

  if ((i + m) < mat.size()) {
    int energy = weights[mat[i] - 1] + weights[mat[(i + m)] - 1];
    swap(fourth_mat[i], fourth_mat[(i + m)]);
    std::string fourth_str;
    transform_vector_to_string(fourth_mat, fourth_str);
    moves.push_back(std::make_tuple(fourth_mat, fourth_str, energy));
  }
}

int reverse_order(
    std::unordered_map<std::string, std::pair<std::string, int>> graph,
    std::string final_state, std::string initial_state) {

  if (graph.find(final_state) != graph.end()) {
    int energy = 0;
    auto u = graph[final_state];
    energy += u.second;
    std::cout << u.first << std::endl;
    std::cout << u.second << std::endl;

    while (true) {
      auto z = graph.at(u.first);
      std::cout << z.first << std::endl;
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

  std::unordered_map<std::string,
                     std::tuple<std::string, std::vector<int>, int>>
      graph;

  std::string source = "source";

  std::string initial_state_str, final_state_str;
  transform_vector_to_string(initial_state, initial_state_str);
  transform_vector_to_string(final_state, final_state_str);

  // Adding source vertex into graph
  graph[initial_state_str] = std::make_tuple("source", initial_state, 0);

  queue_graph q_graph;

  q_graph.push(std::make_pair(initial_state_str, 0));

  while (q_graph.empty() == false) {

    auto u = q_graph.top().first;
    q_graph.pop(); // Remove the smallest priority element

    if (u == final_state_str) // Target vertex found
      break;

    auto vertex_u_property = graph[u];

    for (int i = 0; i < n * m; ++i) {
      std::vector<std::tuple<std::vector<int>, std::string, int>> moves;

      create_neighbors(std::get<1>(vertex_u_property), i, n, m, moves,
                       weights); // u = vertex, i = element in vertex, n =
                                 // height, m = width, moves = possible moves

      for (auto v : moves) {
        int alt = std::get<2>(vertex_u_property) + std::get<2>(v);

        if (graph.find(std::get<1>(v)) == graph.end()) {

          graph[std::get<1>(v)] = std::make_tuple(u, std::get<0>(v), alt);
          q_graph.push(std::make_pair(std::get<1>(v), alt));
        } else {
          auto vertex_v_property = graph[std::get<1>(v)];
          int dist_v = std::get<2>(vertex_v_property);

          if (alt < dist_v) {
            graph[std::get<1>(v)] = std::make_tuple(u, std::get<0>(v), alt);
            q_graph.push(std::make_pair(std::get<1>(v), alt));
          }
        }
      }
    }
  }

  energy = std::get<2>(graph[final_state_str]);
  return energy;
}

int main() {
  _ int n, m, aux;
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
