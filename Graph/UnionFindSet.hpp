#pragma once
#include <iostream>
#include <vector>
using namespace std;

class UnionFindSet // 并查集实际上是一个森林，用双亲表示法表示树
{
public:
	// 初始时数组都设置为-1
	UnionFindSet(size_t size)
		: _ufs(size, -1)
	{
	}

	// 给一个元素的编号，找到该元素所在集合的名
	int FindRoot(int index)
	// 1.优化为小树并大树后，时间复杂度从O(N)->O(logN)。[注：数学归纳法可以证明：优化后的树高度为不超过[logN]+1。]
	// 2.进一步使用压缩路径优化后，时间复杂度不超过O(a(N))。其中a(N)为增长很慢的函数，
	// 甚至小于logN，对于常见的n，通常a(N)<=4，也就是说此时时间复杂度可以<=O(4),可以认为“查”是O(1)的操作
	{
		int root = index;

		// 不是负数就继续找
		while (_ufs[root] >= 0)
		{
			root = _ufs[root];
		}

		// 【优化2】路径压缩：边查找边压缩
		while (_ufs[index] >= 0)
		{
			int parent = _ufs[index];
			_ufs[index] = root; // 把所有都链到root上去，这样减少下一次查找的迭代层数
			index = parent;
		}

		return root;
	}

	bool Union(int x1, int x2) // 时间复杂度O(1)
	{
		int root1 = FindRoot(x1);
		int root2 = FindRoot(x2);

		// 若x1和x2本来就在一个集合，就不用合并了
		if (root1 == root2)
			return false;

		// 【优化1】控制数据量小的往数据量大的合并
		if (abs(_ufs[root1]) < abs(_ufs[root2]))
			swap(root1, root2);

		_ufs[root1] += _ufs[root2];
		_ufs[root2] = root1; // 将其中一个集合名称改变成另外一个

		return true;
	}

	size_t Count() const
	{
		size_t count = 0;
		for (auto &e : _ufs)
		{
			if (e < 0)
				count++;
		}

		return count;
	}

private:
	vector<int> _ufs;
};
