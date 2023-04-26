#ifndef __C_LIST_H__
#define __C_LIST_H__

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct ListNode
{
	void				*m_pData;
	struct ListNode		*m_pNext;
	struct ListNode		*m_pPrev;
}ListNode;

typedef struct List
{
	int			m_size;
	ListNode	*m_pHead;
	ListNode	*m_pTail;
}List;

ListNode* createListNode(void *pData)
{
	ListNode *pListNode = (ListNode*)malloc(sizeof(ListNode));
	if (pListNode)
	{
		pListNode->m_pData = pData;
		pListNode->m_pNext = pListNode->m_pPrev = NULL;
	}
	return pListNode;
}

List* createList()
{
	List* pList = (List*)malloc(sizeof(List));
	if (pList)
	{
		pList->m_size = 0;
		pList->m_pHead = pList->m_pTail = NULL;
	}
	return pList;
}

bool pushFrontList(List *pList, void *pValue)
{
	if (pList)
	{
		ListNode *pNode = createListNode(pValue);

		if (pList->m_size == 0)
		{
			pList->m_pHead = pList->m_pTail = pNode;
		}
		else
		{
			pNode->m_pNext = pList->m_pHead;
			pList->m_pHead->m_pPrev = pNode;
			pList->m_pHead = pNode;
		}
		pList->m_size++;
		return pList->m_size > 0;
	}
	printf("List is a nullptr.\n");
	return false;
}

bool pushBackList(List *pList, void *pValue)
{
	if (pList)
	{
		ListNode* pNode = createListNode(pValue);

		if (pList->m_size == 0)
		{
			pList->m_pHead = pList->m_pTail = pNode;
		}
		else
		{
			pNode->m_pPrev = pList->m_pTail;
			pList->m_pTail->m_pNext = pNode;

			pList->m_pTail = pNode;
		}
		pList->m_size++;
		return pList->m_size > 0;
	}
	printf("List is a nullptr.\n");
	return false;
}

bool popBackList(List *pList)
{
	if (pList && pList->m_size > 0)
	{
		ListNode *pNode = pList->m_pTail;
		pList->m_pTail = pNode->m_pPrev;
		if (pList->m_pTail)
		{
			pList->m_pTail->m_pNext = NULL;
		}
		pList->m_size--;
		free(pNode);
		return true;
	}
	printf("List is a nullptr.\n");
	return false;
}

bool popFrontList(List *pList)
{
	if (pList && pList->m_size > 0)
	{
		ListNode *pNode = pList->m_pHead;
		pList->m_pHead = pNode->m_pNext;

		if (pList->m_pHead)
		{
			pList->m_pHead->m_pPrev = NULL;
		}

		pList->m_size--;
		free(pNode);
		return true;
	}
	printf("List is a nullptr.\n");
	return false;
}

bool frontList(List *pList, void **pValue)
{
	if (!pList)
	{
		printf("List is a nullptr.\n");
	}
	else if (pList->m_size > 0)
	{
		*pValue = pList->m_pHead->m_pData;
		return true;
	}
	printf("List is empty.\n");
	return false;
}

bool backList(List* pList, void** pValue)
{
	if (!pList)
	{
		printf("List is a nullptr.\n");
	}
	else if (pList->m_size > 0)
	{
		*pValue = pList->m_pTail->m_pData;
		return true;
	}
	printf("List is empty.\n");
	return false;
}

void deleteList(List** pList)
{
	if (pList && *pList)
	{
		int size = (*pList)->m_size;
		for (int i = 0; i < size; ++i)
		{
			popBackList(*pList);
		}
		free(*pList);
		*pList = NULL;
		printf("List is destroyed...\n");
	}
}

void printList(List *pList)
{
	if (!pList)
	{
		printf("List is a nullptr.\n");
	}
	else if (pList && pList->m_size == 0)
	{
		printf("List is empty.\n");
	}
	else
	{
		int size = pList->m_size;
		ListNode *pNode = pList->m_pHead;
		printf("List data is ...\n");
		for (int i = 0; i < size; i++)
		{
			printf("[%d] :: %p\n", i, pNode->m_pData);
			pNode = pNode->m_pNext;
		}
	}
}

void traverseList(List* pList, void ***pVec, int* pSize)
{
	if (!pList)
	{
		printf("List is a nullptr.\n");
	}
	else if (pList && pList->m_size == 0)
	{
		printf("List is empty.\n");
	}
	else
	{
		*pSize = pList->m_size;
		(*pVec) = (void **)malloc(sizeof(void**) * (*pSize));
		ListNode *pNode = pList->m_pHead;
		for (int i = 0; i < (*pSize); i++)
		{
			(*pVec)[i] = pNode->m_pData;
			pNode = pNode->m_pNext;
		}
	}
}
#endif// __C_LIST_H__