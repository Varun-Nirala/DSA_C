#ifndef __C_TESTER_H__
#define __C_TESTER_H__

#include "C_Stack.h"
#include "C_List.h"
#include "C_BST.h"

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
		int* pVal = (int *)malloc(sizeof(int *));
		*pVal = arr[i];
		pushStack(pStack, pVal);
	}

	print("Stack size test.", stackSize(pStack) == maxSize);

	int *pValue = (int *)malloc(sizeof(int *));
	for (int i = maxSize - 1; i >= 0; --i)
	{
		
		if (!topStack(pStack, &pValue) || *pValue != arr[i])
		{
			ret = false;
			break;
		}
		popStack(pStack);
	}
	free(pValue);
	pValue = NULL;
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
		int* pVal = (int*)malloc(sizeof(int*));
		*pVal = arr[i];
		pushFrontList(&pList, pVal);
	}
	print("List size test.", (pList->m_size == arrSize));

	int* pArr = NULL;
	int size = 0;
	traverseList(pList, &pArr, &size);

	assert(size == arrSize);

	for (int i = arrSize - 1, j = 0; i >= 0; --i, ++j)
	{
		if (pArr[i] != arr[j])
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
	print("List delete test.", pList->m_size == 0 && pList == NULL);

	pList = createList();

	for (int i = 0; i < arrSize; i++)
	{
		int* pVal = (int *)malloc(sizeof(int *));
		*pVal = arr[i];
		pushBackList(&pList, pVal);
	}
	print("List size test.", pList->m_size == arrSize);

	traverseList(pList, &pArr, &size);

	assert(size == arrSize);

	for (int i = 0; i < arrSize; ++i)
	{
		if (pArr[i] != arr[i])
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
	print("List delete test.\n\n", pList->m_size == 0 && pList == NULL);
}

void test_C_BST(const char* msg)
{
	printf(msg);

	INIT_BST(int);

	BstNode_int *pRoot = NULL;

	int arr[] = { 15, 10, 20, 8, 12, 18, 25, 19, 30, 15, 10, 20, 8, 12, 18, 25, 19, 30 };
	int arrSize = sizeof(arr) / sizeof(arr[0]);

	bool ret = true;
}

#endif //__C_TESTER_H__