#include <iostream>
#include <vector>
#include <typeinfo>
#include "CMyList.h"

using namespace std;

template <typename T>
void DemoList(const vector<T>& data);
template <typename T>
void PrintList(const CList<T>& list);

int main(int argc, char* argv[])
{
	vector<string> stringData =
	{
		"first",
		"second",
		"third"
	};
	vector<int> intData = { 1, 2, 3 };

	DemoList(stringData);
	DemoList(intData);

	return 0;
}

template <typename T>
void DemoList(const vector<T>& data)
{
	if (data.size() != 3)
	{
		return;
	}

	CList<T> list;

	cout << endl << "Demo of template class CList for type of ";
	cout << typeid(list).name() << endl << endl;
	PrintList(list);

	cout << endl << endl << "CList<T>::PushFront inserts the given element value to the beginning of the list";
	list.PushFront(data[0]);
	PrintList(list);

	cout << endl << endl << "CList<T>::PushBack inserts the given element value to the end of the list" << endl;
	list.PushBack(data[2]);
	PrintList(list);

	cout << endl << endl << "CList<T>::Insert inserts element at the specified location in the container" << endl;
	auto it = list.begin();
	++it;
	it = list.Insert(it, data[1]);
	PrintList(list);

	cout << endl << endl << "CList<T>::Erase removes specified element from the container" << endl;
	list.Erase(it);
	PrintList(list);

	cout << endl << endl << "CList<T>::Clear removes all elements from the container" << endl;
	list.Clear();
	PrintList(list);

	cout << endl;
}

template <typename T>
void PrintList(const CList<T>& list)
{
	cout << "Current state of list";

	if (list.IsEmpty())
	{
		cout << ": empty";
		return;
	}

	cout << endl << "  Size: " << list.GetSize();
	cout << endl << "  Data:";

	for (auto it = list.cbegin(); it != list.cend(); ++it)
	{
		cout << endl << "    " << *it;
	}
}