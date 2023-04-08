#pragma once

#include <vector>
#include <string>

class Graph
{
private:
	int n; // number of vertices
	int m; // number of edges
	bool is_directed; // true if the graph is directed
	std::vector<std::vector<int>> adjacency_list; // adjacency list representation of the graph
public:
	Graph(int n, bool is_directed); // constructor
	void AddEdge(int u, int v); // add an edge from node u to node v

	void PrintGraph(); // print the graph, internal use only

	// getters
	int GetNumVertices();
	int GetNumEdges();
	bool IsDirected();
	std::vector<std::vector<int>> GetAdjacencyList();

	// setters
	void SetNumVertices(int n);
	void SetNumEdges(int m);
	void SetIsDirected(bool is_directed);
	void SetAdjacencyList(std::vector<std::vector<int>> adjacency_list);

	// not really used in the assignment, but still have to implement them
	void DeleteEdge(int u, int v); // delete an edge from node u to node v
	bool AreNeighbors(int u, int v); // return true if node v is a neighbor of node u
	std::vector<int> NeighborList(int u); // return a list of neighbors of node u
};