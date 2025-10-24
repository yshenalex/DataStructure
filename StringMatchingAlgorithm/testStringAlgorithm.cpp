#include <iostream>
#include <string>
#include <vector>
using namespace std;

// 【BF算法】
int BruteForce(string str, string sub)
{
	int lenStr = str.size(), lenSub = sub.size();
	if (!lenStr || !lenSub)
		return -1;

	int i = 0, j = 0; // 记录主串和子串的下标
	while (i < lenStr && j < lenSub)
	{
		if (str[i] == sub[j]) // 相同就继续比较
		{
			i++;
			j++;
		}
		else // 不同的话，将j置为0，i回到刚刚出发比较的下一个节点，即i-j+1
		{
			i = i - j + 1;
			j = 0;
		}
	}

	if (j == lenSub) // 如果是子串遍历到终点，那就是找到了，i此次出发时返回下标
		return i - j;

	return -1; // 若是主串到终点，那就是没找到，返回-1
}

// 【KMP算法】
void GetNext(string sub, vector<int> &next) // 获得next数组
{
	int lenSub = sub.size();
	next.resize(lenSub);
	next[0] = -1; // 下标为0处默认回退到-1

	if (lenSub == 1)
		return;

	next[1] = 0; // 下标为0处默认回退到0

	int k = 0; // 前一项(即下标为i-1的位置)元素回退到的下标k，即k = next[i - 1]
	int i = 2; // 当前位置i的下标

	while (i < lenSub) // KMP算法与BF算法的区别：i只前进不后退
	{
		if (k == -1 || sub[k] == sub[i - 1]) // 当i-1元素与k位置元素相同时，那么next[i]就应该是k+1；注：当k回退到-1时也符合条件
		{
			next[i] = k + 1;
			k++;
			i++;
		}
		else
		{
			k = next[k]; // 否则就继续回退，直到符合条件
		}
	}
}
void GetNextval(string sub, vector<int> &next, vector<int> &nextval) // next数组的优化
{
	int n = next.size();
	nextval.resize(n);
	int i = 0;
	while (i < n)
	{
		if (nextval[i] == -1)
		{
			i++;
		}
		else if (next[i] == -1)
		{
			nextval[i] = next[i];
			i++;
		}
		else if (sub[i] == sub[next[i]])
		{
			nextval[i] = next[next[i]];
		}
		else
		{
			nextval[i] = next[i];
			i++;
		}
	}
}

// a   b   a   b   c   a   b   c   d   a   b   c   d   e
// -1  0   0   1   2   0   1   2   0   0   1   2   0   0

int KMP(string str, string sub) // KMP算法
{
	int lenStr = str.size(), lenSub = sub.size();
	if (!lenStr || !lenSub)
		return -1;

	vector<int> next;
	GetNext(sub, next);
	vector<int> nextval;
	GetNextval(sub, next, nextval);

	int i = 0, j = 0; // i, j分别记录主串和子串匹配过程中的下标
	while (i < lenStr && j < lenSub)
	{
		if (j == -1 || str[i] == sub[j])
		{
			i++;
			j++;
		}
		else
		{
			j = next[j]; // KMP算法优势：j无需跟BF算法一样回退到初始位置，next数组(或nextval数组)记录了j应该回退到的位置
		}
	}

	if (j >= lenSub) // 当子串遍历完时，说明匹配成功，返回i - j
		return i - j;

	return -1;
	// 以上if判断条件不能写成：
	// if (i >= lenStr) return -1;return i - j;
	// 这样写的话，如果子串正好在主串末尾找到时就返回-1了
}

void testBF()
{
	cout << BruteForce("abcdef", "def") << endl;   // 3
	cout << BruteForce("abcdefgh", "def") << endl; // 3
	cout << BruteForce("abcdefgh", "ab") << endl;  // 0
	cout << BruteForce("abcdefgh", "cdd") << endl; //-1
}
void testKMP()
{
	cout << KMP("abcdefabcddrf", "abc") << endl;  // 0
	cout << KMP("abcdefabcddrf", "abe") << endl;  //-1
	cout << KMP("abcdefabcddrf", "a") << endl;	  // 0
	cout << KMP("abcdefabcddrf", "cdef") << endl; // 2
	cout << KMP("abcdefabcddrf", "dd") << endl;	  // 9
	cout << KMP("abcdefabcddrf", "de") << endl;	  // 3
	cout << KMP("abcdefabcddrf", "drf") << endl;  // 10
	cout << KMP("abc", "abc") << endl;			  // 0
	cout << KMP("", "drf") << endl;				  //-1
	cout << KMP("", "") << endl;				  //-1
}

int main()
{
	testBF();
	testKMP();
	return 0;
}
