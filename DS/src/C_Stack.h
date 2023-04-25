#ifndef __C_STACK_H__
#define __C_STACK_H__

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct Stack
{
	void	**m_pArr;
	int		m_top;
	int		m_capacity;
}Stack;

Stack* createStack(int capacity)
{
	Stack *pStack = (Stack*)malloc(sizeof(Stack));
	if (pStack)
	{
		pStack->m_pArr = (void**)malloc(sizeof(void*) * capacity);

		pStack->m_capacity = capacity;
		pStack->m_top = -1;
	}
	return pStack;
}

int stackSize(Stack* pStack)
{
	return pStack ? pStack->m_top + 1 : 0;
}

bool pushStack(Stack *pStack, void *pValue)
{
	if (pStack && pStack->m_top < pStack->m_capacity - 1)
	{
		int index = ++(pStack->m_top);
		pStack->m_pArr[index] = pValue;
		return true;
	}
	else
	{
		printf("Stack is full.\n");
		return false;
	}
}

bool topStack(Stack *pStack, void **pValue)
{
	if (pStack && pStack->m_top >= 0)
	{
		*pValue = pStack->m_pArr[pStack->m_top];
		return true;
	}
	else
	{
		printf("Stack is empty.\n");
		return false;
	}
}

void popStack(Stack *pStack)
{
	if (pStack->m_top >= 0)
	{
		(pStack->m_top)--;
	}
	else
	{
		printf("Stack is empty.\n");
	}
}

void deleteStack(Stack** pStack)
{
	if (pStack && *pStack)
	{
		free((*pStack)->m_pArr);
		free((*pStack));
		(*pStack) = NULL;
	}
}
#endif // __C_STACK_H__