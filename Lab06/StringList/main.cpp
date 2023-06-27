#include <iostream>
#include <vector>
#include <typeinfo>
#include "StringList.h"

using namespace std;

void DemoList(const vector<string>& data);
void PrintList(const CStringList& list);

int main(int argc, char* argv[])
{
	vector<string> stringData =
	{
		"first",
		"second",
		"third"
	};

	DemoList(stringData);

	return 0;
}

void DemoList(const vector<string>& data)
{
	if (data.size() != 3)
	{
		return;
	}

	CStringList list;

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

void PrintList(const CStringList& list)
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