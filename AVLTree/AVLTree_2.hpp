#pragma once
#include <stdlib.h>
#include <iostream>
#include <queue>
using std::queue;
using std::cout;

/**
 * @brief AVL树节点
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

/**
 * @brief 二叉链表实现AVL树 
 * 
 * @tparam T 元素数据类型
 */
template <class T>
class AVLTree
{
	/**
	 * @brief AVL树节点类型(AVLTreeNode<T>)的别名
	 * 
	 */
	using TreeNode =  AVLTreeNode<T>;
public:
	AVLTree()
		: _root(nullptr)
	{
	}

	~AVLTree()
	{
		_destroy(_root);
		_root = nullptr;
	}

	/**
	 * @brief 插入操作
	 * 
	 * @param x 待插入的元素
	 */
	void insert(const T& x)
	{
		_root = _insert(_root, x);
	}

	/**
	 * @brief 删除操作
	 * 
	 * @param x 待删除的元素
	 * @return true 删除成功
	 * @return false 删除失败
	 */
	bool erase(const T& x)
	{
		// TODO
		return true;
	}

	/**
	 * @brief 寻找数值为x的节点
	 * 
	 * @param x 
	 * @return TreeNode* 指向节点的指针
	 */
	TreeNode* find(const T& x)
	{
		// TODO
		return true;
	}

	/**
	 * @brief 中序遍历
	 * 
	 */
	void InOrder()
	{
		_InOrder(_root);
	}

	/**
	 * @brief 层序遍历
	 * 
	 */
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

			levelSize = q.size(); // 控制每层输出
			cout << "\n";
		}
	}

	/**
	 * @brief 判断该树是否平衡
	 * 
	 * @return true 
	 * @return false 
	 */
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
		// 已经平衡，无需操作
		if (abs(_getHeight(root->lchild) - _getHeight(root->rchild)) <= 1)
		{
			return root;
		}

		// 以root为根的子树不平衡，开始修复平衡操作
		if (_getHeight(root->lchild) - _getHeight(root->rchild) == -2)
		{
			// RR型
			if (_getHeight(root->rchild->lchild) < _getHeight(root->rchild->rchild))
			{
				return _rotateL(root);
			}
			// RL型
			else // _getHeight(root->rchild->lchild) > _getHeight(root->rchild->rchild)
			{
				root->rchild = _rotateR(root->rchild);
				return _rotateL(root);
			}
			// 不会出现 _getHeight(root->rchild->lchild) == _getHeight(root->rchild->rchild) 情况

	
		}
		else // _getHeight(root->lchild) - _getHeight(root->rchild) == 2
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
		// 不会出现其他情况
		
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

	/**
	 * @brief 判断以root为根的子树是否平衡
	 * 
	 * @param root 
	 * @return true 
	 * @return false 
	 */
	bool _isBalance(TreeNode* root)
	{
		if (!root)
			return true;
		if (abs(_getHeight(root->lchild) - _getHeight(root->rchild) >= 2))
			return false;

		return _isBalance(root->lchild) && _isBalance(root->rchild); 
	}


	/**
	 * @brief 递归销毁以root为根节点子树
	 * 
	 * @param root
	 */
	void _destroy(TreeNode* root) 
	{
		if (!root)
			return;
		// 先释放左右子树的内存
		_destroy(root->lchild);
		_destroy(root->rchild);
		
		// 最后释放当前节点内存
		delete root;
		// 释放完置空(因为只是形参，其实置不置空无所谓)
		root = nullptr;
	}


private:
	/**
	 * @brief AVL树的根节点
	 * 
	 */
	TreeNode *_root; 
};
