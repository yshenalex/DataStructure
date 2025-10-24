#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>

typedef int HPDataType;
typedef struct Heap
{
	HPDataType *_a;
	int _size;
	int _capacity;
} Heap;

void HeapInit(Heap *php, HPDataType *a, int n);
void HeapDestroy(Heap *php);
void HeapPush(Heap *php, HPDataType x);
void HeapPop(Heap *php); // 删除堆顶数据
HPDataType HeapTop(Heap *php);
bool HeapEmpty(Heap *php);
int HeapSize(Heap *php);
void HeapSort(int *a, int n);