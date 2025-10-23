#include"SeqList.h"

void SeqListInit(SL* ps)
{
	ps->a = NULL;
	ps->size = ps->capacity = 0;
}


void SeqListCheckCapacity(SL* ps)
{
	if (ps->size == ps->capacity)
	{
		int newcapacity = ps->capacity == 0 ? 4 : ps->capacity * 2;//我们一般选择增容为原来2倍
		SLDataType* tmp = realloc(ps->a, newcapacity * sizeof(SLDataType));//当传给realloc的是空指针的时候，realloc相当于malloc
		if (tmp == NULL)
		{
			perror("SeqListPushBack::");
			exit(-1);
		}
		ps->a = tmp;
		ps->capacity = newcapacity;
	}
}

void SeqListPushBack(SL* ps, SLDataType x)
{
	//(1)自实现
	//SeqListCheckCapacity(ps);
	//ps->a[ps->size] = x;
	//ps->size++;

	//(2)借用SeqListInsert()：
	SeqListInsert(ps, ps->size, x);
}


void SeqListPopBack(SL* ps)
{
	//(1)自实现：
	//温柔处理方式：
	/*if (ps->size > 0)
	{
		ps->size--;
	}*/

	//暴力处理方式：
	//assert(ps->size>0);
	//ps->size--;

	//(2)利用SeqListErase();
	SeqListErase(ps, ps->size - 1);
}


void SeqListPushFront(SL* ps, SLDataType x)
{
	//(1)自实现：
	//SeqListCheckCapacity(ps);
	//int end = ps->size - 1;
	//while (end >= 0)
	//{
	//	ps->a[end + 1] = ps->a[end];
	//	end--;
	//}
	//ps->a[0] = x;
	//ps->size++;

	//(2)借用SeqListInsert();
	SeqListInsert(ps, 0, x);

}


void SeqListPopFront(SL* ps)
{
	//(1)自实现：
	//assert(ps->size > 0);
	//int begin = 1;
	//while (begin < ps->size)
	//{
	//	ps->a[begin - 1] = ps->a[begin];
	//	begin++;
	//}
	//ps->size--;

	//(2)借用SeqListErase();
	SeqListErase(ps, 0);
}

int SeqListFind(SL* ps, SLDataType x)
{
	int i = 0;
	for (i = 0; i < ps->size; i++)
	{
		if (ps->a[i] == x)
			return i;
	}

	return -1;
}


void SeqListInsert(SL* ps, int pos, SLDataType x)
{
	assert(pos >= 0 && pos <= ps->size);
	SeqListCheckCapacity(ps);

	int end = ps->size - 1;
	while (end >= pos)
	{
		ps->a[end + 1] = ps->a[end];
		end--;
	}
	ps->a[pos] = x;
	ps->size++;
}

void SeqListErase(SL* ps, int pos)
{
	assert(pos >= 0 && pos < ps->size);

	int begin = pos + 1;
	while (begin < ps->size)
	{
		ps->a[begin - 1] = ps->a[begin];
		begin++;
	}
	ps->size--;
}


void SeqListEraseByElement(SL* ps, SLDataType x)
{
	int pos = SeqListFind(ps, x);
	SeqListErase(ps, pos);
}


void SeqListDestory(SL* ps)
{
	free(ps->a);
	ps->a = NULL;
	ps->size = ps->capacity = 0;
}


