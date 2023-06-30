#pragma once
#include <memory>
#include "CMyListIterator.h"

template<typename Type>
class CList
{
	struct Node;
	// [Solved] использовать обычные указатели
	using NodePointer = Node*;
	
	struct Node 
	{
		template <typename U>
		void Create(U&& value, NodePointer prev_, NodePointer next_)
		{
			next = next_;
			prev = prev_;
			std::construct_at(&GetValue(), std::forward<U>(value));
		}

		void Destroy()
		{
			prev = nullptr;
			next = nullptr;
			std::destroy_at(&GetValue());
		}

		Type& GetValue()
		{
			return *reinterpret_cast<Type*> (buffer);
		}

		alignas(Type) char buffer[sizeof(Type)];
		NodePointer next;
		NodePointer prev;
	};

public:
	using Iterator = CListIterator<Node, Type>;
	using ConstIterator = CListIterator<Node, const Type>;

	using ReverseIterator = std::reverse_iterator<Iterator>;
	using ConstReverseIterator = std::reverse_iterator<ConstIterator>;

	CList();
	CList(const CList& list);
	// [Solved] реализовать move-конструктор
	CList(CList&& list);
	~CList();

	Iterator begin();
	Iterator end();
	ConstIterator cbegin() const;
	ConstIterator cend() const;

	ReverseIterator rbegin();
	ReverseIterator rend();
	ConstReverseIterator rcbegin() const;
	ConstReverseIterator rcend() const;
	
	Iterator Insert(Iterator const& pos, Type const& data);
	Iterator Erase(Iterator const& pos);

	void PushFront(const Type& data);
	void PushBack(const Type& data);

	size_t GetSize() const;
	bool IsEmpty() const;

	void Clear();

	CList<Type>& operator=(const CList<Type> & rhs);
	ConstIterator& operator=(const Iterator& rhs);
private:
	size_t m_size;

	NodePointer m_firstNode;
	NodePointer m_lastNode;
};

template <typename Type>
CList<Type>::CList()
	: m_size(0)
{
	try
	{
		m_firstNode = new Node();
		m_lastNode = new Node();
		m_firstNode->next = m_lastNode;
		m_lastNode->prev = m_firstNode;
	}
	catch (...)
	{
		delete m_firstNode;
		delete m_lastNode;
		throw;
	}
}

template <typename Type>
CList<Type>::CList(CList&& list)
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
	}
	catch (...)
	{ 
		delete list.m_firstNode;
		delete list.m_lastNode;
		throw;
	}
}

template <typename Type>
CList<Type>::CList(const CList& list)
	: CList()
{
	for (auto it = list.cbegin(); it != list.cend(); it++)
	{
		try
		{
			// [Solved] если выбросит исключение
			PushBack(*it);
		}
		catch (...)
		{
			Clear();
			throw;
		}
	}
}

template <typename Type>
CList<Type>::~CList()
{
	Clear();
	delete m_firstNode;
	delete m_lastNode;
	m_firstNode->next = nullptr;
	m_lastNode->prev = nullptr;
}

template <typename Type>
CList<Type>& CList<Type>::operator=(const CList<Type>& rhs)
{
	if (std::addressof(rhs) != this)
	{
		CList<Type> copy(rhs);
		std::swap(m_firstNode, copy.m_firstNode);
		std::swap(m_lastNode, copy.m_lastNode);
		std::swap(m_size, copy.m_size);
	}

	return *this;
}

template <typename Type>
void CList<Type>::Clear()
{
	NodePointer node = m_firstNode->next;

	while (node->next != nullptr)
	{
		m_firstNode->next = node->next;
		
		node->Destroy();
		delete node;

		node = m_firstNode->next;
	}

	m_size = 0;
}

template <typename Type>
typename CList<Type>::Iterator CList<Type>::begin()
{
	return Iterator(m_firstNode->next);
}

template <typename Type>
typename CList<Type>::Iterator CList<Type>::end()
{
	return Iterator(m_lastNode);
}

template <typename Type>
typename CList<Type>::ConstIterator CList<Type>::cbegin() const
{
	return ConstIterator(m_firstNode->next);
}

template <typename Type>
typename CList<Type>::ConstIterator CList<Type>::cend() const
{
	return ConstIterator(m_lastNode);
}

template <typename Type>
typename CList<Type>::ReverseIterator CList<Type>::rbegin()
{
	return std::make_reverse_iterator(end());
}

template <typename Type>
typename CList<Type>::ReverseIterator CList<Type>::rend()
{
	return std::make_reverse_iterator(begin());
}

template <typename Type>
typename CList<Type>::ConstReverseIterator CList<Type>::rcbegin() const
{
	return std::make_reverse_iterator(cend());
}

template <typename Type>
typename CList<Type>::ConstReverseIterator CList<Type>::rcend() const
{
	return std::make_reverse_iterator(cbegin());
}

template <typename Type>
typename CList<Type>::Iterator CList<Type>::Insert(Iterator const& pos, Type const& data)
{
	try
	{
		auto newNode = new Node();
	}
	catch (...)
	{
		delete newNode;
		throw;
	}
	newNode->Create(data, nullptr, nullptr);

	NodePointer beforeNew = pos.m_pNode->prev;
	NodePointer afterNew = beforeNew->next;

	newNode->prev = beforeNew;
	newNode->next = afterNew;

	beforeNew->next = newNode;
	afterNew->prev = newNode;

	++m_size;

	return Iterator(newNode);
}

template <typename Type>
typename CList<Type>::Iterator CList<Type>::Erase(Iterator const& pos)
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

template <typename Type>
void CList<Type>::PushFront(const Type& data)
{
	try
	{
		auto newNode = new Node();
	}
	catch (...)
	{
		delete newNode;
		throw;
	}
	newNode->Create(data, m_firstNode, m_firstNode->next);

	m_firstNode->next = newNode;
	newNode->next->prev = newNode;

	++m_size;
}

template <typename Type>
void CList<Type>::PushBack(const Type& data)
{
	try
	{
		auto newNode = new Node();
	}
	catch (...)
	{
		delete newNode;
		throw;
	}

	
	newNode->Create(data, m_lastNode->prev, m_lastNode);

	m_lastNode->prev = newNode;
	newNode->prev->next = newNode;

	++m_size;
}

template <typename Type>
size_t CList<Type>::GetSize() const
{
	return m_size;
}

template <typename Type>
bool CList<Type>::IsEmpty() const
{
	return m_size == 0;
}
