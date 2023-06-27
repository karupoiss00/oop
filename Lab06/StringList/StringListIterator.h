#pragma once
#include <iostream>
#include <exception>
#include <memory>
#include <iterator>
#include <cassert>

class CStringList;

template<typename Node, typename Data>
class CStringListIterator
{
	friend class CStringList;
public:
	using iterator_category = std::bidirectional_iterator_tag;
	using difference_type = std::ptrdiff_t;
	using value_type = Data;
	using pointer = Data*;
	using reference = Data&;

	Data& operator*() const;
	Data* operator->() const;

	bool operator==(const CStringListIterator& it) const;
	bool operator!=(const CStringListIterator& it) const;

	CStringListIterator& operator++();
	CStringListIterator& operator--();

	CStringListIterator operator++(int);
	CStringListIterator operator--(int);
	CStringListIterator<Node, Data>& operator=(const CStringListIterator<Node, Data>& rhs);
private:
	CStringListIterator(Node* value);

	Node* m_pNode;
};

template <typename Node, typename Data>
CStringListIterator<Node, Data>::CStringListIterator(Node* value)
	: m_pNode(value)
{}
template <typename Node, typename Data>
CStringListIterator<Node, Data>& CStringListIterator<Node, Data>::operator=(const CStringListIterator<Node, Data>& rhs)
{
	m_pNode = rhs.m_pNode;
	return *this;
}

template <typename Node, typename Data>
bool CStringListIterator<Node, Data>::operator==(const CStringListIterator& it) const
{
	return m_pNode == it.m_pNode;
}

template <typename Node, typename Data>
bool CStringListIterator<Node, Data>::operator!=(const CStringListIterator& it) const
{
	return m_pNode != it.m_pNode;
}

template <typename Node, typename Data>
Data& CStringListIterator<Node, Data>::operator*() const
{
	return m_pNode->data;
}

template <typename Node, typename Data>
Data* CStringListIterator<Node, Data>::operator->() const
{
	return *m_pNode->data;
}

template <typename Node, typename Data>
CStringListIterator<Node, Data>& CStringListIterator<Node, Data>::operator--()
{
	assert(m_pNode->prev != nullptr);
	m_pNode = m_pNode->prev;
	return *this;
}

template <typename Node, typename Data>
CStringListIterator<Node, Data>& CStringListIterator<Node, Data>::operator++()
{
	assert(m_pNode->next != nullptr);
	m_pNode = m_pNode->next;
	return *this;
}

template <typename Node, typename Data>
CStringListIterator<Node, Data> CStringListIterator<Node, Data>::operator--(int)
{
	CStringListIterator tmp(*this);
	--(*this);
	return tmp;
}

template <typename Node, typename Data>
CStringListIterator<Node, Data> CStringListIterator<Node, Data>::operator++(int)
{
	CStringListIterator tmp(*this);
	++(*this);
	return tmp;
}