#include "mystl_bitset.hpp"
#include <string>
#include <bitset>
using std::string;
using mystl::bitset;

// 三个用于将字符串转为无符号整型的仿函数, 直接copy
struct BKDRHash;
struct APHash;
struct DJBHash;

// 倍数。外面指定的布隆过滤器模板参数N并不是布隆过滤器大小，而是插入的个数，为了降低误判率，实际大小为N * times
static const size_t times = 5;
// 哈希映射函数个数。暂时设定为3，意味着每个字符串将被映射到位图的三个位置
static const size_t hashCount = 3;


/**
 * @brief 布隆过滤器，支持插入字符串对象。底层借助位图实现。
 * 支持insert、contains、clear，不支持删除元素操作，因为可能导致其他元素映射的比特位被修改，导致其他元素判断是否存在时出错
 * @tparam N 插入的元素个数，非布隆过滤器大小
 */
template<size_t N>
class BloomFilter
{
private:
    // 三个哈希映射函数别名:

	using Hash1 = BKDRHash;
	using Hash2 = APHash;
	using Hash3 = DJBHash;
public:

    /**
     * @brief 将字符串插入布隆过滤器
     * 
     * @param s 
     */
	void insert(const string& s)
	{
        // 通过哈希映射函数将对应的字符串映射取模后，将位图对应的比特位置为1
		if (hashCount >= 1)
			_bs.set(Hash1()(s) % _bs.size());
		if (hashCount >= 2)
			_bs.set(Hash2()(s) % _bs.size());
		if (hashCount >= 3)
			_bs.set(Hash3()(s) % _bs.size());
		// 可以扩展更多哈希映射仿函数...
	}

	bool contains(const string& s)
	{
        // 布隆过滤器判断一个对象不在其中是非常准确的，只要通过哈希映射找到对应的几个比特位(此处为3)
        // 如果存在，那么三个比特位肯定都是1，但凡有一个是0，就意味着肯定不存在
		if (hashCount >= 1 && _bs.test(Hash1()(s) % _bs.size()) == false)
			return false;
		if (hashCount >= 2 && _bs.test(Hash2()(s) % _bs.size()) == false)
			return false;
		if (hashCount >= 3 && _bs.test(Hash3()(s) % _bs.size()) == false)
			return false;
		// 可以扩展更多哈希映射仿函数...
        
        // 布隆过滤器判断一个对象在其中是存在一定误判率，因为可能这个对象映射的3个位置正好被其他几个对象映射位置覆盖
        // 此处返回true其实不见得该对象就在布隆过滤器中
		return true;
	}

	void clear()
	{
		_bs.reset();
	}
	
private:
	bitset<N * times> _bs; // 底层的位图开N * times(5)的大小，尽可能降低误判率
};



struct BKDRHash
{
	size_t operator()(const string& s)
	{
		size_t hash = 0;
		for (auto& ch : s)
		{
			hash = hash * 131 + ch;
		}
		return hash;
	}
};

struct APHash
{
	size_t operator()(const string& s)
	{
		size_t hash = 0;
		for (long i = 0; i < s.size(); i++)
		{
			if ((i & 1) == 0)
			{
				hash ^= ((hash << 7) ^ s[i] ^ (hash >> 3));
			}
			else
			{
				hash ^= (~((hash << 11) ^ s[i] ^ (hash >> 5)));
			}
		}
		return hash;
	}
};

struct DJBHash
{
	size_t operator()(const string& s)
	{
		size_t hash = 5381;
		for (auto& ch : s)
		{
			hash += (hash << 5) + ch;
		}
		return hash;
	}
};
