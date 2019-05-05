#include "Stack.h"
#include "Queue.h"
#include <limits>
using namespace std;
using namespace eleno;

struct Vertex
{
};

struct Edge
{
	int weight;
	size_t head_index;
	size_t tail_index;
	Edge* next_edge;
};

struct Graph
{
	size_t num_vex;
	Vertex* vertices;
	Edge* edges;
};

bool ConnectedDFS(const Graph& graph, const size_t source, const size_t destination)
{
	if (source == destination)
		return true;
	bool* visited = new bool[graph.num_vex];
	for (size_t i = 0; i != graph.num_vex; ++i)
		visited[i] = false;
	Stack<size_t> st;
	st.push(source);
	while (!st.empty())
	{
		size_t curr = st.top();
		st.pop();
		visited[curr] = true;
		for (Edge* p = &(graph.edges[curr]); p; p = p->next_edge)
		{
			if (p->tail_index == destination)
			{
				delete[] visited;
				return true;
			}
			if (!visited[p->tail_index])
				st.push(p->tail_index);
		}
	}
	delete[] visited;
	return false;
}

bool ConnectedBFS(const Graph& graph, const size_t source, const size_t destination)
{
	if (source == destination)
		return true;
	bool* visited = new bool[graph.num_vex];
	for (size_t i = 0; i != graph.num_vex; ++i)
		visited[i] = false;
	Queue<size_t> q;
	q.push(source);
	while (!q.empty())
	{
		size_t curr = q.front();
		q.pop();
		visited[curr] = true;
		for (Edge* p = &(graph.edges[curr]); p; p = p->next_edge)
		{
			if (p->tail_index == destination)
			{
				delete[] visited;
				return true;
			}
			if (!visited[p->tail_index])
				q.push(p->tail_index);
		}
	}
	delete[] visited;
	return false;
}

// After Dijkstra is executed, distance[i] records the shortest path from source to vertex i,
// prev_vex_index[i] tracks the previous vertex in the shortest path from source to vertex i.
void Dijkstra(const Graph& graph, const size_t source, int distance[], size_t prev_vex_index[])
{
	bool* done = new bool[graph.num_vex];
	for (size_t i = 0; i != graph.num_vex; ++i)
	{
		done[i] = false;
		distance[i] = INT_MAX;
	}
	done[source] = true;
	distance[source] = 0;
	// prev_vex_index[source] = source;
	for (Edge* p = &(graph.edges[source]); p; p = p->next_edge)
	{
		distance[p->tail_index] = p->weight;
		prev_vex_index[p->tail_index] = source;
	}
	for (size_t count = 1; count < graph.num_vex; ++count)
	{
		// get min distance
		size_t min_index;
		int min = INT_MAX;
		for (size_t i = 0; i != graph.num_vex; ++i)
		{
			if (!done[i] && distance[i] <= min)
			{
				min = distance[i];
				min_index = i;
			}
		}
		done[min_index] = true;
		for (Edge* p = &(graph.edges[min_index]); p; p = p->next_edge)
		{
			if (!done[p->tail_index] && distance[p->tail_index] > distance[min_index] + p->weight)
			{
				distance[p->tail_index] = distance[min_index] + p->weight;
				prev_vex_index[p->tail_index] = min_index;
			}
		}
	}
	delete[] done;
}

int main()
{
	return 0;
}
