#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>

// 队列元素类型为TreeNode*
#include "BinaryTree.h"
typedef TreeNode *QDataType;

typedef struct QueueNode
{
	struct QueueNode *next;
	QDataType data;
} QueueNode;

typedef struct Queue
{
	QueueNode *head;
	QueueNode *tail;
} Queue;

void QueueInit(Queue *pq);
void QueueDestroy(Queue *pq);
void QueuePush(Queue *pq, QDataType x);
void QueuePop(Queue *pq);
QDataType QueueFront(Queue *pq);
QDataType QueueBack(Queue *pq);
int QueueSize(Queue *pq);
bool QueueEmpty(Queue *pq);
