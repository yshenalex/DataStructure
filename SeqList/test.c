#include "SeqList.h"

void PrintSeqList(SL *ps)
{
	int i = 0;
	for (i = 0; i < ps->size; i++)
	{
		printf("%d ", (ps->a)[i]);
	}
	printf("\n");
}

void TestSeqList1()
{
	SL s1;
	SeqListInit(&s1);
	printf("---------------------------\n");
	printf("尾部插入1,2,3,4,5,6：\n");
	SeqListPushBack(&s1, 1);
	SeqListPushBack(&s1, 2);
	SeqListPushBack(&s1, 3);
	SeqListPushBack(&s1, 4);
	SeqListPushBack(&s1, 5);
	SeqListPushBack(&s1, 6);
	PrintSeqList(&s1);
	printf("---------------------------\n");
	printf("前部插入10，20，30，40，50：\n");
	SeqListPushFront(&s1, 10);
	SeqListPushFront(&s1, 20);
	SeqListPushFront(&s1, 30);
	SeqListPushFront(&s1, 40);
	SeqListPushFront(&s1, 50);
	PrintSeqList(&s1);
	printf("---------------------------\n");
	printf("头删4次：\n");
	SeqListPopFront(&s1);
	SeqListPopFront(&s1);
	SeqListPopFront(&s1);
	SeqListPopFront(&s1);
	PrintSeqList(&s1);
	printf("---------------------------\n");
	printf("寻找元素4：\n");
	printf("%d\n", SeqListFind(&s1, 4));
	printf("---------------------------\n");
	printf("下标2位置插入11，22，33，44，55：\n");
	SeqListInsert(&s1, 2, 11);
	SeqListInsert(&s1, 2, 22);
	SeqListInsert(&s1, 2, 33);
	SeqListInsert(&s1, 2, 44);
	SeqListInsert(&s1, 2, 55);
	PrintSeqList(&s1);
	printf("---------------------------\n");
	printf("擦除下标4的元素3次：\n");
	SeqListErase(&s1, 4);
	SeqListErase(&s1, 4);
	SeqListErase(&s1, 4);
	PrintSeqList(&s1);
	printf("---------------------------\n");
	printf("寻找元素5并删除：\n");
	SeqListEraseByElement(&s1, 5);
	PrintSeqList(&s1);

	SeqListDestory(&s1);
}

int main()
{
	TestSeqList1();

	return 0;
}
