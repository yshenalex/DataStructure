#include"List.h"
//【双向带头循环链表】


LTNode* ListInit()
{
	//哨兵位头结点
	LTNode* phead = (LTNode*)malloc(sizeof(LTNode));
	phead->prev = phead;
	phead->next = phead;

	return phead;
}

void ListPrint(LTNode* phead)
{
	assert(phead);

	LTNode* cur = phead->next;
	while (cur != phead)
	{
		printf("%d ", cur->data);
		cur = cur->next;
	}
	printf("\n");
}

LTNode* BuyListNode(LTDataType x)
{
	LTNode* newnode = (LTNode*)malloc(sizeof(LTNode));
	newnode->data = x;
	newnode->prev = NULL;
	newnode->next = NULL;

	return newnode;
}

void ListPushBack(LTNode* phead, LTDataType x)
{
	assert(phead);



	//(1)自实现
	//LTNode* newnode = BuyListNode(x);

	////法一：借助变量tail,逻辑更清晰
	//LTNode* tail = phead->prev;
	//tail->next = newnode;
	//newnode->prev = tail;
	//newnode->next = phead;
	//phead->prev = newnode;

	////法二：不借助变量，需要注意顺序
	////newnode->prev = phead->prev;
	////newnode->next = phead;
	////phead->prev->next = newnode;
	////phead->prev = newnode;


	//(2)借用ListInsert();
	ListInsert(phead, x);
}

void ListPopBack(LTNode* phead)
{
	assert(phead);
	assert(phead->next!=phead);

	//(1)自实现
	//LTNode* tail = phead->prev;
	//LTNode* tailPrev = phead->prev->prev;

	//free(tail);
	//tail = NULL;
	//tailPrev->next = phead;
	//phead->prev = tailPrev;

	//(2)借用ListErase();
	ListErase(phead->prev);
}

void ListPushFront(LTNode* phead, LTDataType x)
{
	assert(phead);


	//(1)自实现
	//LTNode* newnode = BuyListNode(x);
	//LTNode* next = phead->next;

	//phead->next = newnode;
	//newnode->prev = phead;
	//newnode->next = next;
	//next->prev = newnode;

	//(2)借用ListInsert();
	ListInsert(phead->next, x);
}

void ListPopFront(LTNode* phead, LTDataType x)
{
	assert(phead);
	assert(phead->next!=phead);


	//(1)自实现
	//LTNode* next = phead->next;
	//LTNode* nextNext = phead->next->next;

	//phead->next = nextNext;
	//nextNext->prev = phead;
	//free(next);
	//next = NULL;

	//(2)借用ListErase();
	ListErase(phead->next);
}


LTNode* ListFind(LTNode* phead, LTDataType x)
{
	assert(phead);

	LTNode* cur = phead->next;
	while (cur != phead)
	{
		if (cur->data == x)
			return cur;
		cur = cur->next;
	}
	return NULL;
}


void ListInsert(LTNode* pos, LTDataType x)//在pos位置之前插入
{
	assert(pos);

	LTNode* posPrev = pos->prev;
	LTNode* newnode = BuyListNode(x);

	posPrev->next = newnode;
	newnode->prev = posPrev;
	newnode->next = pos;
	pos->prev = newnode;
}


void ListErase(LTNode* pos)//删除pos位置
{
	assert(pos);

	LTNode* posPrev = pos->prev;
	LTNode* posNext = pos->next;

	posPrev->next = posNext;
	posNext->prev = posPrev;

	free(pos);
	pos = NULL;
}


void ListEraseEle(LTNode* phead,LTDataType x)//删除指定元素
{
	LTNode* pos = ListFind(phead, x);
	if (pos != NULL)
	{
		ListErase(pos);
	}
	else
		assert(pos);
}

void ListDestroy(LTNode* phead)
{
	assert(phead);

	LTNode* cur = phead->next;
	while (cur != phead)
	{
		LTNode* next = cur->next;
		free(cur);
		cur = next;
	}

	free(phead);
	phead = NULL;
	//形参改变不会影响实参plist,但为了整洁性，
	//我们此处不传二级指针，在外部再重新置空plist
}






















