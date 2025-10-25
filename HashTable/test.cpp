#include "HashTable.hpp"

#include <string>
#include <iostream>
using namespace std;
using namespace OpenAddressing;

void test1()
{
	HashTable<int> ht;

	// 插入测试
	ht.insert(10);
	ht.insert(20);
	ht.insert(30);
	ht.insert(40);
	ht.insert(50);
	ht.insert(60);
	ht.insert(70);
	ht.insert(80);
	ht.insert(90);
	ht.insert(100);
	ht.insert(110); // 这将触发扩容

	// 打印当前哈希表内容
	ht.Print();

	// 查找测试
	cout << "Find 30: " << (ht.find(30) != -1 ? "Found" : "Not Found") << endl;
	cout << "Find 45: " << (ht.find(45) != -1 ? "Found" : "Not Found") << endl;

	// 删除测试
	ht.erase(30);
	ht.erase(50);
	cout << "After erasing 30 and 50:" << endl;
	ht.Print();

	// 再次查找已删除元素
	cout << "Find 30 after erase: " << (ht.find(30) != -1 ? "Found" : "Not Found") << endl;
}

void test2()
{
	HashTable<int> ht;

	// 插入重复元素
	for (int i = 0; i < 5; i++)
	{
		ht.insert(5);
		ht.insert(10);
		ht.insert(15);
	}

	// 插入足够多的元素触发多次扩容
	for (int i = 0; i < 100; i++)
	{
		ht.insert(i);
	}

	ht.Print();
	cout << "Total elements (should be 100): " << ht.size() << endl;
}

void test3()
{
	HashTable<int> ht;

	// 插入一组数据
	for (int i = 1; i <= 20; i++)
	{
		ht.insert(i);
	}

	// 删除部分数据
	for (int i = 1; i <= 10; i++)
	{
		ht.erase(i);
	}

	// 重新插入已删除的数据
	for (int i = 1; i <= 10; i++)
	{
		ht.insert(i);
	}
	cout << ht.find(2) << endl;

	ht.Print();
}
void test4()
{

	HashTable<string> ht;

	ht.insert("apple");
	ht.insert("banana");
	ht.insert("cherry");
	ht.insert("date");
	ht.insert("elderberry");
	ht.insert("fig");
	ht.insert("grape");
	// ht.insert("kiwi");

	ht.Print();

	cout << "Find 'banana': " << (ht.find("banana") != -1 ? "Found" : "Not Found") << endl;
	cout << "Find 'kiwi': " << (ht.find("kiwi") != -1 ? "Found" : "Not Found") << endl;

	ht.erase("banana");
	cout << "After erasing 'banana':" << endl;
	ht.Print();
}
int main()
{
	// test1();
	// test2();
	// test3();
	test4();

	return 0;
}