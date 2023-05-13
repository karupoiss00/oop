#pragma once
#include <optional>
#include "CMyListIterator.h"

template<typename Type>
class CList
{
	struct Node;
	using NodePointer = std::shared_ptr<Node>;
	
	struct Node
	{
		Node()
			: prev(nullptr), next(nullptr)
		{
		}
	
		Node(const Type& data, NodePointer prev, NodePointer next)
			: data(data), prev(prev), next(next)
		{
		}

		Node(const Type&& data, NodePointer prev, NodePointer next)
			: data(data), prev(prev), next(next)
		{
		}

		std::optional<Type> data;

		std::shared_ptr<Node> prev;
		std::shared_ptr<Node> next;
	};

public:
	using Iterator = CListIterator<Node, Type>;
	using ConstIterator = CListIterator<Node, const Type>;

	using ReverseIterator = std::reverse_iterator<Iterator>;
	using ConstReverseIterator = std::reverse_iterator<ConstIterator>;

	CList();
	CList(const CList& list);
	~CList();
	// ����������� move-�����������
	
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

// �������� ����� �����
	NodePointer m_firstNode;
	NodePointer m_lastNode;
};

template <typename Type>
CList<Type>::CList()
	: m_size(0), m_firstNode(std::make_shared<Node>()), m_lastNode(std::make_shared<Node>())
{
	m_firstNode->next = m_lastNode;
	m_lastNode->prev = m_firstNode;
}

template <typename Type>
CList<Type>::CList(const CList& list)
	: CList()
{
	for (auto it = list.cbegin(); it != list.cend(); it++)
	{
		// ���� �������� ����������
		PushBack(*it);
	}
}

template <typename Type>
CList<Type>::~CList()
{
	Clear();
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
		node->next->prev = m_firstNode;

		node->prev = nullptr;
		node->next = nullptr;

		node = m_firstNode->next;
	}

	m_size = 0;
}

template <typename Type>
typename CList<Type>::Iterator CList<Type>::begin()
{
	return Iterator(m_firstNode->next.get());
}

template <typename Type>
typename CList<Type>::Iterator CList<Type>::end()
{
	return Iterator(m_lastNode.get());
}

template <typename Type>
typename CList<Type>::ConstIterator CList<Type>::cbegin() const
{
	return ConstIterator(m_firstNode->next.get());
}

template <typename Type>
typename CList<Type>::ConstIterator CList<Type>::cend() const
{
	return ConstIterator(m_lastNode.get());
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
	auto newNode = std::make_shared<Node>(data, nullptr, nullptr);

	NodePointer beforeNew = pos.m_pNode->prev;
	NodePointer afterNew = beforeNew->next;

	newNode->prev = beforeNew;
	newNode->next = afterNew;

	beforeNew->next = newNode;
	afterNew->prev = newNode;

	++m_size;

	return Iterator(newNode.get());
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

	return Iterator(afterPos.get());
}

template <typename Type>
void CList<Type>::PushFront(const Type& data)
{
	auto newNode = std::make_shared<Node>(data, m_firstNode, m_firstNode->next);

	m_firstNode->next = newNode;
	newNode->next->prev = newNode;

	++m_size;
}

template <typename Type>
void CList<Type>::PushBack(const Type& data)
{
	auto newNode = std::make_shared<Node>(data, m_lastNode->prev, m_lastNode);

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
	return m_firstNode->next == m_lastNode;
}
