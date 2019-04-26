#pragma once
#include "SeqQueue.h"
#include <iostream>
using namespace std;
using namespace eleno;

template <class T>
struct BiTreeNode
{
	T data;
	BiTreeNode* left;
	BiTreeNode* right;
};

template <class T>
BiTreeNode<T>* ReadTree(const T& end)
{
	BiTreeNode<T>* node = nullptr;
	T ch;
	cin >> ch;
	if (ch != end)
	{
		node = new BiTreeNode<T>;
		node->data = ch;
		node->left = ReadTree(end);
		node->right = ReadTree(end);
	}
	return node;
}
template <class T>
void LevelTraverse(BiTreeNode<T>* root)
{
	if (!root)
		return;
	SeqQueue<BiTreeNode<T>*> q;
	q.push(root);
	while (!q.empty())
	{
		BiTreeNode<T>* curr = q.front();
		cout << curr->data << ' ';
		// do something
		q.pop();
		if (curr->left)
			q.push(curr->left);
		if (curr->right)
			q.push(curr->right);
	}
}

template <class T>
size_t GetWidth(BiTreeNode<T>* root)
{
	if (!root)
		return 0;
	size_t width = 1;
	SeqQueue<BiTreeNode<T>*> q;
	q.push(root);
	while (!q.empty())
	{
		for (size_t remain = q.size(); remain > 0; --remain)
		{
			BiTreeNode<T>* curr = q.front();
			q.pop();
			if (curr->left)
				q.push(curr->left);
			if (curr->right)
				q.push(curr->right);
		}
		if (q.size() > width)
			width = q.size();
	}
	return width;
}