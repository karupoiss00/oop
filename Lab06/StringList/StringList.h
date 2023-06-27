#pragma once
#include <iostream>
#include <string>
#include "StringListIterator.h"

class CStringList
{
	struct Node;
	using NodePointer = Node*;

	struct Node
	{
		Node()
			: prev(nullptr), next(nullptr)
		{
		}

		Node(const std::string& data, Node* prev, Node* next)
			: data(data), prev(prev), next(next)
		{
		}

		Node(const std::string&& data, Node* prev, Node* next)
			: data(data), prev(prev), next(next)
		{
		}

		std::string data;

		Node* prev;
		Node* next;
	};

public:
	using Iterator = CStringListIterator<Node, std::string>;
	using ConstIterator = CStringListIterator<Node, const std::string>;

	using ReverseIterator = std::reverse_iterator<Iterator>;
	using ConstReverseIterator = std::reverse_iterator<ConstIterator>;

	CStringList();
	CStringList(const CStringList& list);
	CStringList(CStringList&& list);
	~CStringList();

	Iterator begin();
	Iterator end();
	ConstIterator cbegin() const;
	ConstIterator cend() const;

	ReverseIterator rbegin();
	ReverseIterator rend();
	ConstReverseIterator rcbegin() const;
	ConstReverseIterator rcend() const;

	Iterator Insert(Iterator const& pos, std::string const& data);
	Iterator Erase(Iterator const& pos);

	void PushFront(const std::string& data);
	void PushBack(const std::string& data);

	size_t GetSize() const;
	bool IsEmpty() const;

	void Clear();

	CStringList& operator=(const CStringList& rhs);
private:
	size_t m_size;

	NodePointer m_firstNode;
	NodePointer m_lastNode;
};