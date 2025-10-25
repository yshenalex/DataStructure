#include <vector>
#include <iostream>
#include <string>
namespace OpenAddressing
{

	using std::cout;
	using std::endl;
	using std::string;
	using std::vector;
	// 初始容量
	static const int initSize = 11;
	// 负载因子
	static const float loadFactor = 0.7f;
	// 扩容倍数
	static const int resizeFactor = 2;

	// 状态值
	enum Status
	{
		EMPTY,
		EXIST,
		DELETED
	};

	template <typename T>
	struct Element
	{
		T val;
		Status stat;

		Element(T val = T())
			: val(val), stat(EMPTY)
		{
		}
	};

	template <typename T>
	struct DefaultFunctor
	{
		size_t operator()(const T &x)
		{
			return (size_t)x;
		}
	};

	// 对于字符串，使用常见的字符串哈希算法映射为整数
	template <>
	struct DefaultFunctor<string>
	{
		size_t operator()(const string &x)
		{
			size_t hash = 0;
			for (auto ch : x)
			{
				hash = hash * 131 + ch;
			}
			return hash;
		}
	};

	template <typename T, typename Functor = DefaultFunctor<T>>
	class HashTable
	{
	public:
		HashTable()
		{
			_data.resize(initSize);
			_setDivisor(initSize);
			_n = _size = 0;
		}

		bool insert(T val)
		{
			if ((static_cast<float>(_n) / _data.size()) >= loadFactor)
			{
				HashTable<T, Functor> newHashTable;
				newHashTable._data.resize(_data.size() * resizeFactor);
				newHashTable._n = _n;
				newHashTable._size = _size;
				newHashTable._setDivisor(newHashTable._data.size());
				for (int i = 0; i < _data.size(); i++)
				{
					if (_data[i].stat != EMPTY) // 空位置数据不要插入扩容后的哈希表
						newHashTable.insert(_data[i].val);
				}

				_data.swap(newHashTable._data);
				_divisor = newHashTable._divisor;
			}

			size_t pos = _hash(val);

			// 平方探测法偏移量
			int i = 1;
			// 控制正负交替
			bool flag = true;

			// FIXME: 其实可能找不到位置插入，对于平方探测法，只有当散列表长度为4*j+3(j=0,1,2,3...)的质数时才能够遍历到所有位置【数论】
			while (true)
			{
				if (_data[pos].stat == EXIST && _data[pos].val == val)
				{
					// 本来就有了还插入即插入失败
					return false;
				}

				if (_data[pos].stat == EMPTY) // 找到空位置可以插入
				{
					_data[pos].val = val;
					_data[pos].stat = EXIST;
					_n++;
					_size++;
					return true;
				}
				// 找到的位置是原来被删除的，且数值跟要插入的一样，直接恢复即可
				else if (_data[pos].stat == DELETED && _data[pos].val == val)
				{
					_data[pos].stat = EXIST;

					// 这里设计为不进行_n++，因为_n设计为非空元素个数(含DELETED)，只将有效数据个数--
					// _n++;
					_size++;
					return true;
				}

				
				// 平方探测法：
				if (flag)
				{
					// 正向
					pos = (pos + i * i) % _data.size();
					flag = false;
				}
				else
				{
					// 反向
					pos = (pos - i * i) % _data.size();
					flag = true;
					i++;
				}
			}
		}

		bool erase(T val)
		{
			size_t pos = find(val);
			if (pos == -1)
				return false;

			// 不进行_n--操作，只将有效数据个数--
			_size--;

			_data[pos].stat = DELETED;
		}

		int find(T val)
		{
			size_t pos = _hash(val);

			int i = 1;
			bool flag = true;
			while (true)
			{
				// 如果位置为空，那么查找的元素就应该插入这里，结果没插，说明不存在
				if (_data[pos].stat == EMPTY)
					return -1;
				// 如果该位置已经被删除，且就是保留元素那个数值，说明不存在
				else if (_data[pos].stat == DELETED && _data[pos].val == val)
					return -1;
				// 如果位置存在且就是寻找元素的值，说明找到了
				else if (_data[pos].stat == EXIST && _data[pos].val == val)
					return pos;
				// 其他情况就继续迭代查找：

				if (flag)
				{
					// 正向
					pos = (pos + i * i) % _data.size();
					flag = false;
				}
				else
				{
					// 反向
					pos = (pos - i * i) % _data.size();
					flag = true;
					i++;
				}
			}
		}

		// 不是哈希表有效数据个数，而是非空数据个数(含DELETED和EXIST)
		size_t size() const
		{
			return _size;
		}

		bool empty() const
		{
			return _size == 0;
		}

		void Print()
		{
			for (int i = 0; i < _data.size(); i++)
			{
				if (_data[i].stat == EXIST)
					cout << _data[i].val << " ";
			}
			cout << endl;
		}

		~HashTable()
		{
		}

	private:
		size_t _hash(T val)
		{
			Functor functor;
			size_t pos = functor(val) % _divisor;
			return pos;
		}

		void _setDivisor(size_t num)
		{
			while (!_isPrimeNum(num) && num > 1)
			{
				num--;
			}

			_divisor = num;
		}

		bool _isPrimeNum(size_t num)
		{
			if (num == 1 || num == 2)
				return true;

			for (int i = 2; i * i <= num; i++)
			{
				if (num % i == 0)
					return false;
			}

			return true;
		}

	private:
		// 哈希表底层存放数组
		vector<Element<T>> _data;
		// 除留余数法的除数，设置为不大于数组长度的最大质数
		size_t _divisor;
		// 哈希表中【非空】数据个数(含EXIST和DELETED)
		size_t _n;
		// 哈希表【有效】数据个数(EXIST)
		size_t _size;
	};
}
