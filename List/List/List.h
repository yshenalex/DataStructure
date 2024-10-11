#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>

typedef int LTDataType;
typedef struct ListNode
{
	LTDataType data;
	struct ListNode* next;
	struct ListNode* prev;
}LTNode;

//【函数接口】

LTNode* ListInit();
void ListPrint(LTNode* phead);
LTNode* BuyListNode(LTNode* phead);

void ListPushBack(LTNode* phead, LTDataType x);
void ListPopBack(LTNode* phead);
void ListPushFront(LTNode* phead, LTDataType x);
void ListPopFront(LTNode* phead, LTDataType x);

LTNode* ListFind(LTNode* phead, LTDataType x);

void ListInsert(LTNode* pos, LTDataType x);
void ListErase(LTNode* pos);

void ListEraseEle(LTNode* phead, LTDataType x);//删除指定数值的首个元素

void ListDestroy(LTNode* phead);






















