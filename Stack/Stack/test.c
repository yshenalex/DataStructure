#include"Stack.h"

void TestStack1()
{
	ST st;
	StackInit(&st);

	printf("-----------------------\n");
	printf("依次入栈1，2，3，4, 5, 6，7：\n");
	StackPush(&st, 1);
	StackPush(&st, 2);
	StackPush(&st, 3);
	StackPush(&st, 4);
	StackPush(&st, 5);
	StackPush(&st, 6);
	StackPush(&st, 7);
	StackPrint(st);
	
	printf("-----------------------\n");
	printf("删除三次：\n");
	StackPop(&st);
	StackPop(&st);
	StackPop(&st);
	StackPrint(st);

	printf("-----------------------\n");
	printf("取栈顶元素：\n");
	printf("%d\n", StackTop(&st));

	printf("-----------------------\n");
	printf("显示栈存储数据个数：\n");
	printf("%d\n", StackSize(&st));
}

int main()
{
	TestStack1();
	return 0;
}
































