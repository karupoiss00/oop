#pragma once
#include <iostream>
#include <optional>
#include "StringList.h"

CStringList::CStringList()
	: m_size(0)
{
	try
	{
		m_firstNode = new Node();
		m_lastNode = new Node();
		m_firstNode->next = m_lastNode;
		m_lastNode->prev = m_firstNode;
	}
	catch (std::exception const& e)
	{
		std::cout << e.what() << std::endl;
		throw e;
	}
}

CStringList::CStringList(CStringList&& list)
	: m_size(list.m_size)
{
	m_firstNode = list.m_firstNode;
	m_lastNode = list.m_lastNode;

	try
	{
		list.m_firstNode = new Node();
		list.m_lastNode = new Node();
		list.m_firstNode->next = list.m_lastNode;
		list.m_lastNode->prev = list.m_firstNode;
		list.m_size = 0;
	}
	catch (std::exception const& e)
	{
		std::cout << e.what() << std::endl;
		throw e;
	}
}

CStringList::CStringList(const CStringList& list)
	: CStringList()
{
	for (auto it = list.cbegin(); it != list.cend(); it++)
	{
		try
		{
			// [Solved] если выбросит исключение
			PushBack(*it);
		}
		catch (std::exception const& e)
		{
			std::cout << e.what() << std::endl;
			throw e;
		}
	}
}

CStringList::~CStringList()
{
	Clear();
	delete m_firstNode;
	delete m_lastNode;
	m_firstNode->next = nullptr;
	m_lastNode->prev = nullptr;
}

CStringList& CStringList::operator=(const CStringList& rhs)
{
	if (std::addressof(rhs) != this)
	{
		CStringList copy(rhs);
		std::swap(m_firstNode, copy.m_firstNode);
		std::swap(m_lastNode, copy.m_lastNode);
		std::swap(m_size, copy.m_size);
	}

	return *this;
}

void CStringList::Clear()
{
	NodePointer node = m_firstNode->next;

	while (node->next != nullptr)
	{
		m_firstNode->next = node->next;

		node->prev = nullptr;
		node->next = nullptr;
		delete node;

		node = m_firstNode->next;
	}

	m_size = 0;
}


CStringList::Iterator CStringList::begin()
{
	return Iterator(m_firstNode->next);
}


CStringList::Iterator CStringList::end()
{
	return Iterator(m_lastNode);
}


CStringList::ConstIterator CStringList::cbegin() const
{
	return ConstIterator(m_firstNode->next);
}


CStringList::ConstIterator CStringList::cend() const
{
	return ConstIterator(m_lastNode);
}


CStringList::ReverseIterator CStringList::rbegin()
{
	return std::make_reverse_iterator(end());
}


CStringList::ReverseIterator CStringList::rend()
{
	return std::make_reverse_iterator(begin());
}

CStringList::ConstReverseIterator CStringList::rcbegin() const
{
	return std::make_reverse_iterator(cend());
}


CStringList::ConstReverseIterator CStringList::rcend() const
{
	return std::make_reverse_iterator(cbegin());
}


CStringList::Iterator CStringList::Insert(Iterator const& pos, std::string const& data)
{
	auto newNode = new Node(data, nullptr, nullptr);

	NodePointer beforeNew = pos.m_pNode->prev;
	NodePointer afterNew = beforeNew->next;

	newNode->prev = beforeNew;
	newNode->next = afterNew;

	beforeNew->next = newNode;
	afterNew->prev = newNode;

	++m_size;

	return Iterator(newNode);
}


CStringList::Iterator CStringList::Erase(Iterator const& pos)
{
	NodePointer beforePos = pos.m_pNode->prev;
	NodePointer afterPos = pos.m_pNode->next;

	pos.m_pNode->prev = nullptr;
	pos.m_pNode->next = nullptr;

	beforePos->next = afterPos;
	afterPos->prev = beforePos;

	--m_size;

	return Iterator(afterPos);
}


void CStringList::PushFront(const std::string& data)
{
	auto newNode = new Node(data, m_firstNode, m_firstNode->next);

	m_firstNode->next = newNode;
	newNode->next->prev = newNode;

	++m_size;
}


void CStringList::PushBack(const std::string& data)
{
	auto newNode = new Node(data, m_lastNode->prev, m_lastNode);

	m_lastNode->prev = newNode;
	newNode->prev->next = newNode;

	++m_size;
}


size_t CStringList::GetSize() const
{
	return m_size;
}


bool CStringList::IsEmpty() const
{
	return m_size == 0;
}
