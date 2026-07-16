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

// 测试6：删除叶子、单孩子、双孩子节点基础场景
void testAVLTree6()
{
    cout << "========== 测试用例6：基础删除(叶子/单孩子/双孩子) ==========\n";
    int arr[] = {10, 5, 18, 3, 7, 15, 20, 2, 4, 6, 8};
    AVLTree<int> avl;
    for (int x : arr) avl.insert(x);

    cout << "【删除前】\n中序：";
    avl.InOrder();
    cout << "\n层序：";
    avl.LevelOrder();
    cout << "平衡：" << boolalpha << avl.isBalance() << "\n";

    // 1. 删除叶子节点 2
    cout << "\n>>> erase(2) 删除叶子节点2\n";
    avl.erase(2);
    cout << "中序："; avl.InOrder(); cout << "\n平衡：" << avl.isBalance() << "\n";

    // 2. 删除只有右孩子的节点3
    cout << "\n>>> erase(3) 删除单孩子节点3\n";
    avl.erase(3);
    cout << "中序："; avl.InOrder(); cout << "\n平衡：" << avl.isBalance() << "\n";

    // 3. 删除有左右双孩子的根10
    cout << "\n>>> erase(10) 删除双孩子根节点10\n";
    avl.erase(10);
    cout << "中序："; avl.InOrder();
    cout << "\n层序："; avl.LevelOrder();
    cout << "平衡：" << avl.isBalance() << "\n\n";
}

// 测试7：删除后触发四种失衡旋转 LL/LR/RR/RL
void testAVLTree7()
{
    cout << "========== 测试用例7：删除触发失衡旋转LL/LR/RR/RL ==========\n";
    // 构造会因删除失衡的树
    int arr[] = {20, 10, 30, 5, 15, 25, 35, 3, 8, 12, 17, 22, 28, 32, 40};
    AVLTree<int> avl;
    for (int x : arr) avl.insert(x);

    cout << "删除前层序："; avl.LevelOrder();
    // 删除右侧节点，左侧过重触发LL
    cout << "\n>>> erase(40)、erase(35) 左子树过重，触发LL旋转\n";
    avl.erase(40);
    avl.erase(35);
    cout << "删除后层序："; avl.LevelOrder();
    cout << "平衡：" << avl.isBalance() << "\n";

    // 重新构造一棵树测试RR
    AVLTree<int> avl2;
    int arr2[] = {10,5,15,3,7,12,18,1,4,6,9,11,13,16,20};
    for(int x:arr2) avl2.insert(x);
    cout << "\n>>> erase(1)、erase(3) 右子树过重，触发RR旋转\n";
    avl2.erase(1);
    avl2.erase(3);
    cout << "层序："; avl2.LevelOrder();
    cout << "平衡：" << avl2.isBalance() << "\n\n";
}

// 测试8：连续删除、删空树、删除不存在元素边界测试
void testAVLTree8()
{
    cout << "========== 测试用例8：边界删除(删空/删不存在值) ==========\n";
    AVLTree<int> avl;
    int arr[] = {6,3,9,2,4,7,10};
    for(int x:arr) avl.insert(x);

    cout << "初始中序："; avl.InOrder();
    cout << "\n初始层序：\n"; avl.LevelOrder();
    // 依次全部删除
    int delList[] = {6,3,9,2,4,7,10};
    for(int x : delList)
    {
        avl.erase(x);
        cout << "\nerase(" << x << ") 后中序：";
        avl.InOrder();
        cout << "\nerase(" << x << ") 后层序：\n";
        avl.LevelOrder();
        cout << " 平衡：" << avl.isBalance();
    }

    // 树已空，删除不存在值
    cout << "\n\n>>> 空树 erase(99)（不存在元素）\n";
    avl.erase(99);
    cout << "执行无异常，树仍为空\n\n";
}

int main()
{
    // 插入测试
    testAVLTree1();
    testAVLTree2();
    testAVLTree3();
    testAVLTree4();
    testAVLTree5();

    // 删除测试
    testAVLTree6();
    testAVLTree7();
    testAVLTree8();

    return 0;
}