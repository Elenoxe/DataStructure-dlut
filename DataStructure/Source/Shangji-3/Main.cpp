#define _FOREST_

#ifdef _FOREST_
#include <iostream>
#include "Forest.h"
using namespace std;
Node<char>* ReadTree();

int main()
{
	cout << "请以先序遍历输入森林的二叉树表示，以\"#\"表示空节点：" << endl;
	Node<char>* forest = ReadTree();
	cout << "中序遍历森林的结果为：" << endl;
	InorderTraverse<char>(forest, [](Node<char> * node)->void { cout << node->data; });
	cout << endl;
	cout << "森林的叶子节点数：";
	cout << GetLeafCount(forest) << endl;
	cout << "该二叉树" << (IsComplete(forest) ? "是" : "不是") << "完全二叉树." << endl;
	return 0;
}

Node<char>* ReadTree()
{
	Node<char>* node = nullptr;
	char ch;
	cin >> ch;
	if (ch != '#')
	{
		node = new Node<char>;
		node->data = ch;
		node->first_child = ReadTree();
		node->next_sibling = ReadTree();
	}
	return node;
}
#endif

#ifdef _GRAPH_
#include <iostream>
#include "Graph.h"
using namespace std;

int main()
{
	Graph<int> graph(Graph<int>::UNDIRECTED);
	cout << "输入边的条数：";
	int n_edges;
	cin >> n_edges;
	for (int i = 1; i <= n_edges; ++i)
	{
		cout << "输入第" << i << "条边连接的两个点：" << endl;
		Graph<int>::size_type vex1, vex2;
		cin >> vex1 >> vex2;
		while (graph.vertices.size() <= vex1 || graph.vertices.size() <= vex2)
			graph.add_vertex(0);
		graph.add_edge(vex1, vex2);
	}
	cout << "图中结点的个数：" << graph.vertices.size() << endl;
	for (Graph<int>::size_type i = 0; i < graph.vertices.size(); ++i)
	{
		cout << "与结点" << i << "连接的结点：";
		for (auto edge : graph.vertices[i].edges)
			cout << edge.tail_index() << ' ';
		cout << endl;
	}
	cout << "图是" << (graph.connected() ? "连通的" : "非连通的") << '.' << endl;
	return 0;
}
#endif