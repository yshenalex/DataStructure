#pragma once
#include <utility>
#include <iostream>
#include <queue>
using std::queue;
using std::cout;
using std::pair;

template <class K, class V>
struct AVLTreeNode
{
	pair<K, V> _kv;
	AVLTreeNode *_left;
	AVLTreeNode *_right;
	AVLTreeNode *_parent;

	int _bf; // 平衡因子：右子树高度-左子树高度 -> 非必需，但这样方便控制平衡

	AVLTreeNode(const pair<K, V> &kv)
		: _kv(kv), _left(nullptr), _right(nullptr), _parent(nullptr), _bf(0)
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

	bool Insert(const pair<K, V> &kv)
	{
		if (!_root)
		{
			_root = new Node(kv);
			_root->_bf = 0;
			return true;
		}

		// 1. 先按照二叉搜索树的规则将节点插入到AVL树中
		Node *parent = nullptr;
		Node *cur = _root;
		while (cur)
		{
			if (kv.first < cur->_kv.first)
			{
				parent = cur;
				cur = cur->_left;
			}
			else if (kv.first > cur->_kv.first)
			{
				parent = cur;
				cur = cur->_right;
			}
			else
			{
				return false;
			}
		}

		cur = new Node(kv);
		if (kv.first > parent->_kv.first)
			parent->_right = cur;
		else
			parent->_left = cur;
		cur->_parent = parent;

		// 2.更新平衡因子
		while (parent)
		{
			if (cur == parent->_left)
				parent->_bf--; // 如果节点插入到parent的左侧，则需要给parent的平衡因子-1
			else
				parent->_bf++; // 如果节点插入到parent的右侧，则需要给parent的平衡因子+1

			// 此时：parent的平衡因子可能有五种情况：0，+-1， +-2

			if (parent->_bf == 0)
			// 如果插入后parent的平衡因子为0，说明插入之前parent的平衡因子为正负1，
			// 插入后被调整成0，相当于把短的那一侧补了一个节点，整体高度不变，不需要往上继续调整，直接break
			{
				break;
			}
			else if (parent->_bf == 1 || parent->_bf == -1)
			// 如果插入后parent的平衡因子为正负1，说明插入前parent的平衡因子一定为0，插入后被更新成正负1,
			// 此时以parent为根的树的高度增加，需要继续向上更新
			{
				cur = cur->_parent;
				parent = parent->_parent;
			}
			else if (parent->_bf == 2 || parent->_bf == -2) // 如果插入后parent平衡因子为正负2，则不是平衡树，需要旋转调整
			{
				// 变化是直线的时候，只要进行单旋即可：
				if (parent->_bf == 2 && cur->_bf == 1)
					_RotateL(parent);
				else if (parent->_bf == -2 && cur->_bf == -1)
					_RotateR(parent);
				// 变化是折线的时候需要两次单旋：
				else if (parent->_bf == 2 && cur->_bf == -1)
					_RotateRL(parent);
				else // 即parent->_bf == -2 && cur->_bf == 1
					_RotateLR(parent);

				break;
			}
		}
	}

	void InOrder()
	{
		_InOrder(_root);
	}

	void LevelOrder()
	{
		queue<Node *> q;
		int levelSize = 1;
		q.push(_root);

		while (!q.empty())
		{
			for (int i = 0; i < levelSize; i++)
			{

				Node *front = q.front();
				q.pop();

				if (front->_left)
					q.push(front->_left);
				if (front->_right)
					q.push(front->_right);

				cout << front->_kv.first << ":" << front->_kv.second << " ";
			}
			cout << endl;

			levelSize = q.size();
		}
	}

