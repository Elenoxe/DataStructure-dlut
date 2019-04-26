#include <iostream>
#include "Stack.h"
#include <string>
#include "SeqQueue.h"
#include "BiTree.h"
#include "Vector.h"
using namespace std;
using namespace eleno;
void DisplayMenu();
void GoToRPNOperation();
string ToRPN(const string& expr);
int GetPrecedence(const char& op);
void GoToFibOperation();
void GoToTreeOperation();
void GoToSaddlePointSearch();
void WriteSaddlePoints(int** a, size_t row, size_t col);

int main()
{
	DisplayMenu();
	while (true)
	{
		cout << "[1-4]：";
		int choice;
		if (cin >> choice)
		{
			switch (choice)
			{
				case 1:
					GoToRPNOperation();
					// DisplayMenu();
					break;
				case 2:
					GoToFibOperation();
					// DisplayMenu();
					break;
				case 3:
					GoToTreeOperation();
					// DisplayMenu();
					break;
				case 4:
					return 0;
				default:
					cout << "请输入正确数字！" << endl;
			}
		}
		else
		{
			cout << "输入错误！" << endl;
		}
		cin.clear();
		cin.ignore(cin.rdbuf()->in_avail(), '\n');
	}
}

void DisplayMenu()
{
	cout << "输入数字进入选项：" << endl;
	cout << "1.求逆波兰式." << endl;
	cout << "2.循环队列计算斐波那契数列." << endl;
	cout << "3.二叉树操作." << endl;
	cout << "4.退出程序." << endl;
}

void GoToRPNOperation()
{
	cin.ignore(cin.rdbuf()->in_avail(), '\n');
	string line;
	cout << "请输入单字母变量和双目四则运算符及“(” 和“)” 组成的表达式，按回车键结束：" << endl;
	while (true)
	{
		try
		{
			getline(cin, line);
			string out = ToRPN(line);
			cout << "表达式的逆波兰式为：" << endl;
			cout << ToRPN(line) << endl;
			return;
		}
		catch (const runtime_error& e)
		{
			cout << e.what() << endl;
			cout << "请重新输入表达式：" << endl;
		}
	}
}

string ToRPN(const string& expr)
{
	string rtn;
	Stack<char> st;
	bool findOp = false;
	bool findAlpha = false;
	for (const char& ch : expr)
	{
		switch (ch)
		{
			case '+':
			case '-':
			case '*':
			case '/':
				findAlpha = false;
				if (findOp)
					throw runtime_error("无效的表达式.");
				findOp = true;
				while (!st.empty() && st.top() != '(' && GetPrecedence(ch) <= GetPrecedence(st.top()))
				{
					rtn += st.top();
					st.pop();
				}
				st.push(ch);
				break;
				// empty braces are allowed.
			case '(':
				findAlpha = false;
				st.push(ch);
				break;
			case ')':
				{
					findAlpha = false;
					bool done = false;
					while (!st.empty())
					{
						if (st.top() != '(')
						{
							rtn += st.top();
							st.pop();
						}
						else
						{
							st.pop();
							done = true;
							break;
						}
					}
					if (!done)
						throw runtime_error("无效的表达式.");
					break;
				}
			default:
				if (findOp)
					findOp = false;
				if (!isalpha(ch) || findAlpha)
					throw runtime_error("变量只允许以单字母命名.");
				findAlpha = true;
				rtn += ch;
		}
	}
	if (findOp)
		throw runtime_error("无效的表达式.");
	while (!st.empty())
	{
		if (st.top() == '(')
			throw runtime_error("无效的表达式.");
		rtn += st.top();
		st.pop();
	}
	return rtn;
}

int GetPrecedence(const char& op)
{
	switch (op)
	{
		case '+':
		case '-':
			return 1;
		case '*':
		case '/':
			return 2;
		default:
			return -1;
	}
}

void GoToFibOperation()
{
	cin.ignore(cin.rdbuf()->in_avail(), '\n');
	cout << "输入斐波那契序列的阶数k和所求序列的上限值max：";
	while (true)
	{
		int k;
		int max;
		if (cin >> k >> max)
		{
			if (k <= 0)
			{
				cout << "k必须为正整数." << endl;
				cout << "请重新输入斐波那契序列的阶数k和所求序列的上限值max：";
				continue;
			}
			SeqQueue<int> q;
			for (int i = 1; i < k; ++i)
				q.push(0);
			q.push(1);
			int prev = 1;
			int rear = 1;
			cout << "所求序列为：" << endl;
			while (true)
			{
				if (q.front() > max)
				{
					cout << endl;
					cout << "队中剩余元素为：" << endl;
					while (q.size() > 1)
					{
						cout << q.front() << ' ';
						q.pop();
					}
					cout << q.front() << endl;
					return;
				}
				rear = 2 * rear - prev;
				prev = q.front();
				cout << prev << ' ';
				q.pop();
				q.push(rear);
			}
		}
		else
		{
			cout << "无效的输入.请重新输入." << endl;
			cin.clear();
			cin.ignore(cin.rdbuf()->in_avail(), '\n');
		}
	}
}

void GoToTreeOperation()
{
	cin.ignore(cin.rdbuf()->in_avail(), '\n');
	cout << "请以先序遍历的顺序输入二叉树，以\"#\"表示空节点：" << endl;
	BiTreeNode<char>* root = ReadTree('#');
	cout << "二叉树的层次遍历顺序为：" << endl;
	LevelTraverse(root);
	cout << endl;
	cout << "二叉树的宽度为：" << GetWidth(root);
}

void GoToSaddlePointSearch()
{
	cin.ignore(cin.rdbuf()->in_avail(), '\n');
	cout << "请输入矩阵的行数和列数：" << endl;
	size_t row, col;

	while (true)
	{
		if (cin >> row >> col)
		{
			cout << "请输入矩阵：" << endl;
			int** a = new int* [row];
			for (size_t i = 0; i < row; ++i)
			{
				a[i] = new int[col];
				for (size_t j = 0; j < row; ++j)
					cin >> a[i][j];
			}
			WriteSaddlePoints(a, row, col);
			return;
		}
		else
		{
			cout << "无效的输入！" << endl;
			cout << "请重新输入矩阵的行数和列数：" << endl;
			cin.clear();
			cin.ignore(cin.rdbuf()->in_avail(), '\n');
		}
	}
}

void WriteSaddlePoints(int** a, size_t row, size_t col)
{
	Vector<size_t>* vMinIndexRow = new Vector<size_t>[row];
	Vector<size_t>* vMaxIndexCol = new Vector<size_t>[col];
	for (size_t i = 0; i < row; ++i)
		vMinIndexRow[i].push_back(0);
	for (size_t i = 0; i < col; ++i)
		vMaxIndexCol[i].push_back(0);
	for (size_t i = 0; i < row; ++i)
	{
		for (size_t j = 0; j < col; ++j)
		{
			if (a[i][j] == a[i][vMinIndexRow[i][0]])
			{
				vMinIndexRow[i].push_back(j);
			}
			else if (a[i][j] < a[i][vMinIndexRow[i][0]])
			{
				vMinIndexRow[i].clear();
				vMinIndexRow[i].push_back(j);
			}

		}
	}
}
