#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void Swap(int& x, int& y)
{
	int tmp = x;
	x = y;
	y = tmp;
}

void PrintArr(int* a, int n)
{
	for (int i = 0; i < n; i++)
	{
		printf("%d ", a[i]);
	}
	printf("\n");
}

void InsertSort(int* arr, int size)
{
	for (int i = 1; i < size; i++)
	{
		int tmp = arr[i];
		int j = i - 1;
		for (; j >= 0; j--)
		{
			if (tmp < arr[j])
				arr[j + 1] = arr[j];
			else
				break;
		}
		arr[j + 1] = tmp;
	}
}

void ShellSort(int* arr, int size)
{
	int d = size / 2;
	while (d >= 1)
	{
		for (int k = 0; k < d; k++)
		{
			for (int i = k + d; i < size; i += d)
			{
				int tmp = arr[i];
				int j = i - d;
				for (; j >= 0; j -= d)
				{
					if (tmp < arr[j])
						arr[j + d] = arr[j];
					else
						break;
				}
				arr[j + d] = tmp;
			}
		}

		d /= 2;
	}
}

void BubbleSort(int* arr, int n)
{
	for (int i = 0; i < n - 1; i++)
	{
		for (int j = 0; j < n - i - 1; j++)
		{
			if (arr[j] > arr[j + 1])
				Swap(arr[j], arr[j + 1]);
		}
	}
}

int partition(int* arr, int low, int high)
{
	int pivot = arr[low];

	while (low < high)
	{
		while (low < high && arr[high] >= pivot)
			high--;
		arr[low] = arr[high];
		while (low < high && arr[low] <= pivot)
			low++;
		arr[high] = arr[low];
	}

	arr[low] = pivot;

	return low;
}

void _QuickSort(int* arr, int low, int high)
{
	if (high - low <= 1)
		return;

	int index = partition(arr, low, high);
	_QuickSort(arr, low, index - 1);
	_QuickSort(arr, index + 1, high);
}

void QuickSort(int* arr, int n)
{
	_QuickSort(arr, 0, n - 1);
}

void SelectSort(int* arr, int n)
{
	for (int i = 0; i < n - 1; i++)
	{
		int index = i;
		for (int j = i; j < n; j++)
		{
			if (arr[j] < arr[index])
				index = j;
		}

		Swap(arr[index], arr[i]);
	}
}

void adjustDown(int* arr, int n, int pos)
{
	int parent = pos;
	int child = 2 * parent + 1;
	while (child < n)
	{
		if (child + 1 < n && arr[child] < arr[child + 1])
			child++;

		if (arr[child] > arr[parent])
		{
			Swap(arr[child], arr[parent]);
			parent = child;
			child = 2 * parent + 1;
		}
		else
		{
			break;
		}
	}
}

void HeapSort(int* arr, int n)
{
	for (int i = (n - 1 - 1) / 2; i >= 0; i--)
	{
		adjustDown(arr, n, i);
	}

	for (int i = 0; i < n - 1; i++)
	{
		Swap(arr[0], arr[n - i - 1]);
		adjustDown(arr, n - i - 1, 0);
	}
}

void _merge(int* arr, int low, int mid, int high)
{
	int* tmp = (int*)malloc((high - low + 1) * sizeof(int));
	for (int i = low; i <= high; i++)
		tmp[i - low] = arr[i];

	int k = low, i = 0, j = mid - low + 1;
	while (i <= mid - low && j <= high - low)
	{
		if (tmp[i] <= tmp[j])
			arr[k++] = tmp[i++];
		else
			arr[k++] = tmp[j++];
	}

	while (i <= mid - low)
		arr[k++] = tmp[i++];

	while (j <= high - low)
		arr[k++] = tmp[j++];

	free(tmp);
	tmp = NULL;
}

void _MergeSort(int* arr, int low, int high)
{
	if (low >= high)
		return;

	int mid = (high + low) / 2;
	_MergeSort(arr, low, mid);
	_MergeSort(arr, mid + 1, high);
	_merge(arr, low, mid, high);
}

void MergeSort(int* arr, int n)
{
	_MergeSort(arr, 0, n - 1);
}

void CountSort(int* arr, int n)
{
	int max = arr[0], min = arr[0];
	for (int i = 0; i < n; i++)
	{
		if (arr[i] > max)
			max = arr[i];
		if (arr[i] < min)
			min = arr[i];
	}

	// 初始辅助数组
	int range = max - min + 1;
	int* tmp = (int*)malloc(range * sizeof(int));
	if (tmp == NULL)
	{
		perror("malloc failed");
		exit(-1);
	}
	memset(tmp, 0, range * sizeof(int));
	for (int i = 0; i < n; i++)
		tmp[arr[i] - min]++;

	// 辅助数组修改为前缀和形式
	for (int i = 1; i < range; i++)
		tmp[i] = tmp[i - 1] + tmp[i];

	// 结果数组
	int* ret = (int*)malloc(n * sizeof(int));
	if (ret == NULL)
	{
		perror("malloc failed");
		exit(-1);
	}
	memset(ret, 0, n * sizeof(int));

	// 从后往前，根据辅助数组的值决定放置位置
	for (int i = n - 1; i >= 0; i--)
		ret[--tmp[arr[i] - min]] = arr[i]; // 相比于直接无脑取值放置，此处遍历每个元素可以保证稳定性

	for (int i = 0; i < n; i++)
		arr[i] = ret[i];

	free(tmp);
	free(ret);
}

int main()
{
	return 0;
}