	bool isBalanceTree()
	{
		return _isBalanceTree(_root);
	}

private:
	void _RotateL(Node *parent)
	{
		// 左单旋：把subR的左(即subRL)给到parent的右，再把parent给到subR的左
		// 注意：记得要更新subRL、parent和subR三者新的_parent
		Node *subR = parent->_right;
		Node *subRL = subR->_left;

		parent->_right = subRL;
		if (subRL) // 可能为空，非空就更新它的_parent
			subRL->_parent = parent;

		Node *ppNode = parent->_parent; // 保存parent的_parent,因为要让它与subR关联起来
		subR->_parent = ppNode;			// 先让subR的_parent指向原来parent的_parent

		subR->_left = parent;
		parent->_parent = subR;

		if (parent == _root) // 如果原来要进行左旋调整的parent是根，就意味parent->_parent==nullptr，那么直接让subR作根
			_root = subR;
		else if (ppNode->_left == parent)
			ppNode->_left = subR;
		else // 即ppNode->right == parent
			ppNode->_right = subR;

		parent->_bf = subR->_bf = 0; // 左旋完更新平衡因子
	}

	void _RotateR(Node *parent)
	{
		Node *subL = parent->_left;
		Node *subLR = subL->_right;

		parent->_left = subLR;
		if (subLR)
			subLR->_parent = parent;

		Node *ppNode = parent->_parent;
		subL->_parent = ppNode;

		subL->_right = parent;
		parent->_parent = subL;

		if (parent == _root)
			_root = subL;
		else if (ppNode->_left == parent)
			ppNode->_left = subL;
		else
			ppNode->_right = subL;

		parent->_bf = subL->_bf = 0;
	}

	void _RotateRL(Node *parent)
	{
		Node *subR = parent->_right;
		Node *subRL = subR->_left;
		int bf = subRL->_bf;

		_RotateR(subR);
		_RotateL(parent);

		if (bf == 0)
		// 【特殊情况】有可能新加的节点就是subRL(也就说原来两个节点，加上新增的共三个节点)，
		// 此时它的_bf为空，右左双旋后，三个节点的平衡因子应该都是0
		{
			parent->_bf = 0;
			subR->_bf = 0;
			subRL->_bf = 0;
		}
		else if (bf == -1) // 插入到了subRL的左子树上，调整完后，subR的左链接到subRL的更矮的右子树，subR平衡因子为1，具体看图
		{
			parent->_bf = 0;
			subR->_bf = 1;
			subRL->_bf = 0;
		}
		else // 即bf == 1
		// 插入到了subRL的右子树上，调整完后，parent的右链接到subRL的更矮的左子树，parent平衡因子为-1，具体看图
		{
			parent->_bf = -1;
			subR->_bf = 0;
			subRL->_bf = 0;
		}
	}

	void _RotateLR(Node *parent)
	{
		Node *subL = parent->_left;
		Node *subLR = subL->_right;
		int bf = subLR->_bf;

		_RotateL(subL);
		_RotateR(parent);

		if (bf == 0)
		{
			parent->_bf = 0;
			subL->_bf = 0;
			subLR->_bf = 0;
		}
		else if (bf == -1)
		{
			parent->_bf = 1;
			subL->_bf = 0;
			subLR->_bf = 0;
		}
		else // 即bf == 1
		{
			parent->_bf = 0;
			subL->_bf = -1;
			subLR->_bf = 0;
		}
	}

	void _InOrder(Node *_root)
	{
		if (!_root)
			return;

		_InOrder(_root->_left);
		cout << _root->_kv.first << ":" << _root->_kv.second << " ";
		_InOrder(_root->_right);
	}

	int _Height(Node *root)
	{
		if (!root)
			return 0;

		int leftHeight = _Height(root->_left);
		int rightHeight = _Height(root->_right);

		return leftHeight > rightHeight ? leftHeight + 1 : rightHeight + 1;
	}

	bool _isBalanceTree(Node *root)
	{
		if (!root)
			return true;

		int leftHeight = _Height(_root->_left);
		int rightHeight = _Height(_root->_right);
		int diff = rightHeight - leftHeight;

		if (abs(diff) >= 2) // 所有子树的左右子树高度差都不超过1，就是平衡树
			return false;

		return _isBalanceTree(root->_left) && _isBalanceTree(root->_right);
	}

	Node *_root;
};