#pragma once
#include <iostream>
#include <exception>
#include <memory>
#include <iterator>
#include <cassert>

template<typename Type>
class CList;

template<typename Node, typename Data>
class CListIterator : public std::iterator<std::bidirectional_iterator_tag, Data>
{
	template<typename Type>
	friend class CList;
public:
	Data& operator*() const;
	Data* operator->() const;

	bool operator==(const CListIterator& it) const;
	bool operator!=(const CListIterator& it) const;

	CListIterator& operator++();
	CListIterator& operator--();

	CListIterator operator++(int);
	CListIterator operator--(int);

private:
	CListIterator(Node* value);

	Node* m_pNode;
};

template <typename Node, typename Data>
CListIterator<Node, Data>::CListIterator(Node* value)
	: m_pNode(value)
{}

template <typename Node, typename Data>
bool CListIterator<Node, Data>::operator==(const CListIterator& it) const
{
	return m_pNode == it.m_pNode;
}

template <typename Node, typename Data>
bool CListIterator<Node, Data>::operator!=(const CListIterator& it) const
{
	return m_pNode != it.m_pNode;
}

template <typename Node, typename Data>
Data& CListIterator<Node, Data>::operator*() const
{
	return m_pNode->data.value();
}

template <typename Node, typename Data>
Data* CListIterator<Node, Data>::operator->() const
{
	return *m_pNode->data;
}

template <typename Node, typename Data>
CListIterator<Node, Data>& CListIterator<Node, Data>::operator--()
{
	assert(m_pNode->prev != nullptr);
	m_pNode = m_pNode->prev.get();
	return *this;
}

template <typename Node, typename Data>
CListIterator<Node, Data>& CListIterator<Node, Data>::operator++()
{
	assert(m_pNode->next != nullptr);
	m_pNode = m_pNode->next.get();
	return *this;
}

template <typename Node, typename Data>
CListIterator<Node, Data> CListIterator<Node, Data>::operator--(int)
{
	CListIterator tmp(*this);
	--(*this);
	return tmp;
}

template <typename Node, typename Data>
CListIterator<Node, Data> CListIterator<Node, Data>::operator++(int)
{
	CListIterator tmp(*this);
	++(*this);
	return tmp;
}