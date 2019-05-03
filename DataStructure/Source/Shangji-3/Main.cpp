#define _FOREST_

#ifdef _FOREST_
#include <iostream>
#include "Forest.h"
using namespace std;
Node<char>* ReadTree();

int main()
{
	cout << "���������������ɭ�ֵĶ�������ʾ����\"#\"��ʾ�սڵ㣺" << endl;
	Node<char>* forest = ReadTree();
	cout << "�������ɭ�ֵĽ��Ϊ��" << endl;
	InorderTraverse<char>(forest, [](Node<char> * node)->void { cout << node->data; });
	cout << endl;
	cout << "ɭ�ֵ�Ҷ�ӽڵ�����";
	cout << GetLeafCount(forest) << endl;
	cout << "�ö�����" << (IsComplete(forest) ? "��" : "����") << "��ȫ������." << endl;
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
	cout << "����ߵ�������";
	int n_edges;
	cin >> n_edges;
	for (int i = 1; i <= n_edges; ++i)
	{
		cout << "�����" << i << "�������ӵ������㣺" << endl;
		Graph<int>::size_type vex1, vex2;
		cin >> vex1 >> vex2;
		while (graph.vertices.size() <= vex1 || graph.vertices.size() <= vex2)
			graph.add_vertex(0);
		graph.add_edge(vex1, vex2);
	}
	cout << "ͼ�н��ĸ�����" << graph.vertices.size() << endl;
	for (Graph<int>::size_type i = 0; i < graph.vertices.size(); ++i)
	{
		cout << "����" << i << "���ӵĽ�㣺";
		for (auto edge : graph.vertices[i].edges)
			cout << edge.tail_index() << ' ';
		cout << endl;
	}
	cout << "ͼ��" << (graph.connected() ? "��ͨ��" : "����ͨ��") << '.' << endl;
	return 0;
}
#endif