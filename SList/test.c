#include"SList.h"

void TestSList1()
{
	SLTNode* plist = NULL;
	printf("-----------------------\n");
	printf("尾插1，2，3，4，5：\n");
	SListPushBack(&plist, 1);
	SListPushBack(&plist, 1);
	SListPushBack(&plist, 2);
	SListPushBack(&plist, 3);
	SListPushBack(&plist, 4);
	SListPrint(plist);
	printf("-----------------------\n");
	printf("头插10，20，30，40：\n");
	SListPushFront(&plist, 10);
	SListPushFront(&plist, 20);
	SListPushFront(&plist, 30);
	SListPushFront(&plist, 40);
	SListPrint(plist);
	printf("-----------------------\n");
	printf("尾删3次：\n");
	SListPopBack(&plist);
	SListPopBack(&plist);
	SListPopBack(&plist);
	SListPrint(plist);
	printf("-----------------------\n");
	printf("头删4次：\n");
	SListPopFront(&plist);
	SListPopFront(&plist);
	SListPopFront(&plist);
	SListPopFront(&plist);
	SListPrint(plist);
	printf("-----------------------\n");
	printf("尾插2,3,4：\n");
	SListPushBack(&plist, 2);
	SListPushBack(&plist, 3);
	SListPushBack(&plist, 4);
	SListPrint(plist);
	printf("-----------------------\n");
	printf("寻找首个元素1：\n");
	printf("%p\n", SListFind(plist,1));
	printf("-----------------------\n");
	printf("寻找所有元素1：\n");
	SListFindPrintAll(plist, 1);
}


int main()
{
	TestSList1();
	return 0;
}

























