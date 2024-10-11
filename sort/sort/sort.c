#define _CRT_SECURE_NO_WARNINGS
#include"sort.h"
#include"Stack.h"

void Swap(int* p, int* q)
{
	int tmp = *p;
	*p = *q;
	*q = tmp;
}

void InsertSort(int* arr, int size)//时间复杂度O(N^2)
{
	for (int i = 0; i < size - 1; i++)//需要n - 1躺：把每个元素都插入到合适位置；排完n趟，前面n个元素都是有序的
	{
		int end = i;//前面有序部分的末尾
		int e = arr[end + 1];//无序部分的第一个元素，即需要将其插入前面有序部分合适位置
		while (end >= 0)
		{
			if (e < arr[end])
			{
				arr[end + 1] = arr[end];//比e大的话，元素往后挪
				end--;
			}
			else
			{
				break;//直接跳出循环，与end=-1时情况合起来
			}
		}
		arr[end + 1] = e;//在比e小的元素后面插入
	}
}


void ShellSort(int* arr, int size)//时间复杂度介于O(N^1.25)~O(1.6*N^1.25)
{
	int gap = size;
	while (gap > 1)//每次更改gap的值，使数组多次调整后越来越接近有序，最后来一次插入排序(即gap=1时的希尔排序)
	{
		gap = gap / 3 + 1;//让gap每次mod3,; +1使得gap至少是1，不会出现是0的情况，因为最后要进行一次插入排序
		//希尔排序从插入排序优化而来，通过每次跳的gap间距，使每次排完接近有序，
		//最后gap=1时进行一次插入排序，耗时较短(一个数组越接近有序，插入排序耗时越短)
		for (int i = 0; i < size - gap; i++)//i每次+1，达到“分组并行排序(跳gap)”，即无需[0->0+gap->0+2*gap->……;1->1+gap->1+2*gap->……;……]
		{
			int end = i;
			int e = arr[end + gap];
			while (end >= 0)
			{
				if (arr[end] > e)
				{
					arr[end + gap] = arr[end];
					end -= gap;
				}
				else
				{
					break;
				}
			}
			arr[end + gap] = e;
		}
	}
}


void AdjustDown(int* arr, int size, int root)//向下调整算法；时间复杂度：O(logN)
{
	int parent = root;
	int child = parent * 2 + 1;
	while (child < size)
	{
		if (child + 1 < size && arr[child] < arr[child + 1])
		{
			child++;
		}
		if (arr[child] > arr[parent])
		{
			Swap(&arr[child], &arr[parent]);

			parent = child;
			child = parent * 2 + 1;
		}
		else
		{
			break;
		}
	}
}
void HeapSort(int* arr, int size)//时间复杂度O(N*logN):排升序->建大堆
{
	for (int i = (size - 1 - 1) / 2; i >= 0; i--)//建堆时间复杂度O(N)
	{
		AdjustDown(arr, size, i);
	}

	int i = 1;
	while (i < size)
	{
		Swap(&arr[0], &arr[size - i]);
		AdjustDown(arr, size - i, 0);
		i++;
	}
}


void SelectSort(int* arr, int size)//时间复杂度O(N^2)
{
	int begin = 0, end = size - 1;//设定一个区间，区间内找到最大值和最小值的下标，最大值放在末尾，最小值放在开头

	while (begin < end)
	{
		int maxi = begin, mini = begin;

		//遍历(begin,end]。之所以左开区间是因为我们假设了最大值最小值默认值为开头，反正无论如何都会比较到
		//当然写int i = begin 也可以，只是第一进入循环时什么都没干
		for (int i = begin + 1; i <= end; i++)
		{
			if (arr[i] > arr[maxi])
			{
				maxi = i;
			}
			if (arr[i] < arr[mini])
			{
				mini = i;
			}
		}

		Swap(&arr[begin], &arr[mini]);
		if (begin == maxi)//修订一下。因为可能最大值在开头，最小值在末尾，这样的话begin与mini交换后，下面end与maxi又交换回去了
		{
			maxi = mini;
		}
		Swap(&arr[end], &arr[maxi]);

		begin++;
		end--;
	}
}



void BubbleSort(int* arr, int size)//时间复杂度:O(N^2)
{
	for (int i = 0; i < size - 1; i++)
	{
		int exchange = 0;//优化：标记是否发生了交换
		for (int j = 0; j < size - 1 - i; j++)
		{
			if (arr[j] > arr[j + 1])
			{
				Swap(&arr[j], &arr[j + 1]);
				exchange = 1;//如果第一趟完整下来发生交换，说明是乱序的，
			}
		}

		if (exchange == 0)//若第一趟下来根本没发生交换，说明本来就有序，直接返回
			return;
	}
}

