#pragma once
#include "Stack.h"
using namespace eleno;

template <class T>
struct Node
{
	T data;
	Node* first_child;
	Node* next_sibling;
};
template <class T>
void InorderTraverse(Node<T>* root)
{
	Stack<Node<T>*> st;

	if (!root)
		return;

}