//#include "C_GenericKeyword.h"
//#include "C_tester.h"
#include "C_BST.h"

//#include "temp.h"
INIT_BST(int);

int main()
{
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
	//test_C_GenericKeyword();
	//nsC_DS::nsC_Tester::test_C_Stack("Testing C style Stack\n\n");
	//nsC_DS::nsC_Tester::test_C_List("Testing C style List\n\n");
	//nsC_DS::nsC_Tester::test_C_BST("Testing C style BST\n\n");
	return 0;
}