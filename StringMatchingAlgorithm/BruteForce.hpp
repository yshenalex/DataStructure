#pragma once
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


