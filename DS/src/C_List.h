#ifndef __C_LIST_H__
#define __C_LIST_H__

#include <vector>
#include <iostream>

namespace nsC_DS { namespace nsC_List {
template<typename T>
struct Node
{
	T		m_data{};
	Node	*m_pNext{};
	Node	*m_pPrev{};

	Node(T value) :
		m_data(value)
	{}
};

template<typename T>
struct List
{
	int			m_size{};
	Node<T>		*m_pHead{};
	Node<T>		*m_pTail{};
};

template<typename T>
List<T>* createList()
{
	return new List<T>();
}

template<typename T>
int size(List<T> *list)
{
	return list ? list->m_size : 0;
}

template<typename T>
void deleteList(List<T> *&list)
{
	if (list)
	{
		int size = list->m_size;
		for (int i = 0; i < size; ++i)
		{
			popBack(list);
		}

		delete list;
		list = nullptr;
		std::cout << "List is destroyed...\n";
	}
}

template<typename T>
bool pushFront(List<T> *list, T value)
{
	if (list)
	{
		Node<T> *node = new Node<T>(value);

		if (list->m_size == 0)
		{
			list->m_pHead = list->m_pTail = node;
		}
		else
		{
			list->m_pHead->m_pPrev = node;
			node->m_pNext = list->m_pHead;

			list->m_pHead = node;
		}
		list->m_size++;
		return list->m_size > 0;
	}
	std::cout << "List is a nullptr.\n";
	return false;
}

template<typename T>
bool pushBack(List<T> *list, T value)
{
	if (list)
	{
		Node<T> *node = new Node<T>(value);

		if (list->m_size == 0)
		{
			list->m_pHead = list->m_pTail = node;
		}
		else
		{
			list->m_pTail->m_pNext = node;
			node->m_pPrev = list->m_pTail;

			list->m_pTail = node;
		}

		list->m_size++;

		return list->m_size > 0;
	}
	std::cout << "List is a nullptr.\n";
	return false;
}

template<typename T>
bool popBack(List<T> *list)
{
	if (list && list->m_size > 0)
	{
		Node<T> *node = list->m_pTail;
		list->m_pTail = node->m_pPrev;
		if (list->m_pTail)
		{
			list->m_pTail->m_pNext = nullptr;
		}

		list->m_size--;
		delete node;

		return true;
	}
	std::cout << "List is a nullptr.\n";
	return false;
}

template<typename T>
bool popFront(List<T> *list)
{
	if (list && list->m_size > 1)
	{
		Node<T> *node = list->m_pHead;
		list->m_pHead = node->m_pNext;
		if (list->m_pHead)
		{
			list->m_pHead->m_pPrev = nullptr;
		}

		list->m_size--;
		delete node;
		return true;
	}
	std::cout << "List is a nullptr.\n";
	return false;
}

template<typename T>
bool front(List<T> *list, T &value)
{
	if (!list)
	{
		std::cout << "List is a nullptr.\n";
	}
	else if (list->m_size > 0)
	{
		value = list->m_pHead->m_data;
		return true;
	}
	std::cout << "List is empty." << std::endl;
	return false;
}

template<typename T>
bool back(List<T> *list, T &value)
{
	if (!list)
	{
		std::cout << "List is a nullptr.\n";
	}
	else if (list->m_size > 0)
	{
		value = list->m_pTail->m_data;
		return true;
	}
	std::cout << "List is empty.\n";
	return false;
}

template<typename T>
void traverse(List<T> *list)
{
	if (!list)
	{
		std::cout << "List is a nullptr.\n";
	}
	else if (list && list->m_size == 0)
	{
		std::cout << "List is empty.\n";
	}
	else
	{
		int size = list->m_size;
		Node<T> *node = list->m_pHead;
		std::cout << "List data is ..." << std::endl;
		for (int i = 0; i < size; i++)
		{
			std::cout << "[" << i << "]" << " :: " << node->m_data << std::endl;
			node = node->m_pNext;
		}
	}
}

template<typename T>
void traverse(List<T>* list, std::vector<T> &vec)
{
	if (!list)
	{
		std::cout << "List is a nullptr.\n";
	}
	else if (list && list->m_size == 0)
	{
		std::cout << "List is empty.\n";
	}
	else
	{
		int size = list->m_size;
		vec.resize(size);
		Node<T>* node = list->m_pHead;
		for (int i = 0; i < size; i++)
		{
			vec[i] = node->m_data;
			node = node->m_pNext;
		}
	}
}
}}
#endif// __C_LIST_H__