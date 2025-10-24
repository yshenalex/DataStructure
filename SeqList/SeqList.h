#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef int SLDataType;

// 静态顺序表
// #define N 1000
// typedef struct SeqList
//{
//	SLDataType a [N];
//	int size;
// }SL;

// 动态顺序表：
typedef struct SeqList
{
	SLDataType *a;
	int size;	  // 已存数据个数
	int capacity; // 容量数
} SL;

// 【接口函数】：
void SeqListInit(SL *ps);		   // 初始化
void SeqListCheckCapacity(SL *ps); // 检查是否需要增容

void SeqListPushBack(SL *ps, SLDataType x);	 // 尾插
void SeqListPopBack(SL *ps);				 // 尾删
void SeqListPushFront(SL *ps, SLDataType x); // 头插
void SeqListPopFront(SL *ps);				 // 头删

int SeqListFind(SL *ps, SLDataType x);			   // 寻找某个元素，返回所在下标
void SeqListInsert(SL *ps, int pos, SLDataType x); // 指定位置插入
void SeqListErase(SL *ps, int pos);				   // 指定位置删除

void SeqListEraseByElement(SL *ps, SLDataType x); // 删除指定数值元素

void SeqListDestory(SL *ps); // 销毁(释放动态开辟的内存)
