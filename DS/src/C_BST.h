#ifndef __C_BST_H__
#define __C_BST_H__

#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include <stdlib.h>
/*
	Desc : Binary search tree handling keys with same value
*/

#define STRUCT_NAME(dataType)		BstNode_##dataType

#define DECLARE_STRUCT(dataType)	typedef struct STRUCT_NAME(dataType) {			\
										dataType						m_data;		\
										size_t							m_count;	\
										struct STRUCT_NAME(dataType)	*m_lt;		\
										struct STRUCT_NAME(dataType)	*m_rt;		\
									}STRUCT_NAME(dataType)

#define CAST_PTR_AS(pointer, dataType)	((dataType *)(pointer))

#define DECLARE_FUNC_createNode(dataType)		STRUCT_NAME(dataType)* createNode_##dataType(dataType data)
#define DECLARE_FUNC_insertRecursive(dataType)	bool insertRecursive_##dataType(STRUCT_NAME(dataType) **root, dataType data)
#define DECLARE_FUNC_insertIterative(dataType)	bool insertIterative_##dataType(STRUCT_NAME(dataType) **root, dataType data)
#define DECLARE_FUNC_search(dataType)			bool search_##dataType(STRUCT_NAME(dataType) *root, dataType data)
#define DECLARE_FUNC_findMin(dataType)			STRUCT_NAME(dataType)* findMin_##dataType(STRUCT_NAME(dataType) *root)
#define DECLARE_FUNC_remove(dataType)			STRUCT_NAME(dataType)* remove_##dataType(STRUCT_NAME(dataType) **root, dataType data)

//#define DECLARE_FUNC_preorder(dataType)			void preorder##dataType(STRUCT_NAME(dataType) *root)
//#define DECLARE_FUNC_inorder(dataType)			void inorder##dataType(STRUCT_NAME(dataType) *root)
//#define DECLARE_FUNC_postorder(dataType)		void postorder##dataType(STRUCT_NAME(dataType) *root)

#define DECLARE_FUNC_preorderData(dataType)		void preorderData_##dataType(STRUCT_NAME(dataType) *root, STRUCT_NAME(dataType) **listNode)
#define DECLARE_FUNC_inorderData(dataType)		void inorderData_##dataType(STRUCT_NAME(dataType) *root, STRUCT_NAME(dataType) **listNode)
#define DECLARE_FUNC_postorderData(dataType)	void postorderData_##dataType(STRUCT_NAME(dataType) *root, STRUCT_NAME(dataType) **listNode)

#define DEFINE_FUNC_createNode(dataType)											\
DECLARE_FUNC_createNode(dataType) {													\
	STRUCT_NAME(dataType) *newNode = NULL;											\
	newNode = (STRUCT_NAME(dataType) *)malloc(sizeof(STRUCT_NAME(dataType)));		\
	newNode->m_data = data;															\
	newNode->m_count = 1;															\
	newNode->m_lt = newNode->m_rt = NULL;											\
	return newNode;																	\
}

#define DEFINE_FUNC_insertRecursive(dataType)										\
DECLARE_FUNC_insertRecursive(dataType) {											\
	if (!(*root)) {																	\
		(*root) = createNode_##dataType(data);										\
	}																				\
	else if (data < (*root)->m_data) {												\
		insertRecursive_##dataType(&((*root)->m_lt), data);							\
	}																				\
	else if (data > (*root)->m_data) {												\
		insertRecursive_##dataType(&((*root)->m_rt), data);							\
	}																				\
	else { /* i.e same key */														\
		(*root)->m_count++;															\
	}																				\
	return true;																	\
}

#define DEFINE_FUNC_insertIterative(dataType)										\
DECLARE_FUNC_insertIterative(dataType) {											\
	if (!(*root)) {																	\
		(*root) = createNode_##dataType(data);										\
	}																				\
	else {																			\
		STRUCT_NAME(dataType)* curr = (*root);										\
		STRUCT_NAME(dataType)* prev = NULL;											\
		while (curr) {																\
			prev = curr;															\
			if (data < curr->m_data) {												\
				curr = curr->m_lt;													\
			}																		\
			else if (data > curr->m_data) {											\
				curr = curr->m_rt;													\
			}																		\
			else {																	\
				break;																\
			}																		\
		}																			\
		if (curr)	/* that means it should have the same key */					\
		{																			\
			if (curr->m_data == data) {												\
				curr->m_count++;													\
			}																		\
			else {																	\
				printf("ERROR::%s::%d:: Data corrupt.", __FUNCTION__, __LINE__);	\
				assert(false);														\
				return false;														\
			}																		\
		}																			\
		else if (prev)  {															\
			if (data < prev->m_data) {												\
				prev->m_lt = createNode_##dataType(data);							\
			}																		\
			else {																	\
				prev->m_rt = createNode_##dataType(data);							\
			}																		\
		}																			\
		else {																		\
			return false;															\
		}																			\
	}																				\
	return true;																	\
}

