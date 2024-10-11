#include"Heap.h"

void Swap(HPDataType* e1, HPDataType* e2)
{
	HPDataType tmp = *e1;
	*e1 = *e2;
	*e2 = tmp;
}

void AdjustDown(HPDataType* a, int n, int root)//向下调整算法。前提：堆顶的左右子树都是堆。此处调整为小堆。
{
	int parent = root;
	int child = parent * 2 + 1;//先假设左孩子为目标，即左孩子小于右孩子，后面再调

	while (child < n)//孩子节点下标在堆下标范围内就可以调整
	{
		if (child + 1 < n && a[child + 1] < a[child])//如果右孩子更小就将右孩子与双亲节点交换，但需要注意避免越界访问
			child++;

		if (a[child] < a[parent])//较小的孩子小于双亲节点就交换
		{
			Swap(&a[child], &a[parent]);
			
			//继续向下调整：
			parent = child;
			child = child * 2 + 1;
		}
		else//双亲结点小于较小的孩子节点就可以直接退出循环了
		{
			break;
		}
	}
}

void HeapInit(Heap* php, HPDataType* a, int n)
{
	assert(php);
	
	php->_a = (HPDataType*)malloc(sizeof(HPDataType) * n); 
	if (php->_a == NULL)
	{
		perror("HeapInit::");
		exit(-1);
	}
	memcpy(php->_a, a, sizeof(HPDataType) * n);
	php->_size = php->_capacity = n;

	//构建堆
	for (int i = (n - 1 - 1) / 2; i >= 0; i--)
	{
		AdjustDown(php->_a, php->_size, i);
	}
}

void HeapDestroy(Heap* php)
{
	assert(php);

	free(php->_a);
	php->_a = NULL;
	php->_capacity = php->_size = 0;
}

void AdjustUp(HPDataType* a, int child)//向上调整算法
{
	int parent = (child - 1) / 2;

	//while(parent >= 0)  
	//这样写其实是不对的，因为parent永远都大于等于0
	while (child > 0)//child跑到堆顶时结束循环
	{
		if (a[parent] > a[child])
		{
			Swap(&a[parent], &a[child]);
			child = parent;
			parent = (child - 1) / 2;
		}
		else
		{
			break;
		}
	}
}


void HeapPush(Heap* php, HPDataType x)
{
	assert(php);

	if (php->_capacity == php->_size)//判断是否需要扩容
	{
		HPDataType* tmp = (HPDataType*)realloc(php->_a, sizeof(HPDataType) * php->_capacity * 2);
		if (tmp == NULL)
		{
			perror("HeapPush::");
			exit(-1);
		}
		php->_a = tmp;
		php->_capacity *= 2;
	}

	php->_a[php->_size++] = x;//尾插

	AdjustUp(php->_a, php->_size - 1);//向上调整为堆
}

void HeapPop(Heap* php)
{
	assert(php);
	assert(php->_size > 0);

	Swap(&php->_a[0], &php->_a[php->_size - 1]);
	php->_size--;

	AdjustDown(php, php->_size, 0);
}

HPDataType HeapTop(Heap* php)
{
	assert(php);
	assert(php->_size > 0);

	return php->_a[0];
}

bool HeapEmpty(Heap* php)
{
	assert(php);
	return php->_size == 0;
}

int HeapSize(Heap* php)
{
	assert(php);
	return php->_size;
}


void HeapSort(int* a, int n)//堆排序，时间复杂度：O(N*logN)，此处排降序
{
	//建小堆，时间复杂度：O(N)
	for (int i = (n - 1 - 1) / 2; i >= 0; i--)
	{
		AdjustDown(a, n, i);
	}

	//排序
	int end = n - 1;
	while (end > 0)
	{
		Swap(&a[0], &a[end]);

		//
		AdjustDown(a, end, 0);
		end--;

	}
}