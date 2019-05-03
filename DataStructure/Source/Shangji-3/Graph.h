#pragma once
#include "Vector.h"
#include "ForwardList.h"
#include "Stack.h"
using namespace eleno;

template <class T>
struct Graph
{
public:
	enum Type { DIRECTED, UNDIRECTED };

	struct Vertex;
	struct Edge;
	using size_type = typename Vector<Vertex>::size_type;

	struct Vertex
	{
		T data;
		ForwardList<Edge> edges;

		Vertex() : data()
		{
		}

		explicit Vertex(const T& data) { this->data = data; }
	};

	struct Edge
	{
	private:
		size_type _tail_index;
	public:
		Edge() = default;
		explicit Edge(const size_type& tailIndex) { _tail_index = tailIndex; }
		size_type tail_index() const { return _tail_index; }
	};

private:
	Type _type;
public:
	Vector<Vertex> vertices;
	explicit Graph(const Type& type) { _type = type; }
	Type type() const { return _type; }
	void add_vertex(const T& data);
	void add_edge(const size_type& head, const size_type& tail);
	void remove_vertex(const size_type& index);
	void remove_edge(const size_type& head, const size_type& tail);
	bool adjacent(const size_type& head, const size_type& tail) const;
	bool connected() const;
};

template <class T>
void Graph<T>::add_vertex(const T& data)
{
	vertices.push_back(Vertex(data));
}

template <class T>
void Graph<T>::add_edge(const size_type& head, const size_type& tail)
{
	if (head < vertices.size() && tail < vertices.size())
	{
		vertices[head].edges.push_front(Edge(tail));
		if (_type == UNDIRECTED)
			vertices[tail].edges.push_front(Edge(head));
	}
}

template <class T>
void Graph<T>::remove_vertex(const size_type& index)
{
	for (size_type i = 0; i != vertices.size(); ++i)
		remove_edge(i, index);
	vertices.erase(vertices.begin() + index);
}

template <class T>
void Graph<T>::remove_edge(const size_type& head, const size_type& tail)
{
	if (head < vertices.size() && tail < vertices.size())
	{
		for (auto iter = vertices[head].edges.beforebegin(); iter + 1 != vertices[head].edges.end(); ++iter)
		{
			if (*(iter + 1)._tail_index == tail)
			{
				vertices[head].edges.erase_after(iter);
				break;
			}
		}
		if (_type == UNDIRECTED)
		{
			for (auto iter = vertices[tail].edges.beforebegin(); iter + 1 != vertices[tail].edges.end(); ++iter)
			{
				if (*(iter + 1)._tail_index == head)
				{
					vertices[tail].edges.erase_after(iter);
					break;
				}
			}
		}
	}
}

template <class T>
bool Graph<T>::adjacent(const size_type& head, const size_type& tail) const
{
	for (const auto& edge : vertices[head].edges)
	{
		if (edge._tail_index == tail)
			return true;
	}
	return false;
}

template <class T>
bool Graph<T>::connected() const
{
	if (vertices.empty())
		return true;
	bool* visited = new bool[vertices.size()];
	for (size_type i = 0; i < vertices.size(); ++i)
		visited[i] = false;
	size_type start = 0;
	Stack<size_type> st;
	st.push(start);
	while (!st.empty())
	{
		size_type vexIndex = st.top();
		st.pop();
		visited[vexIndex] = true;
		for (const auto& edge : vertices[vexIndex].edges)
			if(!visited[edge.tail_index()])
			st.push(edge.tail_index());
	}
	for (size_type i = 0; i < vertices.size(); ++i)
		if (!visited[i])
		{
			delete[] visited;
			return false;
		}
	delete[] visited;
	return true;
}
