#include <iostream>
#include "AVLTree_2.hpp"
using namespace std;

// 测试1：混合LL、LR、RR、RL四种旋转场景
void testAVLTree1()
{
    int arr1[] = {16, 3, 7, 11, 9, 26, 18, 14, 15};
    int sz1 = sizeof(arr1) / sizeof(arr1[0]);
    AVLTree<int> avl1;
    for (int i = 0; i < sz1; ++i)
    {
        avl1.insert(arr1[i]);
    }

    cout << "========== 测试用例1 ==========" << endl;
    cout << "插入序列：";
    for (int x : arr1) cout << x << " ";
    cout << "\n中序遍历：" << endl;
    avl1.InOrder();
    cout << "\n\n层序遍历：" << endl;
    avl1.LevelOrder();
    cout << "是否平衡树：" << boolalpha << avl1.isBalance() << "\n\n";
}

// 测试2：基础有序序列触发RR、RL旋转
void testAVLTree2()
{
    int arr2[] = {4, 2, 6, 1, 3, 5, 15, 7, 16, 14};
    int sz2 = sizeof(arr2) / sizeof(arr2[0]);
    AVLTree<int> avl2;
    for (int i = 0; i < sz2; ++i)
    {
        avl2.insert(arr2[i]);
    }

    cout << "========== 测试用例2 ==========" << endl;
    cout << "插入序列：";
    for (int x : arr2) cout << x << " ";
    cout << "\n中序遍历：" << endl;
    avl2.InOrder();
    cout << "\n\n层序遍历：" << endl;
    avl2.LevelOrder();
    cout << "是否平衡树：" << boolalpha << avl2.isBalance() << "\n\n";
}

// 测试3：纯升序序列（RR旋转）
void testAVLTree3()
{
    int arr3[] = {1,2,3,4,5,6,7};
    int sz3 = sizeof(arr3) / sizeof(arr3[0]);
    AVLTree<int> avl3;
    for (int i = 0; i < sz3; ++i)
    {
        avl3.insert(arr3[i]);
    }

    cout << "========== 测试用例3（升序RR） ==========" << endl;
    cout << "插入序列：";
    for (int x : arr3) cout << x << " ";
    cout << "\n中序遍历：" << endl;
    avl3.InOrder();
    cout << "\n\n层序遍历：" << endl;
    avl3.LevelOrder();
    cout << "是否平衡树：" << boolalpha << avl3.isBalance() << "\n\n";
}

// 测试4：纯降序序列（LL旋转）
void testAVLTree4()
{
    int arr4[] = {7,6,5,4,3,2,1};
    int sz4 = sizeof(arr4) / sizeof(arr4[0]);
    AVLTree<int> avl4;
    for (int i = 0; i < sz4; ++i)
    {
        avl4.insert(arr4[i]);
    }

    cout << "========== 测试用例4（降序LL） ==========" << endl;
    cout << "插入序列：";
    for (int x : arr4) cout << x << " ";
    cout << "\n中序遍历：" << endl;
    avl4.InOrder();
    cout << "\n\n层序遍历：" << endl;
    avl4.LevelOrder();
    cout << "是否平衡树：" << boolalpha << avl4.isBalance() << "\n\n";
}

// 测试5：插入重复值，验证去重逻辑
void testAVLTree5()
{
    int arr5[] = {10, 5, 15, 5, 10, 20, 15};
    int sz5 = sizeof(arr5) / sizeof(arr5[0]);
    AVLTree<int> avl5;
    for (int i = 0; i < sz5; ++i)
    {
        avl5.insert(arr5[i]);
    }

    cout << "========== 测试用例5（含重复值） ==========" << endl;
    cout << "插入序列：";
    for (int x : arr5) cout << x << " ";
    cout << "\n中序遍历（无重复）：" << endl;
    avl5.InOrder();
    cout << "\n\n层序遍历：" << endl;
    avl5.LevelOrder();
    cout << "是否平衡树：" << boolalpha << avl5.isBalance() << "\n\n";
}

int main()
{
    testAVLTree1();
    testAVLTree2();
    testAVLTree3();
    testAVLTree4();
    testAVLTree5();
    return 0;
}