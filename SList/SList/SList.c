#include"SList.h"


SLTNode* BuyListNode(SLTDataType x)
{
	SLTNode* newnode = (SLTNode*)malloc(sizeof(SLTNode));
	if (newnode == NULL)
	{
		perror("SListPushBack::");
		exit(-1);
	}
	newnode->data = x;
	newnode->next = NULL;

	return newnode;
}

void SListPrint(SLTNode* phead)
{
	assert(phead);

	SLTNode* cur = phead;
	while (cur != NULL)
	{
		printf("%d->", cur->data);
		cur = cur->next;
	}
	printf("NULL\n");
}

void SListPushBack(SLTNode** pphead, SLTDataType x)
{
	assert(pphead);

	SLTNode* newnode = BuyListNode(x);
	
	if (*pphead == NULL)
	{
		*pphead = newnode;
	}
	else
	{
		SLTNode* tail = *pphead;
		while (tail->next != NULL)
		{
			tail = tail->next;
		}
		tail->next = newnode;
	}
}

void SListPushFront(SLTNode** pphead, SLTDataType x)
{
	assert(pphead);

	SLTNode* newnode = BuyListNode(x);
	newnode->next = *pphead;
	*pphead = newnode;
}

void SListPopBack(SLTNode** pphead)
{
	assert(pphead);
	assert(*pphead);

	if ((*pphead)->next == NULL)//1.一个节点
	{
		free(*pphead);
		*pphead = NULL;
	}
	else//2.两个及以上节点
	{
		//法一：
		SLTNode* prev = NULL;
		SLTNode* tail = *pphead;
		while (tail->next != NULL)
		{
			prev = tail;
			tail = tail->next;
		}
		free(tail);
		tail = NULL;
		prev->next = NULL;
	
		//法二：
		//SLTNode* tail = *pphead;
		//while (tail->next->next != NULL)
		//{
		//	tail = tail->next;
		//}
		//free(tail->next);
		//tail->next = NULL;
	}
}

void SListPopFront(SLTNode** pphead)
{
	assert(pphead);
	assert(*pphead);

	SLTNode* next = (*pphead)->next;
	free(*pphead);
	*pphead = next;
}

SLTNode* SListFind(SLTNode* phead, SLTDataType x)//找到第一个数值等于这个数的节点
{
	SLTNode* cur = phead;
	while (cur != NULL)
	{
		if (cur->data == x)
			return cur;
		cur = cur->next;
	}
	return NULL;
}

void SListFindPrintAll(SLTNode* phead, SLTDataType x)
{
	SLTNode* pos = SListFind(phead, x);
	int i = 1;
	while (pos != NULL)
	{
		printf("第%d个pos节点：%p->%d\n", i++, pos, x);
		pos = SListFind(pos->next, x);
	}
}


void SListInsert(SLTNode** pphead, SLTNode* pos, SLTDataType x)
{
	assert(pphead);
	assert(pos);

	SLTNode* newnode = BuyListNode(x);
	if (*pphead == pos)
	{
		newnode->next = *pphead;
		*pphead = newnode;
	}
	else
	{
		SLTNode* posPrev = *pphead;
		while (posPrev->next != pos)
		{
			posPrev = posPrev->next;
		}
		posPrev->next = newnode;
		newnode->next = pos;
	}
}

void SListInsertAfter(SLTNode* pos, SLTDataType x)
{
	assert(pos);
	SLTNode* newnode = BuyListNode(x);
	newnode->next = pos->next;
	pos->next = newnode;
}


void SListErase(SLTNode** pphead, SLTNode* pos)
{
	assert(pphead);
	assert(pos);

	if (*pphead == pos)
	{
		//(1)自实现：
		//*pphead = pos->next;
		//free(pos);
		//pos = NULL;

		//(2)借用SListPopFront()：
		SListPopFront(pphead);
	}
	else
	{
		SLTNode* prev = *pphead;
		while (prev->next!=pos)
		{
			prev = prev->next;
		}
		prev->next = pos->next;
		free(pos);
		pos = NULL;//置不置空无所谓，因为pos是形参，是实参的临时拷贝。
		//你置空后不会影响实参,而且出了函数pos已经销毁了
	}
}

void SListEraseAfter(SLTNode* pos)
{
	assert(pos);
	assert(pos->next);//最后一个节点没有下一个可以删除，直接断言

	SLTNode* next = pos->next;
	pos->next = next->next;
	free(next);
	next = NULL;//同上，置不置空无所谓
}


void SListDestory(SLTNode** pphead)
{
	assert(pphead);

	SLTNode* cur = *pphead;
	while (cur)
	{
		SLTNode* next = cur->next;
		free(cur);
		cur = next;
	}
	*pphead = NULL;
}