int GetMidIndex(int* arr, int begin, int end)//快排优化：尽量避免key选到最大和最小
{
	int mid = (begin + end) / 2;
	if (arr[begin] > arr[end])
	{
		if (arr[end] > arr[mid])
			return end;
		else if (arr[end] < arr[mid])
		{
			if (arr[begin] > arr[mid])
				return mid;
			else
				return begin;
		}
		else
			return end;
	}
	else if (arr[begin] < arr[end])
	{
		if (arr[end] < arr[mid])
			return end;
		else if (arr[end] > arr[mid])
		{
			if (arr[begin] < arr[mid])
				return mid;
			else
				begin;
		}
		else
			return end;
	}
	else
	{
		return begin;
	}
}
int PartSort1(int* arr, int begin, int end)//快速排序单趟：左右指针法
{
	int index = GetMidIndex(arr, begin, end);
	Swap(&arr[index], &arr[end]);

	int keyi = end;//末尾标记为key
	while (begin < end)
	{
		while (begin < end && arr[begin] <= arr[keyi])//左指针找大。注：必须有=号，否则可能出现死循环，下面同理
		{
			begin++;
		}
		while (begin < end && arr[end] >= arr[keyi])//右指针找小
		{
			end--;
		}
		Swap(&arr[begin], &arr[end]);
	}
	Swap(&arr[begin], &arr[keyi]);//我们让左边指针先走，这样停下来的位置必定是比keyi处大的元素，交换一下
	
	return begin;//返回begin或end都可以，此时二者相等
}

int PartSort2(int* arr, int begin, int end)//挖坑法
{
	int index = GetMidIndex(arr, begin, end);
	Swap(&arr[index], &arr[end]);

	int key = arr[end];//区间最后一个数的值视为key，保存起来，该位置视为坑
	while (begin < end)
	{
		while (begin < end && arr[begin] <= key)
		{
			begin++;
		}
		arr[end] = arr[begin];//左指针找大，找到之后，把该数填到坑的位置。同时该数位置形成新的坑
		while (begin < end && arr[end] >= key)
		{
			end--;
		}
		arr[begin] = arr[end];//右指针找小，找到之后，把该数填到坑的位置，即上一次的begin。同时该位置形成新的坑
	}
	arr[begin] = key;//最后把key填到坑去
	
	return begin;
}

int PartSort3(int* arr, int begin, int end)//前后指针法
{
	int index = GetMidIndex(arr, begin, end);
	Swap(&arr[index], &arr[end]);

	int cur = begin;
	int prev = begin - 1;
	int keyi = end;

	while (cur < end)//cur找小，找到之后++prev并与cur交换
	{
		if (arr[cur] < arr[keyi] && ++prev != cur)//cur与prev相等时换不换无所谓，那当然能不换就不换
		{
			Swap(&arr[prev], &arr[cur]);
		}
		cur++;
	}
	Swap(&arr[++prev], &arr[keyi]);//最后prev位置与keyi交换
	
	return prev;
}

void _QuickSort(int* arr, int left, int right)//递归实现
{
	if (left >= right)
		return;

	//int div = PartSort1(arr, left, right);
	//int div = PartSort2(arr, left, right);
	int div = PartSort3(arr, left, right);
	_QuickSort(arr, left, div - 1);//左边全部都比div处小，左边区间递归排一下
	_QuickSort(arr, div + 1, right);//右边全部都比div处大，右边区间递归排一下


	////快排优化：如果区间较短的时候，比如区间长度为10，此时没必要进行快排，因为要递归进去。即小区间我们直接用插入排序即可
	//if (right - left + 1 > 10)
	//{
	//	int div = PartSort3(arr, left, right);
	//	_QuickSort(arr, left, div - 1);
	//	_QuickSort(arr, div + 1, right);
	//}
	//else
	//{
	//	InsertSort(arr + left, right - left + 1);
	//}
}

