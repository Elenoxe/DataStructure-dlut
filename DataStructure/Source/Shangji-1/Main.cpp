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
		cout << "[1-3]��";
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
	cout << "1.һԪ����ʽ����." << endl;
	cout << "2.������A��B��C����" << endl;
	cout << "3.�˳�����" << endl;
}

void GoToPolyOperation()
{
	system("cls");
	bool input = false;
	Poly pa, pb;
	cout << "��������ִ�в�����" << endl;
	cout << "1.�������ʽPa." << endl;
	cout << "2.��Pa����." << endl;
	cout << "3.�����Ա�����ֵ����Pa" << endl;
	cout << "4.�������ʽPb����Pa+Pb" << endl;
	cout << "5.������һ��" << endl;
	while(true)
	{	
		cout << "[1-5]��";
		int choice;
		if (cin >> choice)
		{
			switch (choice)
			{
				case 1:
					cout << "�������������ʽ�����ϵ����ָ������������\",\"�ָ�����\"#\"����." << endl;
					ReadPoly(pa);
					input = true;
					cout << "Pa=";
					PrintPoly(pa);
					cout << endl;
					break;
				case 2:
					if (!input)
						cout << "��δ��ȷ����Pa." << endl;
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
						cout << "��δ��ȷ����Pa." << endl;
					else
					{
						cout << "�������Ա�����ֵ��" << endl;
						Poly::variable_value_type x;
						if (cin >> x)
							cout << "Pa(" << x << ")=" << pa.subs(x) << endl;
						else
							cout << "��Ч���Ա���ֵ." << endl;
					}
					break;
				case 4:
					if (!input)
						cout << "��δ��ȷ����Pa." << endl;
					else
					{
						cout << "�������������ʽ�����ϵ����ָ������������\",\"�ָ�����\"#\"����." << endl;
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

void GoToLinkListOperation()
{
	SortedForwardList<int> a, b, c;
	cout << "���������뵥����A��Ԫ�أ����ͣ�,����\"#\"������" << endl;
	ReadList<int>(a);
	cout << "���������뵥����B��Ԫ�أ����ͣ�,����\"#\"������" << endl;
	ReadList<int>(b);
	cout << "���������뵥����C��Ԫ�أ����ͣ�,����\"#\"������" << endl;
	ReadList<int>(c);
	cout << endl;
	cout << "������A��";
	PrintList<int>(a);
	cout << endl;
	cout << "������B��";
	PrintList<int>(b);
	cout << endl;
	cout << "������C��";
	PrintList<int>(c);
	cout << endl;
	DeleteSameFromListAscending<int>(a, b, c);
	cout << "ɾ��B��C����Ԫ�غ�ĵ�����A��";
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
					throw runtime_error("��Ч������.");
				if (ch != sep && ch != end)
					throw runtime_error("�Ƿ��ķָ����������.");
				poly.push(Term(coef, exp));
				if (ch == end)
					return;
			}
		}
		catch (const runtime_error& error)
		{
			cout << error.what() << endl;
			cout << "�������������ʽ��" << endl;
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
					throw runtime_error("��Ч������.");
				}
			}
		}
		catch (const runtime_error& error)
		{
			cout << error.what() << endl;
			cout << "���������뵥����" << endl;
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
