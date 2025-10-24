#pragma once
#include <iostream>
#include <queue>
using namespace std;

template <class K, class V>
struct AVLTreeNode
{
	pair<K, V> _kv;
	int _height;
	AVLTreeNode *_lchild;
	AVLTreeNode *_rchild;

	AVLTreeNode(const pair<K, V> kv)
		: _kv(kv), _height(1), _lchild(nullptr), _rchild(nullptr)
	{
	}
};

template <class K, class V>
class AVLTree
{
	typedef AVLTreeNode<K, V> Node;

public:
	AVLTree()
		: _root(nullptr)
	{
	}

	bool Insert(K &key)
	{
	}

private:
	bool _insert(Node *root, pair<K, V> kv)
	{
		if (!root)
		{
			root = new Node(kv);
			return true;
		}

		if (kv.first < root->_kv.first)
			_Insert(root->_lchild, kv);
		else if (kv.first > root->_kv.first)
			_Insert(root->_rchild, kv);
		else
			return false;
	}
	void _getNewHeight(Node *root)
	{
		if (!root)
			return;
		if (!root->_lchild && !root->_rchild)
			root->_height = root->_lchild->_height > root->_rchild->_height ? root->_lchild->_height + 1 : root->_rchild->_height + 1;
		else if (!root->_lchild || !root->_rchild)
			root->_height = root->_lchild == nullptr ? root->_rchild->_height + 1 : root->_lchild->_height + 1;
	}

	Node *_root;
};
