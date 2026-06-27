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
		// TODO
	}

	void insert(const T& x)
	{
		_root = _insert(_root, x);
	}

	bool erase(const T& x)
	{
		// TODO
		return true;
	}

	TreeNode* find(const T& x)
	{
		// TODO
		return true;
	}

	void InOrder()
	{
		_InOrder(_root);
	}

	void LevelOrder()
	{
		queue<TreeNode*> q;
		q.push(_root);
		int levelSize = q.size();
		
		while (!q.empty())
		{
			for (int i = 0; i < levelSize; i++)
			{
				TreeNode* node = q.front();
				q.pop();
				cout << node->value << " ";
				
				if (node->lchild)
					q.push(node->lchild);
				if (node->rchild)
					q.push(node->rchild);
			}

			levelSize = q.size();
			cout << endl;
		}
	}

	bool isBalance()
	{
		return _isBalance(_root);
	}



private:
	TreeNode* _insert(TreeNode* root, const T& x)
	{
		// 最开始空树时直接插入
		if (!root)
			return new TreeNode(x);

		if (root->value == x)
			return root; // 什么都不用做
		else if (root->value < x)
			root->rchild = root->rchild == nullptr ? new TreeNode(x) : _insert(root->rchild, x); // 递归找到合适位置插入
		else 
			root->lchild = root->lchild == nullptr ? new TreeNode(x) : _insert(root->lchild, x);
		
		// 更新节点的高度
		_updateHeight(root);

		// 递归回溯时进行平衡修复
		return _rebalance(root);
	}

	/**
	 * @brief 获取某一节点的高度
	 * 
	 */
	int _getHeight(TreeNode* node)
	{	
		// 空节点高度设置为0
		return node == nullptr ? 0 : node->height;
	}

	/**
	 * @brief 更新某一节点的高度 
	 * 
	 */
	void _updateHeight(TreeNode* node)
	{

		int lheight = _getHeight(node->lchild);
		int rheight = _getHeight(node->rchild);
		node->height = lheight > rheight ? lheight + 1 : rheight + 1;
	}

	/**
	 * @brief 以root为根节点的子树平衡修复
	 * 
	 * @param root 子树的旧根节点
	 * @return TreeNode* 子树的新根节点
	 */
	TreeNode* _rebalance(TreeNode* root)
	{	
		if (abs(_getHeight(root->lchild) - _getHeight(root->rchild)) <= 1)
		{
			return root;
		}

		if (_getHeight(root->lchild) - _getHeight(root->rchild) == -2)
		{
			// RR型
			if (_getHeight(root->rchild->lchild) < _getHeight(root->rchild->rchild))
			{
				return _rotateL(root);
			}
			// RL型
			else 
			{
				root->rchild = _rotateR(root->rchild);
				return _rotateL(root);
			}
			// 不会出现 root->rchild->lchild->height == root->rchild->rchild->height 情况

	
		}
		else if (_getHeight(root->lchild) - _getHeight(root->rchild) == 2)
		{
			// LL型
			if (_getHeight(root->lchild->lchild) > _getHeight(root->lchild->rchild))
			{
				return _rotateR(root);
			}
			// LR型
			else 
			{
				root->lchild = _rotateL(root->lchild);
				return _rotateR(root);
			}

		}
	}
	
	/**
	 * @brief 以root为根节点子树左旋
	 * 
	 * @param root 子树的旧根节点
	 * @return TreeNode* 子树的新根节点
	 */
	TreeNode* _rotateL(TreeNode* root)
	{
		if (!root->rchild)
			return root;
		
		TreeNode* newparent = root->rchild;
		root->rchild = newparent->lchild;
		newparent->lchild = root;

		// 更新高度
		_updateHeight(root);
		_updateHeight(newparent);
		
		return newparent;
	}

	/**
	 * @brief 以root为根节点子树右旋
	 * 
	 * @param root 子树的旧根节点
	 * @return TreeNode* 子树的新根节点
	 */
	TreeNode* _rotateR(TreeNode* root)
	{
		if (!root->lchild)
			return root;
		
		TreeNode* newparent = root->lchild;
		root->lchild = newparent->rchild;
		newparent->rchild = root;

		_updateHeight(root);
		_updateHeight(newparent);

		return newparent;
	}

	void _InOrder(TreeNode* root)
	{	
		if (!root)
			return;

		_InOrder(root->lchild);
		cout << root->value << " ";
		_InOrder(root->rchild);

	}

	bool _isBalance(TreeNode* root)
	{
		if (!root)
			return true;
		if (abs(_getHeight(root->lchild) - _getHeight(root->rchild) >= 2))
			return false;

		return _isBalance(root->lchild) && _isBalance(root->rchild); 
	}


private:
	TreeNode *_root;
};
