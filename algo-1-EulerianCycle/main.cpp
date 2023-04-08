#include "graph.h"
#include "utils.h"

#include <iostream>
#include <vector>

int main()
{
	std::cout << "Is the graph directed: y/n" << std::endl;

	/* first 3 inputs */
	char is_directed;
	std::cin >> is_directed;

	int n;
	std::cin >> n;

	int m;
	std::cin >> m;

	/* check if the input is valid */
	if (n < 1 || m < 1 || (is_directed != 'y' && is_directed != 'n'))
	{
		std::cout << "invalid input";
		return 0;
	}

	/* create the graph with n vertices, and set the graph to be directed if is_directed == 'y', with 0 edges */
	Graph graph(n, is_directed == 'y');

	/* add the edges to the graph */
	for (int i = 0; i < m; i++)
	{
		int v, u;
		std::cin >> v >> u;
		if (v < 1 || v > n || u < 1 || u > n) // check if the input is valid
		{
			// keep scanning the input until there is no more input (to discard the rest of the input)
			int x; // dummy variable, a "trashcan". We were guaranteed that all the inputs are integers
			while (std::cin >> x);
			std::cout << "invalid input";
			return 0;
		}
		graph.AddEdge(u, v);
	}

	if (IsEulerian(graph))
	{
		std::cout << "The graph is aulerian" << std::endl;
		std::vector<int> eulerian_cycle = FindEulerianCycle(graph);
		std::cout << "(";
		for (int i = 0; i < eulerian_cycle.size() - 1; i++)
		{
			std::cout << eulerian_cycle[i] << ", ";
		}
		std::cout << eulerian_cycle[eulerian_cycle.size() - 1] << ")";
	}
	else
	{
		std::cout << "The graph is not aulerian";
	}
	return 0;
}