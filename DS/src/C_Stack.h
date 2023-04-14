#ifndef __C_STACK_H__
#define __C_STACK_H__

#include <iostream>

namespace nsC_DS { namespace nsC_Stack {

constexpr int kDEFAULT_CAP = 10;
template<typename T>
struct Stack
{
	T		*m_arr{};
	int		m_top{-1};
	int		m_capacity{ kDEFAULT_CAP };

	Stack(int cap)
	{
		if (cap > m_capacity)
		{
			m_capacity = cap;
		}
		m_arr = new T[m_capacity];
	}
};

template<typename T>
int size(Stack<T> &stack)
{
	return stack.m_top + 1;
}

template<typename T>
bool push(Stack<T> &stack, T value)
{
	if (stack.m_top < stack.m_capacity - 1)
	{
		int index = ++stack.m_top;
		stack.m_arr[index] = value;
		return true;
	}
	else
	{
		std::cout << "Stack is FULL." << std::endl;
		return false;
	}
}

template<typename T>
bool top(Stack<T> &stack, T &value)
{
	if (stack.m_top >= 0)
	{
		value = stack.m_arr[stack.m_top];
		return true;
	}
	else
	{
		std::cout << "Stack is EMPTY." << std::endl;
		return false;
	}
}

template<typename T>
void pop(Stack<T> &stack)
{
	if (stack.m_top >= 0)
	{
		stack.m_top--;
	}
	else
	{
		std::cout << "Stack is EMPTY." << std::endl;
	}
}

}}
#endif // __C_STACK_H__