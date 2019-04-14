#include <iostream>
#include <cstdlib>
#include "Poly.h"
using namespace eleno;
using namespace std;
void DisplayMenu();
void GoToPolyOperation();
void GoToLinkListOperation();
void ReadPoly(Poly& poly, const char& sep = ',', const char& end = '#');
void PrintPoly(const Poly& poly);
template <class T>
void ReadList(SortedForwardList<T>& list, const char& end = '#');
template <class T>
void PrintList(const SortedForwardList<T>& list);
template <class T>
void DeleteSameFromListAscending(SortedForwardList<T>& from, const SortedForwardList<T> &first, const SortedForwardList<T> &second);
int main()
{
	DisplayMenu();
	while (true)
	{
		cout << "[1-3]：";
		int choice;
		if (cin >> choice)
		{
			switch (choice)
			{
				case 1:
					GoToPolyOperation();
					DisplayMenu();
					break;
				case 2:
					GoToLinkListOperation();
					// DisplayMenu();
					break;
				case 3:
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
	cout << "1.一元多项式操作." << endl;
	cout << "2.单链表A，B，C操作" << endl;
	cout << "3.退出程序" << endl;
}

void GoToPolyOperation()
{
	system("cls");
	bool input = false;
	Poly pa, pb;
	cout << "输入数字执行操作：" << endl;
	cout << "1.输入多项式Pa." << endl;
	cout << "2.将Pa逆置." << endl;
	cout << "3.输入自变量的值，求Pa" << endl;
	cout << "4.输入多项式Pb，求Pa+Pb" << endl;
	cout << "5.返回上一级" << endl;
	while(true)
	{	
		cout << "[1-5]：";
		int choice;
		if (cin >> choice)
		{
			switch (choice)
			{
				case 1:
					cout << "请依次输入多项式各项的系数和指数，项与项以\",\"分隔，以\"#\"结束." << endl;
					ReadPoly(pa);
					input = true;
					cout << "Pa=";
					PrintPoly(pa);
					cout << endl;
					break;
				case 2:
					if (!input)
						cout << "尚未正确输入Pa." << endl;
					else
					{
						pa.reverse();
						cout << "Pa=";
						PrintPoly(pa);
						cout << endl;
					}
					break;
				case 3:
					if (!input)
						cout << "尚未正确输入Pa." << endl;
					else
					{
						cout << "请输入自变量的值：" << endl;
						Poly::variable_value_type x;
						if (cin >> x)
							cout << "Pa(" << x << ")=" << pa.subs(x) << endl;
						else
							cout << "无效的自变量值." << endl;
					}
					break;
				case 4:
					if (!input)
						cout << "尚未正确输入Pa." << endl;
					else
					{
						cout << "请依次输入多项式各项的系数和指数，项与项以\",\"分隔，以\"#\"结束." << endl;
						ReadPoly(pb);
						cout << "Pb=";
						PrintPoly(pb);
						cout << endl;
						Poly sum = pa + pb;
						cout << "Pa+Pb=";
						PrintPoly(sum);
						cout << endl;
					}
					break;
				case 5:
					system("cls");
					return;
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

void GoToLinkListOperation()
{
	SortedForwardList<int> a, b, c;
	cout << "请依次输入单链表A的元素（整型）,输入\"#\"结束：" << endl;
	ReadList<int>(a);
	cout << "请依次输入单链表B的元素（整型）,输入\"#\"结束：" << endl;
	ReadList<int>(b);
	cout << "请依次输入单链表C的元素（整型）,输入\"#\"结束：" << endl;
	ReadList<int>(c);
	cout << endl;
	cout << "单链表A：";
	PrintList<int>(a);
	cout << endl;
	cout << "单链表B：";
	PrintList<int>(b);
	cout << endl;
	cout << "单链表C：";
	PrintList<int>(c);
	cout << endl;
	DeleteSameFromListAscending<int>(a, b, c);
	cout << "删除B和C公共元素后的单链表A：";
	PrintList<int>(a);
	cout << endl << endl;
}

void ReadPoly(Poly& poly, const char& sep, const char& end)
{
	while(true)
	{
		poly.clear();
		try
		{
			while (true)
			{
				Term::coef_type coef;
				Term::exp_type exp;
				char ch;
				if (!(cin >> coef >> exp >> ch))
					throw runtime_error("无效的输入.");
				if (ch != sep && ch != end)
					throw runtime_error("非法的分隔符或结束符.");
				poly.push(Term(coef, exp));
				if (ch == end)
					return;
			}
		}
		catch (const runtime_error& error)
		{
			cout << error.what() << endl;
			cout << "请重新输入多项式：" << endl;
		}
		cin.clear();
		cin.ignore(cin.rdbuf()->in_avail(), '\n');
	}
}
void PrintPoly(const Poly& poly)
{
	if (poly.empty())
		cout << "0";
	for (auto iter = poly.cbegin(); iter != poly.cend(); ++iter)
	{
		if ((*iter).exp == 0)
			cout << (*iter).coef;
		else
			cout << (*iter).coef << "x^" << (*iter).exp;
		if (iter + 1 != poly.cend() && (*(iter + 1)).coef >= 0)
			cout << "+";
	}
}
template <class T>
void ReadList(SortedForwardList<T>& list,const char& end)
{
	while(true)
	{
		list.clear();
		try
		{
			while(true)
			{
				T data;
				char ch;
				if(cin >> data)
				{
					list.push(data);
				}
				else
				{
					cin.clear();
					cin >> ch;
					if (ch == end)
						return;
					throw runtime_error("无效的输入.");
				}
			}
		}
		catch (const runtime_error& error)
		{
			cout << error.what() << endl;
			cout << "请重新输入单链表：" << endl;
		}
		cin.clear();
		cin.ignore(cin.rdbuf()->in_avail(), '\n');
	}
}
template <class T>
void PrintList(const SortedForwardList<T>& list)
{
	for (const auto& elem : list)
		cout << elem << ' ';
}

template <class T>
void DeleteSameFromListAscending(SortedForwardList<T>& from, const SortedForwardList<T>& first, const SortedForwardList<T>& second)
{
	auto prev = from.cbefore_begin();
	auto curr = from.cbegin();
	auto iter_first = first.cbegin();
	auto iter_second = second.cbegin();
	while (iter_first != first.cend() && iter_second != second.cend())
	{
		if (*iter_first == *iter_second)
		{
			while (*curr <= *iter_first)
			{
				if (*curr == *iter_first)
				{
					curr = from.erase_after(prev);
					if (curr == from.cend())
						return;
					continue;
				}
				++prev;
				++curr;
				if (curr == from.cend())
					return;
			}
			++iter_first;
			++iter_second;
		}
		else
		{
			auto& smaller = *iter_first < *iter_second ? iter_first : iter_second;
			++smaller;
		}
	}
}
