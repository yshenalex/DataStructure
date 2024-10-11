#include"SepList.h"

void PrintSepList(SL* ps)
{
	int i = 0;
	for (i = 0; i < ps->size; i++)
	{
		printf("%d ", (ps->a)[i]);
	}
	printf("\n");
}


void TestSepList1()
{
	SL s1;
	SepListInit(&s1);
	printf("---------------------------\n");
	printf("尾部插入1,2,3,4,5,6：\n");
	SepListPushBack(&s1, 1);
	SepListPushBack(&s1, 2);
	SepListPushBack(&s1, 3);
	SepListPushBack(&s1, 4);
	SepListPushBack(&s1, 5);
	SepListPushBack(&s1, 6);
	PrintSepList(&s1);
	printf("---------------------------\n");
	printf("前部插入10，20，30，40，50：\n");
	SepListPushFront(&s1, 10);
	SepListPushFront(&s1, 20);
	SepListPushFront(&s1, 30);
	SepListPushFront(&s1, 40);
	SepListPushFront(&s1, 50);
	PrintSepList(&s1);
	printf("---------------------------\n");
	printf("头删4次：\n");
	SepListPopFront(&s1);
	SepListPopFront(&s1);
	SepListPopFront(&s1);
	SepListPopFront(&s1);
	PrintSepList(&s1);
	printf("---------------------------\n");
	printf("寻找元素4：\n");
	printf("%d\n",SepListFind(&s1, 4));
	printf("---------------------------\n");
	printf("下标2位置插入11，22，33，44，55：\n");
	SepListInsert(&s1, 2, 11);
	SepListInsert(&s1, 2, 22);
	SepListInsert(&s1, 2, 33);
	SepListInsert(&s1, 2, 44);
	SepListInsert(&s1, 2, 55);
	PrintSepList(&s1);
	printf("---------------------------\n");
	printf("擦除下标4的元素3次：\n");
	SepListErase(&s1, 4);
	SepListErase(&s1, 4);
	SepListErase(&s1, 4);
	PrintSepList(&s1);
	printf("---------------------------\n");
	printf("寻找元素5并删除：\n");
	SepListEraseByElement(&s1, 5);
	PrintSepList(&s1);

	SepListDestory(&s1);
}


int main()
{
	TestSepList1();

	return 0;
}
































