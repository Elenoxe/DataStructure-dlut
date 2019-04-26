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
		cout << "[1-4]��";
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
					cout << "��������ȷ���֣�" << endl;
			}
		}
		else
		{
			cout << "�������" << endl;
		}
		cin.clear();
		cin.ignore(cin.rdbuf()->in_avail(), '\n');
	}
}

void DisplayMenu()
{
	cout << "�������ֽ���ѡ�" << endl;
	cout << "1.���沨��ʽ." << endl;
	cout << "2.ѭ�����м���쳲���������." << endl;
	cout << "3.����������." << endl;
	cout << "4.�˳�����." << endl;
}

void GoToRPNOperation()
{
	cin.ignore(cin.rdbuf()->in_avail(), '\n');
	string line;
	cout << "�����뵥��ĸ������˫Ŀ�������������(�� �͡�)�� ��ɵı��ʽ�����س���������" << endl;
	while (true)
	{
		try
		{
			getline(cin, line);
			string out = ToRPN(line);
			cout << "���ʽ���沨��ʽΪ��" << endl;
			cout << ToRPN(line) << endl;
			return;
		}
		catch (const runtime_error& e)
		{
			cout << e.what() << endl;
			cout << "������������ʽ��" << endl;
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
					throw runtime_error("��Ч�ı��ʽ.");
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
						throw runtime_error("��Ч�ı��ʽ.");
					break;
				}
			default:
				if (findOp)
					findOp = false;
				if (!isalpha(ch) || findAlpha)
					throw runtime_error("����ֻ�����Ե���ĸ����.");
				findAlpha = true;
				rtn += ch;
		}
	}
	if (findOp)
		throw runtime_error("��Ч�ı��ʽ.");
	while (!st.empty())
	{
		if (st.top() == '(')
			throw runtime_error("��Ч�ı��ʽ.");
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
	cout << "����쳲��������еĽ���k���������е�����ֵmax��";
	while (true)
	{
		int k;
		int max;
		if (cin >> k >> max)
		{
			if (k <= 0)
			{
				cout << "k����Ϊ������." << endl;
				cout << "����������쳲��������еĽ���k���������е�����ֵmax��";
				continue;
			}
			SeqQueue<int> q;
			for (int i = 1; i < k; ++i)
				q.push(0);
			q.push(1);
			int prev = 1;
			int rear = 1;
			cout << "��������Ϊ��" << endl;
			while (true)
			{
				if (q.front() > max)
				{
					cout << endl;
					cout << "����ʣ��Ԫ��Ϊ��" << endl;
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
			cout << "��Ч������.����������." << endl;
			cin.clear();
			cin.ignore(cin.rdbuf()->in_avail(), '\n');
		}
	}
}

void GoToTreeOperation()
{
	cin.ignore(cin.rdbuf()->in_avail(), '\n');
	cout << "�������������˳���������������\"#\"��ʾ�սڵ㣺" << endl;
	BiTreeNode<char>* root = ReadTree('#');
	cout << "�������Ĳ�α���˳��Ϊ��" << endl;
	LevelTraverse(root);
	cout << endl;
	cout << "�������Ŀ��Ϊ��" << GetWidth(root);
}

void GoToSaddlePointSearch()
{
	cin.ignore(cin.rdbuf()->in_avail(), '\n');
	cout << "����������������������" << endl;
	size_t row, col;

	while (true)
	{
		if (cin >> row >> col)
		{
			cout << "���������" << endl;
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
			cout << "��Ч�����룡" << endl;
			cout << "��������������������������" << endl;
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
