#include "BloomFilter.hpp"
#include <string>
#include <iostream>
using namespace mystl;
using namespace std;
int main()
{
    // 准备往布隆过滤器插入4个左右的数据
    BloomFilter<4> filter;

    // 插入一些元素
    filter.insert("apple");
    filter.insert("banana");
    filter.insert("cherry");
    filter.insert("date");

    // 测试存在的元素
    cout << "Contains 'apple'? " << (filter.contains("apple") ? "Yes" : "No") << endl;
    cout << "Contains 'banana'? " << (filter.contains("banana") ? "Yes" : "No") << endl;

    // 测试不存在的元素
    cout << "Contains 'grape'? " << (filter.contains("grape") ? "Yes" : "No") << endl;
    cout << "Contains 'orange'? " << (filter.contains("orange") ? "Yes" : "No") << endl;

    // 清空过滤器
    filter.clear();
    cout << "After clear, contains 'apple'? " << (filter.contains("apple") ? "Yes" : "No") << endl;

	return 0;
}