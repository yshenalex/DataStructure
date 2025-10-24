#include "List.h"

void TestList1()
{
	LTNode *plist = ListInit();
	printf("--------------------------------\n");
	printf("尾插1,2,3,4,5：\n");
	ListPushBack(plist, 1);
	ListPushBack(plist, 2);
	ListPushBack(plist, 3);
	ListPushBack(plist, 4);
	ListPushBack(plist, 5);
	ListPrint(plist);
	printf("--------------------------------\n");
	printf("头插10,20,30,40,50：\n");
	ListPushFront(plist, 10);
	ListPushFront(plist, 20);
	ListPushFront(plist, 30);
	ListPushFront(plist, 40);
	ListPushFront(plist, 50);
	ListPrint(plist);
	printf("--------------------------------\n");
	printf("尾删4次：\n");
	ListPopBack(plist);
	ListPopBack(plist);
	ListPopBack(plist);
	ListPopBack(plist);
	ListPrint(plist);
	printf("--------------------------------\n");
	printf("删除指定数值首个元素20：\n");
	ListEraseEle(plist, 20);
	ListPrint(plist);

	ListDestroy(plist);
	plist = NULL; // 释放后手动置空，类似于free();
}

int main()
{
	TestList1();
	return 0;
}