#define DEFINE_FUNC_search(dataType)												\
DECLARE_FUNC_search(dataType) {														\
	if (!root) { return false; }													\
	if (data < root->m_data) {														\
		return search_##dataType(root->m_lt, data);									\
	}																				\
	else if (data > root->m_data) {													\
		return search_##dataType(root->m_rt, data);									\
	}																				\
	else { return true; }															\
}

#define DEFINE_FUNC_findMin(dataType)												\
DECLARE_FUNC_findMin(dataType) {													\
	STRUCT_NAME(dataType) *curr = root;												\
	/* loop down to find the leftmost leaf */										\
	while (curr->m_lt != NULL) {													\
		curr = curr->m_lt;															\
	}																				\
	return curr;																	\
}

#define DEFINE_FUNC_remove(dataType)												\
DECLARE_FUNC_remove(dataType) {														\
	if (!(*root)) { return NULL; }													\
	else if (data < (*root)->m_data)												\
	{																				\
		(*root)->m_lt = remove_##dataType(&((*root)->m_lt), data);					\
	}																				\
	else if (data > (*root)->m_data) {												\
		(*root)->m_rt = remove_##dataType(&((*root)->m_rt), data);					\
	}																				\
	else { /* We found the Node */													\
		/* Case 1. If it have count > 1, multiple same key */						\
		if ((*root)->m_count > 1) { 												\
			(*root)->m_count--;														\
		}																			\
		/* Case 2. If it have no child */											\
		else if ((*root)->m_lt == NULL && (*root)->m_rt == NULL) {					\
			free((*root));															\
			(*root) = NULL;															\
		}																			\
		/* Case 3. If it have Only one child */										\
			/* a: Have right Child */												\
		else if ((*root)->m_lt == NULL)												\
		{																			\
			STRUCT_NAME(dataType)* temp = (*root);									\
			(*root) = (*root)->m_rt;												\
			free(temp);																\
		}																			\
		/* Case 3. If it have Only one child */										\
			/* b: Have left Child */												\
		else if ((*root)->m_rt == NULL)												\
		{																			\
			STRUCT_NAME(dataType)* temp = (*root);									\
			(*root) = (*root)->m_lt;												\
			free(temp);																\
		}																			\
		/* Case 3. If it have both child */											\
		else																		\
		{																			\
			/* Find the minimum in right sub tree */								\
			STRUCT_NAME(dataType) *rightMin = findMin_##dataType((*root)->m_rt);	\
			(*root)->m_data = rightMin->m_data;										\
			(*root)->m_count = rightMin->m_count;									\
			rightMin->m_count = 1;													\
			(*root)->m_rt = remove_##dataType(&((*root)->m_rt), rightMin->m_data);	\
		}																			\
	}																				\
	return (*root);																	\
}

#define DEFINE_FUNC_preorderData(dataType)											\
DECLARE_FUNC_preorderData(dataType) {												\
	if (!root) { return; }															\
	(*listNode)->m_rt = createNode_##dataType(root->m_data);						\
	listNode = &((*listNode)->m_rt);												\
	preorderData_##dataType(root->m_lt, listNode);									\
	preorderData_##dataType(root->m_rt, listNode);									\
}

#define DEFINE_FUNC_inorderData(dataType)											\
DECLARE_FUNC_inorderData(dataType) {												\
	if (!root) { return; }															\
	inorderData_##dataType(root->m_lt, listNode);									\
	(*listNode)->m_rt = createNode_##dataType(root->m_data);						\
	listNode = &((*listNode)->m_rt);												\
	inorderData_##dataType(root->m_rt, listNode);									\
}

#define DEFINE_FUNC_postorderData(dataType)											\
DECLARE_FUNC_postorderData(dataType) {												\
	if (!root) { return; }															\
	postorderData_##dataType(root->m_rt, listNode);									\
	postorderData_##dataType(root->m_lt, listNode);									\
	(*listNode)->m_rt = createNode_##dataType(root->m_data);						\
	listNode = &((*listNode)->m_rt);												\
}

#define INIT_BST(dataType)					\
DECLARE_STRUCT(dataType);					\
											\
DEFINE_FUNC_createNode(dataType)			\
											\
DEFINE_FUNC_insertRecursive(dataType)		\
											\
DEFINE_FUNC_insertIterative(dataType)		\
											\
DEFINE_FUNC_search(dataType)				\
											\
DEFINE_FUNC_findMin(dataType)				\
											\
DEFINE_FUNC_remove(dataType)				\
											\
DEFINE_FUNC_preorderData(dataType)			\
											\
DEFINE_FUNC_inorderData(dataType)			\
											\
DEFINE_FUNC_postorderData(dataType)

#endif //__BST_H__