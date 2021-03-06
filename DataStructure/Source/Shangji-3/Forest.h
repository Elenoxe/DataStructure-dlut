#pragma once
#include "Stack.h"
#include "Queue.h"
#include <functional>
using namespace eleno;

template <class T>
struct Node
{
	T data;
	Node* first_child;
	Node* next_sibling;
};

template <class T>
void InorderTraverse(Node<T>* node, std::function<void(Node<T>*)> visit)
{
	if (!node)
		return;
	Stack<Node<T>*> st;
	while (!st.empty() || node)
	{
		if (node)
		{
			st.push(node);
			node = node->first_child;
		}
		else
		{
			node = st.top();
			st.pop();
			visit(node);
			node = node->next_sibling;
		}
	}
}

template <class T>
int GetLeafCount(Node<T>* root)
{
	if (!root)
		return 0;
	int num = 0;
	auto f = [&num](Node<T>* node)-> void
	{
		if (!node->first_child)
			++num;
	};
	InorderTraverse<T>(root, f);
	return num;
}

template <class T>
bool IsComplete(Node<T>* root)
{
	// Level traverse the tree,
	// once encounter a node which is nullptr
	// any nodes encountered after must be nullptr
	if (!root)
		return true;
	bool done = false;
	Queue<Node<T>*> q;
	q.push(root);
	while (!q.empty())
	{
		Node<T>* curr = q.front();
		q.pop();
		if (!curr)
			done = true;
		else
		{
			if (done)
				return false;
			q.push(curr->first_child);
			q.push(curr->next_sibling);
		}
	}
	return true;
}
