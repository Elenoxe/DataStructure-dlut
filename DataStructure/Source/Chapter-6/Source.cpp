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
	st.push(tr);
	while (!st.empty())
	{
		BiTree node = st.top();
		if (node->data == val)
			return node;
		st.pop();
		if (node->right)
			st.push(node->right);
		if (node->left)
			st.push(node->left);
	}
	return nullptr;
}

bool IsComplete(const BiTree& tr)
{
	if (tr == nullptr)
		return true;
	bool flag = false;
	Queue<BiTree> q;
	q.push(tr);
	while (!q.empty())
	{
		BiTree node = q.front();
		q.pop();
		if (node->left)
		{
			if (flag)
				return false;
			q.push(node->left);
		}
		else
			flag = true;
		if (node->right)
		{
			if (flag)
				return false;
			q.push(node->right);
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