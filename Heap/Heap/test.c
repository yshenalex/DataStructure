#include"Heap.h"

void testHeap1()
{
	int a[]= {27, 15, 19, 18, 28, 34, 65, 49, 25, 37};
	Heap hp;
	HeapInit(&hp, a, sizeof(a) / sizeof(a[0]));
	HeapPush(&hp, 1);
	HeapPush(&hp, 6);
	HeapPush(&hp, 8);

	for (int i = 0; i < hp._size; i++)
	{
		printf("%d ", hp._a[i]);
	}
}
void testHeap2()
{
	Heap hp;
	int a[] = { 27, 15};
	HeapInit(&hp, a, sizeof(a) / sizeof(a[0]));
	HeapPop(&hp);
	HeapPop(&hp);
	bool flag = HeapEmpty(&hp);
	printf("%d", flag);
}

void testHeap3()
{
	int a[] = { 27, 15, 19, 18, 28, 34, 65, 49, 25, 37 };
	HeapSort(a, 10);
	for (int i = 0; i < sizeof(a)/sizeof(a[0]); i++)
	{
		printf("%d ", a[i]);
	}
}
void testHeap4()
{
	int a[] = { 28, 15, 42, 18, 22, 5,40 };
	Heap hp;
	HeapInit(&hp, a, sizeof(a) / sizeof(a[0]));
	for (int i = 0; i < hp._size; i++)
	{
		printf("%d ", hp._a[i]);
	}
}

int main()
{
	//testHeap1();
	//testHeap2();
	//testHeap3();
	testHeap4();
	return 0;
}