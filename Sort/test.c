#include "Sort.h"

void PrintArr(int *a, int n)
{
	for (int i = 0; i < n; i++)
	{
		printf("%d ", a[i]);
	}
	printf("\n");
}

void testTime()
{
	int maxsize = 50000;
	int *arr1 = (int *)malloc(maxsize * sizeof(int));
	int *arr2 = (int *)malloc(maxsize * sizeof(int));
	int *arr3 = (int *)malloc(maxsize * sizeof(int));
	int *arr4 = (int *)malloc(maxsize * sizeof(int));
	int *arr5 = (int *)malloc(maxsize * sizeof(int));
	int *arr6 = (int *)malloc(maxsize * sizeof(int));
	int *arr7 = (int *)malloc(maxsize * sizeof(int));
	int *arr8 = (int *)malloc(maxsize * sizeof(int));

	if (!arr1 || !arr2 || !arr3 || !arr4 || !arr5 || !arr6 || !arr7 || !arr8)
		return;

	srand(time(0));
	for (int i = 0; i < maxsize; i++)
	{
		int tmp = rand() % 10000 + 1;
		arr1[i] = tmp;
		arr2[i] = tmp;
		arr3[i] = tmp;
		arr4[i] = tmp;
		arr5[i] = tmp;
		arr6[i] = tmp;
		arr7[i] = tmp;
		arr8[i] = tmp;
	}

	int begin1 = clock();
	InsertSort(arr1, maxsize);
	int end1 = clock();

	int begin2 = clock();
	ShellSort(arr2, maxsize);
	int end2 = clock();

	int begin3 = clock();
	HeapSort(arr3, maxsize);
	int end3 = clock();

	int begin4 = clock();
	SelectSort(arr4, maxsize);
	int end4 = clock();

	int begin5 = clock();
	BubbleSort(arr5, maxsize);
	int end5 = clock();

	int begin6 = clock();
	QuickSort(arr6, maxsize);
	int end6 = clock();

	int begin7 = clock();
	MergeSort(arr7, maxsize);
	int end7 = clock();

	int begin8 = clock();
	CountSort(arr7, maxsize);
	int end8 = clock();

	printf("InsertSort:%d\n", end1 - begin1);
	printf("ShellSort:%d\n", end2 - begin2);
	printf("HeapSort:%d\n", end3 - begin3);
	printf("SelectSort:%d\n", end4 - begin4);
	printf("BubbleSort:%d\n", end5 - begin5);
	printf("QuickSort:%d\n", end6 - begin6);
	printf("MergeSort:%d\n", end7 - begin7);
	printf("CountSort:%d\n", end8 - begin8);

	free(arr1);
	free(arr2);
	free(arr3);
	free(arr4);
	free(arr5);
	free(arr6);
	free(arr7);
	free(arr8);
}

void testInsertSort()
{
	int a[] = {5, 1, 0, 9, 4, 3, 7, 2, 8, 6};
	PrintArr(a, sizeof(a) / sizeof(a[0]));
	InsertSort(a, sizeof(a) / sizeof(a[0]));
	PrintArr(a, sizeof(a) / sizeof(a[0]));

	int b[] = {3, 7};
	PrintArr(b, sizeof(b) / sizeof(b[0]));
	InsertSort(b, sizeof(b) / sizeof(b[0]));
	PrintArr(b, sizeof(b) / sizeof(b[0]));
}
void testShellSort()
{
	int a[] = {5, 1, 0, 9, 4, 3, 7, 2, 8, 6};
	PrintArr(a, sizeof(a) / sizeof(a[0]));
	ShellSort(a, sizeof(a) / sizeof(a[0]));
	PrintArr(a, sizeof(a) / sizeof(a[0]));

	int b[] = {3, 7};
	PrintArr(b, sizeof(b) / sizeof(b[0]));
	ShellSort(b, sizeof(b) / sizeof(b[0]));
	PrintArr(b, sizeof(b) / sizeof(b[0]));
}
void testHeapSort()
{
	int a[] = {5, 1, 0, 9, 4, 3, 7, 2, 8, 6};
	PrintArr(a, sizeof(a) / sizeof(a[0]));
	HeapSort(a, sizeof(a) / sizeof(a[0]));
	PrintArr(a, sizeof(a) / sizeof(a[0]));

	int b[] = {3, 7};
	PrintArr(b, sizeof(b) / sizeof(b[0]));
	HeapSort(b, sizeof(b) / sizeof(b[0]));
	PrintArr(b, sizeof(b) / sizeof(b[0]));
}
void testSelectSort()
{
	int a[] = {5, 1, 0, 9, 4, 3, 7, 2, 8, 6};
	PrintArr(a, sizeof(a) / sizeof(a[0]));
	SelectSort(a, sizeof(a) / sizeof(a[0]));
	PrintArr(a, sizeof(a) / sizeof(a[0]));

	int b[] = {3, 7};
	PrintArr(b, sizeof(b) / sizeof(b[0]));
	SelectSort(b, sizeof(b) / sizeof(b[0]));
	PrintArr(b, sizeof(b) / sizeof(b[0]));
}
void testBubleSort()
{
	int a[] = {5, 1, 0, 9, 4, 3, 7, 2, 8, 6};
	PrintArr(a, sizeof(a) / sizeof(a[0]));
	BubbleSort(a, sizeof(a) / sizeof(a[0]));
	PrintArr(a, sizeof(a) / sizeof(a[0]));

	int b[] = {3, 7};
	PrintArr(b, sizeof(b) / sizeof(b[0]));
	BubbleSort(b, sizeof(b) / sizeof(b[0]));
	PrintArr(b, sizeof(b) / sizeof(b[0]));
}
void testQuickSort()
{
	int a[] = {5, 1, 0, 9, 4, 3, 7, 2, 8, 6};
	PrintArr(a, sizeof(a) / sizeof(a[0]));
	QuickSort(a, sizeof(a) / sizeof(a[0]));
	PrintArr(a, sizeof(a) / sizeof(a[0]));

	int b[] = {3, 7};
	PrintArr(b, sizeof(b) / sizeof(b[0]));
	QuickSort(b, sizeof(b) / sizeof(b[0]));
	PrintArr(b, sizeof(b) / sizeof(b[0]));
}
void testMergeSort()
{
	int a[] = {5, 1, 0, 9, 4, 3, 7, 2, 8, 6};
	PrintArr(a, sizeof(a) / sizeof(a[0]));
	MergeSort(a, sizeof(a) / sizeof(a[0]));
	PrintArr(a, sizeof(a) / sizeof(a[0]));

	int b[] = {3, 7};
	PrintArr(b, sizeof(b) / sizeof(b[0]));
	MergeSort(b, sizeof(b) / sizeof(b[0]));
	PrintArr(b, sizeof(b) / sizeof(b[0]));
}
void testCountSort()
{
	int a[] = {5, 1, 0, 9, 4, 3, 7, 2, 8, 6};
	PrintArr(a, sizeof(a) / sizeof(a[0]));
	CountSort(a, sizeof(a) / sizeof(a[0]));
	PrintArr(a, sizeof(a) / sizeof(a[0]));

	int b[] = {3, 7};
	PrintArr(b, sizeof(b) / sizeof(b[0]));
	CountSort(b, sizeof(b) / sizeof(b[0]));
	PrintArr(b, sizeof(b) / sizeof(b[0]));
}
int main()
{
	testTime();

	// testInsertSort();
	// testShellSort();
	// testHeapSort();
	// testSelectSort();
	// testBubleSort();
	// testQuickSort();
	// testMergeSort();
	// testCountSort();

	return 0;
}