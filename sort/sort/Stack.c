#include"Stack.h"

void StackInit(ST* ps)
{
	assert(ps);
	ps->a = NULL;
	ps->top = 0;//top初始化为0，意味着top表示栈顶元素上一个位置
	//也可以：ps->top=-1;
	ps->capacity = 0;
}

void StackPush(ST* ps, STDataType x)
{
	assert(ps);

	if (ps->top == ps->capacity)
	{
		int newCapacity = ps->capacity == 0 ? 4 : ps->capacity * 2;
		STDataType* tmp = (STDataType*)realloc(ps->a, sizeof(STDataType) * newCapacity);
		if (tmp == NULL)
		{
			perror("StackPush::");
			exit(-1);
		}
		ps->a = tmp;
		ps->capacity = newCapacity;
	}

	ps->a[ps->top] = x;
	ps->top++;
}

void StackDestroy(ST* ps)
{
	assert(ps);

	free(ps->a);
	ps->a = NULL;
	ps->top = ps->capacity = 0;
}

void StackPop(ST* ps)
{
	assert(ps);
	assert(!StackEmpty(ps));
	//【注意】top>0才可以删除，否则删除后top为负数，下标无法与前面规则一致
	ps->top--;
}

STDataType StackTop(ST* ps)
{
	assert(ps);
	assert(!StackEmpty(ps));
	return ps->a[ps->top - 1];
}


bool StackEmpty(ST* ps)
{
	assert(ps);
	return ps->top == 0;
}

int StackSize(ST* ps)
{
	assert(ps);
	return ps->top;
}

void StackPrint(ST ps)
//(个思)由于pop会修改栈数据，为了多次打印，尝试使用传值调用(形参改变不会影响实参，top不会改变，区别于QueuePop)
{
	while (!StackEmpty(&ps))
	{
		printf("%d ", StackTop(&ps));
		StackPop(&ps);
	}
	printf("\n");
}













