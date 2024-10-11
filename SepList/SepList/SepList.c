#include"SepList.h"

void SepListInit(SL* ps)
{
	ps->a = NULL;
	ps->size = ps->capacity = 0;
}


void SepListCheckCapacity(SL* ps)
{
	if (ps->size == ps->capacity)
	{
		int newcapacity = ps->capacity == 0 ? 4 : ps->capacity * 2;//我们一般选择增容为原来2倍
		SLDataType* tmp = realloc(ps->a, newcapacity * sizeof(SLDataType));//当传给realloc的是空指针的时候，realloc相当于malloc
		if (tmp == NULL)
		{
			perror("SepListPushBack::");
			exit(-1);
		}
		ps->a = tmp;
		ps->capacity = newcapacity;
	}
}

void SepListPushBack(SL* ps, SLDataType x)
{
	//(1)自实现
	//SepListCheckCapacity(ps);
	//ps->a[ps->size] = x;
	//ps->size++;

	//(2)借用SepListInsert()：
	SepListInsert(ps, ps->size, x);
}


void SepListPopBack(SL* ps, SLDataType x)
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

	//(2)利用SepListErase();
	SepListErase(ps, ps->size - 1);
}


void SepListPushFront(SL* ps, SLDataType x)
{
	//(1)自实现：
	//SepListCheckCapacity(ps);
	//int end = ps->size - 1;
	//while (end >= 0)
	//{
	//	ps->a[end + 1] = ps->a[end];
	//	end--;
	//}
	//ps->a[0] = x;
	//ps->size++;

	//(2)借用SepListInsert();
	SepListInsert(ps, 0, x);

}


void SepListPopFront(SL* ps, SLDataType x)
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

	//(2)借用SepListErase();
	SepListErase(ps, 0);
}

int SepListFind(SL* ps, SLDataType x)
{
	int i = 0;
	for (i = 0; i < ps->size; i++)
	{
		if (ps->a[i] == x)
			return i;
	}

	return -1;
}


void SepListInsert(SL* ps, int pos, SLDataType x)
{
	assert(pos >= 0 && pos <= ps->size);
	SepListCheckCapacity(ps);

	int end = ps->size - 1;
	while (end >= pos)
	{
		ps->a[end + 1] = ps->a[end];
		end--;
	}
	ps->a[pos] = x;
	ps->size++;
}

void SepListErase(SL* ps, int pos)
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


void SepListEraseByElement(SL* ps, SLDataType x)
{
	int pos = SepListFind(ps, x);
	SepListErase(ps, pos);
}


void SepListDestory(SL* ps)
{
	free(ps->a);
	ps->a = NULL;
	ps->size = ps->capacity = 0;
}















