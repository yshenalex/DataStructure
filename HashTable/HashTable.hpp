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

	/**
	 * @brief 默认的T类型映射为size_t类型的方法
	 *
	 * @tparam T
	 */
	template <typename T>
	struct DefaultFunctor
	{
		size_t operator()(const T& x)
		{
			return (size_t)x;
		}
	};

	// 对于字符串，使用常见的字符串哈希算法映射为整数
	template <>
	struct DefaultFunctor<string>
	{
		size_t operator()(const string& x)
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
			// HACK: 其实哈希表可能存在很多DELETED元素，看着很空实际很满，设计定期调整会比较好
			if ((static_cast<float>(_n) / _data.size()) >= loadFactor)
				_reHashing();

			int pos = _hash(val);

			// 平方探测法偏移量
			int d = 1;
			// 控制正负交替
			bool direction = true;

			// HACK: 其实可能找不到位置插入，对于平方探测法，只有当散列表长度为4*j+3(j=0,1,2,3...)的质数时才能够遍历到所有位置【数论】
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
				_setNextPos(pos, direction, d);
			}
		}

		bool erase(T val)
		{
			int pos = find(val);
			if (pos == -1)
				return false;

			// 不进行_n--操作，只将有效数据个数--
			_size--;

			_data[pos].stat = DELETED;
		}

		int find(T val)
		{
			int pos = _hash(val);

			int d = 1;
			bool direction = true;
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
				_setNextPos(pos, direction, d);
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
		/**
		 * @brief 哈希函数
		 *
		 * @param val 外部传入的需要存储的数值
		 * @return int 经过哈希函数映射的位置
		 */
		int _hash(T val)
		{
			Functor functor;
			int pos = functor(val) % _divisor;
			return pos;
		}

		// 再散列
		void _reHashing()
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

		/**
		 * @brief 平方探测法获取下一个位置
		 *
		 * @param pos 旧位置
		 * @param direction 正向或反向; true: 正向, false: 反向
		 * @param d 偏移量
		 */
		void _setNextPos(int& pos, bool& direction, int& d)
		{
			if (direction)
			{
				// 正向
				pos = (pos + d * d) % _data.size();
				direction = false;
			}
			else
			{
				// 反向
				pos = (pos - d * d) % _data.size();
				direction = true;
				d++;
			}
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

#include <memory>
namespace SeparateChaining
{
	using std::cout;
	using std::endl;
	using std::string;
	using std::swap;
	using std::vector;

	static const int initSize = 11;
	static const int resizeFactor = 2;

	template <typename T>
	struct DefaultFunctor
	{
		size_t operator()(const T& x)
		{
			return (size_t)x;
		}
	};

	template <>
	struct DefaultFunctor<string>
	{
		size_t operator()(const string& x)
		{
			size_t hash = 0;
			for (auto ch : x)
			{
				hash = hash * 131 + ch;
			}
			return hash;
		}
	};

	template <typename T>
	struct HashNode
	{
		T val;
		HashNode<T>* next;

		HashNode(T val = T())
			: val(val), next(nullptr)
		{
		}
	};

	template <typename T, typename Functor = DefaultFunctor<T>>
	class HashTable
	{
		using Node = HashNode<T>;

	public:
		HashTable()
		{
			_tables.resize(initSize, nullptr);
			_n = 0;
		}

		bool insert(T val)
		{
			if (_n == _tables.size())
				_rehashing();

			if (find(val))
				return false;

			int pos = _hash(val);
			// OPTIMIZE: 此处可以按序插入，形成有序链表，这样查找效率为提高
			Node* newNode = new Node(val);
			newNode->next = _tables[pos];
			_tables[pos] = newNode;
			_n++;

			return true;
		}

		bool erase(T val)
		{
			int pos = _hash(val);

			Node* parent = nullptr;
			Node* cur = _tables[pos];
			while (cur)
			{
				if (cur->val == val)
				{
					if (parent)
						parent->next = cur->next;
					else
						_tables[pos] = _tables[pos]->next;

					delete cur;
					_n--;
					return true;
				}

				parent = cur;
				cur = cur->next;
			}

			return false;
		}

		bool find(T val)
		{
			int pos = _hash(val);

			Node* cur = _tables[pos];
			while (cur)
			{
				if (cur->val == val)
					return true;

				cur = cur->next;
			}
			return false;
		}

		size_t size() const
		{
			return _n;
		}

		bool empty() const
		{
			return _n == 0;
		}

		void Print()
		{
			for (int i = 0; i < _tables.size(); i++)
			{
				Node* cur = _tables[i];
				while (cur)
				{
					cout << cur->val << " ";
					cur = cur->next;
				}
			}
			cout << endl;
		}

		~HashTable()
		{
			for (int i = 0; i < _tables.size(); i++)
			{
				Node* cur = _tables[i];
				while (cur)
				{
					Node* next = cur->next;
					delete cur;
					cur = next;
				}
				// 不要忘记把哈希表各个初始节点置空，否则析构函数调用时将导致重复释放资源错误
				_tables[i] = nullptr;
			}
		}

	private:
		int _hash(T val)
		{
			Functor functor;
			return functor(val) % _tables.size();
		}

		void _rehashing()
		{
			HashTable<T, Functor> newHashTable;

			// 我们希望哈希表长度为素数
			int newSize = _tables.size() * resizeFactor;
			while (!_isPrimeNum(newSize))
			{
				newSize++;
			}
			newHashTable._tables.resize(newSize, nullptr);

			// 原哈希表的数据逐个重新插入到新哈希表中
			for (int i = 0; i < _tables.size(); i++)
			{
				Node* cur = _tables[i];
				while (cur)
				{
					Node* next = cur->next;

					int pos = newHashTable._hash(cur->val);
					cur->next = newHashTable._tables[pos];
					newHashTable._tables[pos] = cur;
					newHashTable._n++;

					cur = next;
				}
				// 不要忘记把哈希表各个初始节点置空，否则析构函数调用时将导致重复释放资源错误
				_tables[i] = nullptr;
			}

			swap(*this, newHashTable);
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
		vector<Node*> _tables;
		// 有效数据个数
		size_t _n;
	};
}