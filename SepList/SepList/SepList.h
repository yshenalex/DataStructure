#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>

typedef int SLDataType;

//静态顺序表
//#define N 1000
//typedef struct SepList
//{
//	SLDataType a [N];
//	int size;
//}SL;

//动态顺序表：
typedef struct SepList
{
	SLDataType* a;
	int size;//已存数据个数
	int capacity;//容量数
}SL;


//【接口函数】：
void SepListInit(SL* ps);//初始化
void SepListCheckCapacity(SL* ps);//检查是否需要增容

void SepListPushBack(SL* ps, SLDataType x);//尾插
void SepListPopBack(SL* ps);//尾删
void SepListPushFront(SL* ps, SLDataType x);//头插
void SepListPopFront(SL* ps);//头删

int SepListFind(SL* ps, SLDataType x);//寻找某个元素，返回所在下标
void SepListInsert(SL* ps, int pos, SLDataType x);//指定位置插入
void SepListErase(SL* ps, int pos);//指定位置删除

void SepListEraseByElement(SL* ps, SLDataType x);//删除指定数值元素

void SepListDestory(SL* ps);//销毁(释放动态开辟的内存)





















