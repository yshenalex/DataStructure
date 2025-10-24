#include <iostream>
#include "AVLTree.hpp"
using namespace std;

void testAVLTree1()
{
	int a1[] = {16, 3, 7, 11, 9, 26, 18, 14, 15};

	AVLTree<int, int> avt1;
	for (int i = 0; i < sizeof(a1) / sizeof(a1[0]); i++)
	{
		avt1.Insert(make_pair(a1[i], a1[i]));
	}
	cout << "---------avt1----------" << endl;
	cout << "中序遍历：" << endl;
	avt1.InOrder();
	cout << endl;
	cout << "层序遍历：" << endl;
	avt1.LevelOrder();
	cout << endl;
	cout << "是否是平衡树：";
	cout << avt1.isBalanceTree() << endl;

	int a2[] = {4, 2, 6, 1, 3, 5, 15, 7, 16, 14};

	AVLTree<int, int> avt2;
	for (int i = 0; i < sizeof(a2) / sizeof(a2[0]); i++)
	{
		avt2.Insert(make_pair(a2[i], a2[i]));
	}
	cout << "---------avt1----------" << endl;
	cout << "中序遍历：" << endl;
	avt2.InOrder();
	cout << endl;
	cout << "层序遍历：" << endl;
	avt2.LevelOrder();
	cout << endl;
	cout << "是否是平衡树：";
	cout << avt2.isBalanceTree() << endl;
}
int main()
{
	testAVLTree1();
	return 0;
}