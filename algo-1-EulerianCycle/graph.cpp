#include "graph.h"

#include <iostream>

Graph::Graph(int n, bool is_directed)
{
	this->n = n;
	this->is_directed = is_directed;
	adjacency_list.resize(n);
}

void Graph::AddEdge(int u, int v)
{
	int node_v_to_u = u;
	if (!is_directed)
	{
		int node_u_to_v = v;
		adjacency_list[u - 1].push_back(node_u_to_v);
	}
	adjacency_list[v - 1].push_back(node_v_to_u);

	m++;
}

void Graph::PrintGraph()
{
	for (int i = 0; i < n; i++)
	{
		std::cout << "Node " << i + 1 << ": ";
		for (int j = 0; j < adjacency_list[i].size(); j++)
		{
			std::cout << adjacency_list[i][j] << " ";
		}
		std::cout << std::endl;
	}
}

void Graph::DeleteEdge(int u, int v)
{
	for (int i = 0; i < adjacency_list[u - 1].size(); i++)
	{
		if (adjacency_list[u - 1][i] == v)
		{
			adjacency_list[u - 1].erase(adjacency_list[u - 1].begin() + i);
			break;
		}
	}
	if (!is_directed)
	{
		for (int i = 0; i < adjacency_list[v - 1].size(); i++)
		{
			if (adjacency_list[v - 1][i] == u)
			{
				adjacency_list[v - 1].erase(adjacency_list[v - 1].begin() + i);
				break;
			}
		}
	}
	m--;
}

bool Graph::AreNeighbors(int u, int v)
{
	for (int i = 0; i < adjacency_list[u - 1].size(); i++)
	{
		if (adjacency_list[u - 1][i] == v)
		{
			return true;
		}
	}
	return false;
}

std::vector<int> Graph::NeighborList(int u)
{
	std::vector<int> neighbor_list;
	for (int i = 0; i < adjacency_list[u - 1].size(); i++)
	{
		int node = adjacency_list[u - 1][i];
		neighbor_list.push_back(node);
	}
	return neighbor_list;
}

int Graph::GetNumVertices()
{
	return n;
}

int Graph::GetNumEdges()
{
	return m;
}

void Graph::SetAdjacencyList(std::vector<std::vector<int>> adjacency_list)
{
	this->adjacency_list = adjacency_list;
}

bool Graph::IsDirected()
{
	return is_directed;
}

std::vector<std::vector<int>> Graph::GetAdjacencyList()
{
	return adjacency_list;
}

void Graph::SetNumVertices(int n)
{
	this->n = n;
}

void Graph::SetNumEdges(int m)
{
	this->m = m;
}

void Graph::SetIsDirected(bool is_directed)
{
	this->is_directed = is_directed;
}