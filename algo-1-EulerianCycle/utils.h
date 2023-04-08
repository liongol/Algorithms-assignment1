#pragma once

#include <vector>
#include "graph.h"

std::vector<std::vector<int>> GetIndegreeOutdegree(Graph g);
/*
input: graph g
output: a vector of vectors of integeres, where indegree_outdegree[i][0] is the indegree of node i+1 and indegree_outdegree[i][1] is the outdegree of node i+1
*/

bool AreAllDegreesEvenOrInEqOut(std::vector<std::vector<int>> indegree_outdegree, bool directed);
/*
input: indegree_outdegree: a vector of vectors of integers, where indegree_outdegree[i][0] is the indegree of node i+1 and indegree_outdegree[i][1] is the outdegree of node i+1
	   directed: a boolean indicating whether the graph is directed or not
output: true if all indegrees are equal to outdegrees (if directed) or all degrees are even (if undirected), false otherwise
*/

Graph GetTransposedGraph(Graph g);
/*
input: graph g
output: transposed graph of g
*/

// Visit function of DFS algorithm (in our assignment, used to check if the graph is strongly connected or connected)
void Visit(Graph g, int u, std::vector<bool>& visited);
/*
input: graph g, node u, visited: a vector of booleans, where visited[i] is true if node i+1 has been visited, false otherwise
output: none
*/

bool IsStronglyConnectedOrConnected(Graph g);
/*
input: graph g
output: true if the graph is strongly connected or connected, false otherwise
*/

bool IsEulerian(Graph g);
/*
input: graph g
output: true if the graph is Eulerian, false otherwise
(a graph is iff it is strongly connected or connected and all indegrees are equal to outdegrees (if directed) or all degrees are even (if undirected))
*/

std::vector<int> FindCircuit(Graph g, int v, std::vector<std::vector<bool>>& used_edges);
/*
input: graph g, vertex v, used_edges: a matrix of booleans, where used_edges[i][j] is true if the edge (i+1, j+1) has been used, false otherwise
output: a list of vertices
*/

std::vector<int> FindEulerianCycle(Graph g);
/*
input: graph g
output: a list of vertices, representing an Euler circuit
*/