// 【递归改非递归：
// 1、改循环(斐波拉契数列)——一些简单的递归才能改循环；
// 2、栈模拟存储数据非递归
// 【非递归好处：
// 1、提高效率(递归建立栈帧还是有消耗的，但是对于现代计算机，这个优化微乎其微可以忽略。
// 2、递归最大的缺陷是：如果栈帧的深度太深，可能会导致栈溢出，因为系统栈空间一般不大
void _QuickSortNonR(int* arr, int size)//非递归实现
{
	struct Stack st;
	StackInit(&st);

	StackPush(&st, size - 1);
	StackPush(&st, 0);

	while (!StackEmpty(&st))
	{
		int begin = StackTop(&st);
		StackPop(&st);
		int end = StackTop(&st);
		StackPop(&st);

		int div = PartSort3(arr, begin, end);

		if (div + 1 < end)//如果只有一个元素，就不再入栈了，直接认为是有序
		{
			StackPush(&st, end);
			StackPush(&st, div + 1);
		}
		if (begin < div - 1)
		{
			StackPush(&st, div - 1);
			StackPush(&st, begin);
		}
	}
}
void QuickSort(int* arr, int size)
{
	_QuickSort(arr, 0, size - 1);
	//_QuickSortNonR(arr, size - 1);
}

void _MergeSort(int* arr, int left, int right, int* tmp)
{
	if (left >= right)
		return;

	int mid = (right - left) / 2 + left;

	//递归子问题，左区间与右区间都有序
	_MergeSort(arr, left, mid, tmp);
	_MergeSort(arr, mid + 1, right, tmp);

	//归并[left, mid][mid + 1, right]
	int begin1 = left, end1 = mid;
	int begin2 = mid + 1, end2 = right;

	int index = left;
	while (begin1 <= end1 && begin2 <= end2)
	{
		if (arr[begin1] > arr[begin2])
			tmp[index++] = arr[begin2++];
		else
			tmp[index++] = arr[begin1++];
	}
	while (begin1 <= end1)
		tmp[index++] = arr[begin1++];
	while (begin2 <= end2)
		tmp[index++] = arr[begin2++];

	// 把归并好的的数组复制到原数组
	for (int i = left; i <= right; i++)
	{
		arr[i] = tmp[i];
	}
}

void _MergeSortNonR(int* a, int n)//非递归实现
{
	int* tmp = (int*)malloc(sizeof(int) * n);
	if (tmp == NULL)
	{
		perror("malloc fail");
		return;
	}

	int gap = 1;
	while (gap < n)
	{
		// gap个数据  gap个数据归并
		for (int j = 0; j < n; j += 2 * gap)
		{
			// 归并 取小的尾插
			int begin1 = j, end1 = j + gap - 1;
			int begin2 = j + gap, end2 = j + 2 * gap - 1;

			// 第一组越界
			if (end1 >= n)
			{
				break;
			}

			// 第二组全部越界
			if (begin2 >= n)
			{
				break;
			}

			// 第二组部分越界
			if (end2 >= n)
			{
				// 修正一下end2，继续归并
				end2 = n - 1;
			}

			int i = j;
			while (begin1 <= end1 && begin2 <= end2)
			{
				if (a[begin1] <= a[begin2])
				{
					tmp[i++] = a[begin1++];
				}
				else
				{
					tmp[i++] = a[begin2++];
				}
			}

			while (begin1 <= end1)
			{
				tmp[i++] = a[begin1++];
			}

			while (begin2 <= end2)
			{
				tmp[i++] = a[begin2++];
			}

			// 拷贝回原数组 -- 归并哪部分就拷贝哪部分回去
			memcpy(a + j, tmp + j, (end2 - j + 1) * sizeof(int));
		}

		gap *= 2;

	}

	free(tmp);
	tmp = NULL;
}

void MergeSort(int* arr, int size)//时间复杂度O(N*logN);空间复杂度O(N)
{
	int* tmp = (int*)malloc(size * sizeof(int));
	if (!tmp)
	{
		perror("malloc fail");
		exit(-1);
	}

	_MergeSort(arr, 0, size - 1, tmp);
	//_MergeSortNonR(arr, size);


	free(tmp);
	tmp = NULL;
}



// 时间复杂度：O(N+range)
// 空间复杂度：O(range)
// 适合数据范围集中，也就是range小
// 只适合整数，不适合浮点数、字符串等
void CountSort(int* arr, int size)
{
	int min = arr[0], max = arr[0];
	for (int i = 0; i < size; i++)
	{
		if (min > arr[i])
			min = arr[i];
		if (max < arr[i])
			max = arr[i];
	}

	int range = max - min + 1;
	int* tmp = (int*)malloc(range * sizeof(int));
	if(!tmp)
	{
		perror("malloc fail");
		exit(-1);
	}
	memset(tmp, 0, sizeof(int) * range);

	//统计次数
	for (int i = 0; i < size; i++)
	{
		tmp[arr[i] - min]++;//存相对位置
	}

	//排序
	int j = 0;
	for (int i = 0; i < range; i++)
	{
		while (tmp[i]--)
		{
			arr[j] = i + min;
			j++;
		}
	}

	free(tmp);
	tmp = NULL;
}
