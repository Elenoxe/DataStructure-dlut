#include "Stack.h"
#include "Queue.h"
using namespace eleno;
struct BiTreeNode
{
	int data;
	BiTreeNode* left;
	BiTreeNode* right;
};
typedef BiTreeNode* BiTree;
BiTreeNode* Search(const BiTree &tr, const int &val)
{
	if (tr == nullptr)
		return nullptr;
	Stack<BiTree> st;
	st.Push(tr);
	while (!st.IsEmpty())
	{
		BiTree node = st.Top();
		if (node->data == val)
			return node;
		st.Pop();
		if (node->right)
			st.Push(node->right);
		if (node->left)
			st.Push(node->left);
	}
	return nullptr;
}

bool IsComplete(const BiTree& tr)
{
	if (tr == nullptr)
		return true;
	bool flag = false;
	Queue<BiTree> q;
	q.Push(tr);
	while (!q.IsEmpty())
	{
		BiTree node = q.Front();
		q.Pop();
		if (node->left)
		{
			if (flag)
				return false;
			q.Push(node->left);
		}
		else
			flag = true;
		if (node->right)
		{
			if (flag)
				return false;
			q.Push(node->right);
		}
		else
			flag = true;
	}
	return true;
}

int main()
{
	return 0;
}