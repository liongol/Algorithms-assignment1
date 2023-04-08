#include "utils.h"

std::vector<std::vector<int>> GetIndegreeOutdegree(Graph g)
/*
input: graph g
output: a vector of vectors of integeres, where indegree_outdegree[i][0] is the indegree of node i+1 and indegree_outdegree[i][1] is the outdegree of node i+1
*/
{
	std::vector<std::vector<int>> indegree_outdegree(g.GetNumVertices(), std::vector<int>(2, 0));
	std::vector<std::vector<int>> adjacency_list = g.GetAdjacencyList();
	for (int i = 0; i < adjacency_list.size(); i++)
	{
		for (int j = 0; j < adjacency_list[i].size(); j++)
		{
			indegree_outdegree[adjacency_list[i][j] - 1][0]++;
			indegree_outdegree[i][1]++;
		}
	}
	return indegree_outdegree;
}

bool AreAllDegreesEvenOrInEqOut(std::vector<std::vector<int>> indegree_outdegree, bool directed)
/*
input: indegree_outdegree: a vector of vectors of integers, where indegree_outdegree[i][0] is the indegree of node i+1 and indegree_outdegree[i][1] is the outdegree of node i+1
	   directed: a boolean indicating whether the graph is directed or not
output: true if all indegrees are equal to outdegrees (if directed) or all degrees are even (if undirected), false otherwise
*/
{
	if (directed)
	{
		// check if all indegrees are equal to outdegrees
		for (int i = 0; i < indegree_outdegree.size(); i++)
		{
			if (indegree_outdegree[i][0] != indegree_outdegree[i][1])
			{
				return false;
			}
		}
	}
	else
	{
		// check if all degrees are even
		for (int i = 0; i < indegree_outdegree.size(); i++)
		{
			if (indegree_outdegree[i][0] % 2 != 0)
			{
				return false;
			}
		}
	}
	return true;
}

Graph GetTransposedGraph(Graph g)
/*
input: graph g
output: transposed graph of g
*/
{
	if (!g.IsDirected())
	{
		return g;
	}
	else
	{
		Graph transposed_graph(g.GetNumVertices(), true);
		std::vector<std::vector<int>> adjacency_list = g.GetAdjacencyList();

		for (int i = 0; i < g.GetNumVertices(); i++)
		{
			std::vector<int> neighbor_list = g.NeighborList(i + 1);
			for (int j = 0; j < neighbor_list.size(); j++)
			{
				transposed_graph.AddEdge(i + 1, neighbor_list[j]);
			}
		}
		return transposed_graph;
	}
}

// Visit function of DFS algorithm (in our assignment, used to check if the graph is strongly connected or connected)
void Visit(Graph g, int u, std::vector<bool>& visited)
/*
input: graph g, node u, visited: a vector of booleans, where visited[i] is true if node i+1 has been visited, false otherwise
output: none
*/
{
	if (visited[u - 1])
	{
		return;
	}

	visited[u - 1] = true;
	std::vector<int> neighbor_list = g.NeighborList(u);
	for (int i = 0; i < neighbor_list.size(); i++)
	{
		if (!visited[neighbor_list[i] - 1])
		{
			Visit(g, neighbor_list[i], visited);
		}
	}
}

bool IsStronglyConnectedOrConnected(Graph g)
/*
input: graph g
output: true if the graph is strongly connected or connected, false otherwise
*/
{
	// if the graph is directed, we need to run Visit algorithm on node [0], and then on node [0] in the transposed graph
	// if the graph is undirected, we need to run Visit algorithm on node [0]
	std::vector<bool> visited(g.GetNumVertices(), false);

	if (g.IsDirected())
	{
		Visit(g, 1, visited);
		for (int i = 0; i < visited.size(); i++)
		{
			if (!visited[i])
			{
				return false;
			}
		}
		visited = std::vector<bool>(g.GetNumVertices(), false);
		Graph transposed_graph = GetTransposedGraph(g);
		Visit(transposed_graph, 1, visited);
		for (int i = 0; i < visited.size(); i++)
		{
			if (!visited[i])
			{
				return false;
			}
		}
		return true;
	}
	else
	{
		Visit(g, 1, visited);
		for (int i = 0; i < visited.size(); i++)
		{
			if (!visited[i])
			{
				return false;
			}
		}
		return true;
	}
	return false; // should never reach this line
}


bool IsEulerian(Graph g)
/*
input: graph g
output: true if the graph is Eulerian, false otherwise
(a graph is iff it is strongly connected or connected and all indegrees are equal to outdegrees (if directed) or all degrees are even (if undirected))
*/
{
	if (!IsStronglyConnectedOrConnected(g))
	{
		return false;
	}
	std::vector<std::vector<int>> indegree_outdegree = GetIndegreeOutdegree(g);
	return AreAllDegreesEvenOrInEqOut(indegree_outdegree, g.IsDirected());
}

std::vector<int> FindCircuit(Graph g, int v, std::vector<std::vector<bool>>& used_edges)
/*
input: graph g, vertex v, used_edges: a matrix of booleans, where used_edges[i][j] is true if the edge (i+1, j+1) has been used, false otherwise
output: a list of vertices
*/
{
	std::vector<int> circuit;
	circuit.push_back(v);
	int current_vertex = v;
	do
	{
		std::vector<int> neighbor_list = g.NeighborList(current_vertex);
		for (int i = 0; i < neighbor_list.size(); i++)
		{
			if (!used_edges[current_vertex - 1][neighbor_list[i] - 1])
			{
				used_edges[current_vertex - 1][neighbor_list[i] - 1] = true;
				used_edges[neighbor_list[i] - 1][current_vertex - 1] = true;
				circuit.push_back(neighbor_list[i]);
				current_vertex = neighbor_list[i];
				break;
			}
		}
	} while (current_vertex != v);
	return circuit;
}

std::vector<int> FindEulerianCycle(Graph g)
/*
input: graph g
output: a list of vertices, representing an Euler circuit
*/
{
	std::vector<std::vector<bool>> used_edges(g.GetNumVertices(), std::vector<bool>(g.GetNumVertices(), false));
	std::vector<int> euler_circuit = FindCircuit(g, 1, used_edges);
	int index = 0;
	while (index < euler_circuit.size())
	{
		int current_vertex = euler_circuit[index];
		std::vector<int> neighbor_list = g.NeighborList(current_vertex);
		bool has_unused_edge = false;
		for (int i = 0; i < neighbor_list.size(); i++)
		{
			if (!used_edges[current_vertex - 1][neighbor_list[i] - 1])
			{
				has_unused_edge = true;
				break;
			}
		}
		if (has_unused_edge)
		{
			std::vector<int> circuit = FindCircuit(g, current_vertex, used_edges);
			euler_circuit.insert(euler_circuit.begin() + index, circuit.begin(), circuit.end());
		}
		index++;
	}
	// here we got almost a correct circuit. now, we might have vertices that are written twice in a row, because we didn't delete one instance of them when we "pasted" the circuit into the euler_circuit
	// we will delete the second instance of each vertex
	for (int i = 0; i < euler_circuit.size() - 1; i++)
	{
		if (euler_circuit[i] == euler_circuit[i + 1])
		{
			euler_circuit.erase(euler_circuit.begin() + i);
			i--;
		}
	}
	return euler_circuit;
}