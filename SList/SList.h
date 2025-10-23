#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>


typedef int SLTDataType;
typedef struct SListNode
{
	SLTDataType data;//存储的数据
	struct SListNode* next;//指向下一节点
}SLTNode;


//【函数接口】
SLTNode* BuyListNode(SLTDataType x);

void SListPrint(SLTNode* phead);

void SListPushBack(SLTNode**pphead,SLTDataType x);
void SListPushFront(SLTNode** phead,SLTDataType x);
void SListPopBack(SLTNode** pphead);
void SListPopFront(SLTNode** pphead);

SLTNode* SListFind(SLTNode* phead, SLTDataType x);
void SListFindPrintAll(SLTNode* phead, SLTDataType x);

void SListInsert(SLTNode** pphead, SLTNode* pos, SLTDataType x);//在pos位置之前插入一个节点
void SListInsertAfter(SLTNode* pos, SLTDataType x);
void SListErase(SLTNode** pphead, SLTNode* pos);
void SListEraseAfter(SLTNode* pos);//删除给定位置下一节点，不涉及改变phead,不用传二级指针
//void SListInsert(SLTNode* phead, int pos, SLTDataType x);

void SListDestory(SLTNode** phead);






