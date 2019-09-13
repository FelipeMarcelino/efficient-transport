#include <iostream>
#include <vector>
using namespace std;

#define _ ios_base::sync_with_stdio(0);cin.tie(0);

void print(std::vector<int> const &input)
{
	for (int i = 0; i < input.size(); i++) {
		std::cout << input.at(i) << ' ';
	}
}

int main()
{ _
	int n, m, aux;
	cin >> n >> m;
	std::vector<int> weights;
	std::vector<std::vector<int>> initial_state(n); 
	std::vector<std::vector<int>> final_state(n);

	// Reading standard input
	for(int i = 0 ; i < n * m; i++){
		cin >> aux;
		weights.push_back(aux);
	}

	for(int i = 0; i < n; i++){
		for(int j = 0; j < m; j++){
			cin >> aux;
			initial_state[i].push_back(aux);
		}
	}

	for(int i = 0; i < n; i++){
		for(int j = 0; j < m; j++){
			cin >> aux;
			final_state[i].push_back(aux);
		}
	}


	return 0;
}
