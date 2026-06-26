#pragma once
#include <stdlib.h>
#include <iostream>
#include <queue>
using namespace std;


/**
 * @brief 二叉链表实现AVL树 
 * 
 * @tparam T 元素数据类型
 */
template <class T>
struct AVLTreeNode
{
	T value; // 节点数值
	int height; // 节点高度
	AVLTreeNode *lchild;
	AVLTreeNode *rchild;

	AVLTreeNode(const T& x) : value(x), height(1), lchild(nullptr), rchild(nullptr) {}
};

template <class T>
class AVLTree
{
	using TreeNode =  AVLTreeNode<T>;
public:
	AVLTree()
		: _root(nullptr)
	{
	}

	~AVLTree()
	{

	}

	bool insert(const T& x)
	{

	}

	bool erase(const T& x)
	{

	}

	TreeNode* find(const T& x)
	{

	}


private:
	TreeNode* _insert(TreeNode* root, const T& x)
	{
		if (root->value == x)
			return root; // 什么都不用做
		else if (root->value < x)
			root->rchild = root->rchild == nullptr ? new TreeNode(x) : _insert(root->rchild, x); // 递归找到合适位置插入
		else 
			root->lchild = root->lchild == nullptr ? new TreeNode(x) : _insert(root->lchild, x);
		
		// 更新节点的高度
		_updateHeight(root);

		// 平衡修复


	}

	void _updateHeight(TreeNode* root)
	{
		if (root->lchild && root->rchild)
			root->height = root->lchild->height > root->rchild->height ? root->lchild->height + 1 : root->rchild->height + 1;
		else if (!root->lchild && root->rchild)
			root->height = root->rchild->height + 1;
		else if (root->lchild && !root->rchild)
			root->height = root->lchild->height + 1;
		// 左右子树都为空的情况什么都不用做，因为一个节点的height默认就是1
	}

	TreeNode* _rebalance(TreeNode* root)
	{
		if (abs(root->lchild->height - root->rchild->height) <= 1)
		{
			return root;
		}
		if (root->lchild->height - root->rchild->height == -2)
		{
			
		}
		else if (root->lchild->height - root->rchild->height == 2)
		{

		}
	}


private:
	TreeNode *_root;
};
