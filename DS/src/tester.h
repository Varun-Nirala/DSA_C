#ifndef __C_TESTER_H__
#define __C_TESTER_H__

#include "stack.h"
#include "list.h"
#include "bst.h"

void print(const char *msg, bool pass)
{
	if (pass)
	{
		printf("PASS : %s\n", msg);
	}
	else
	{
		printf("FAIL : %s\n", msg);
	}
}

void test_C_Stack(const char *msg)
{
	printf(msg);

	const int maxSize = 9;
	Stack *pStack = createStack(maxSize);

	bool ret = true;
	print("Stack empty test.", stackSize(pStack) == 0);

	int arr[] = { 15, 10, 20, 8, 12, 18, 25, 19, 30 };
	int arrSize = sizeof(arr) / sizeof(arr[0]);

	assert(arrSize == maxSize);

	for (int i = 0; i < maxSize; i++)
	{
		pushStack(pStack, (void *)&arr[i]);
		int* pValue = NULL;
		topStack(pStack, &pValue);
		assert(*pValue == arr[i]);
	}

	print("Stack size test.", stackSize(pStack) == maxSize);

	for (int i = maxSize - 1; i >= 0; --i)
	{
		int* pValue = NULL;
		if (!topStack(pStack, &pValue) || *pValue != arr[i])
		{
			ret = false;
			break;
		}
		popStack(pStack);
	}
	print("Stack after all pop, size test.", stackSize(pStack) == 0);
	print("Stack final test.\n\n", ret);

	deleteStack(&pStack);
}

void test_C_List(const char *msg)
{
	printf(msg);
	int arr[] = { 15, 10, 20, 8, 12, 18, 25, 19, 30, 15, 10, 20, 8, 12, 18, 25, 19, 30 };
	int arrSize = sizeof(arr) / sizeof(arr[0]);

	List *pList = createList();

	bool ret = true;
	print("List empty test.", pList->m_size == 0);
	for (int i = 0; i < arrSize; i++)
	{
		pushFrontList(pList, &arr[i]);
	}
	print("List size test.", (pList->m_size == arrSize));

	int **pArr = NULL;
	int size = 0;
	traverseList(pList, &pArr, &size);

	assert(size == arrSize);

	for (int i = arrSize - 1, j = 0; i >= 0; --i, ++j)
	{
		if (*pArr[i] != arr[j])
		{
			ret = false;
			break;
		}
	}

	free(pArr);
	pArr = NULL;
	size = 0;
	
	print("List pushFront test.", ret);
	deleteList(&pList);
	print("List delete test.", pList == NULL);

	pList = createList();

	for (int i = 0; i < arrSize; i++)
	{
		pushBackList(pList, &arr[i]);
	}
	print("List size test.", pList->m_size == arrSize);

	traverseList(pList, &pArr, &size);

	assert(size == arrSize);

	for (int i = 0; i < arrSize; ++i)
	{
		if (*pArr[i] != arr[i])
		{
			ret = false;
			break;
		}
	}

	free(pArr);
	pArr = NULL;
	size = 0;

	print("List pushBack test.", ret);
	deleteList(&pList);
	print("List delete test.\n\n", pList == NULL);
}

INIT_BST(int);

void test_C_BST(const char* msg)
{
	printf(msg);

	//int arr[] = { 15, 10, 20, 8, 12, 18, 25, 19, 30, 15, 10, 20, 8, 12, 18, 25, 19, 30 };
	//int arrSize = sizeof(arr) / sizeof(arr[0]);
	//bool ret = true;

	BstNode_int* m_root = NULL;
	insertIterative_int(&m_root, 1);
	insertRecursive_int(&m_root, 2);

	int val = 1;
	printf("Searching for %d : ", val);
	if (search_int(m_root, val))
	{
		printf("Found\n");
	}
	else
	{
		printf("Not Found\n");
	}

	val = 5;
	printf("Searching for %d : ", val);
	if (search_int(m_root, val))
	{
		printf("Found\n");
	}
	else
	{
		printf("Not Found\n");
	}

	val = 2;
	printf("Removing value %d\n", val);
	remove_int(&m_root, 2);
	printf("Searching for %d : ", val);
	if (search_int(m_root, val))
	{
		printf("Found\n");
	}
	else
	{
		printf("Not Found\n");
	}
}

#endif //__C_TESTER_H__