#include <utility>
#include <iostream>
using namespace std;
enum Color
{
	RED,
	BLACK,
	RED_BLACK,
	BLACK_BLACK
};

template <typename K, typename V>
struct TreeNode
{
	TreeNode *left;
	TreeNode *right;
	TreeNode *parent;
	Color color;
	pair<K, V> kv;

	struct TreeNode(const pair<K, V> &kv)
		: kv(kv), left(nullptr), right(nullptr), parent(nullptr), color(Color::RED)
	{
	}

	struct TreeNode()
	{
	}
};

template <typename K, typename V>
class RedBlackTree
{
	typedef TreeNode<K, V> TreeNode;

public:
	RedBlackTree() : _root(nullptr)
	{
	}

	~RedBlackTree()
	{
	}

	bool insert(const std::pair<K, V> &kv)
	{
		// 情况1：被插入节点是根节点
		if (!_root)
		{
			_root = new TreeNode(kv);
			_root->color = Color::BLACK; // 根节点直接染成黑色
			return true;
		}

		TreeNode *newnode = new TreeNode(kv);
		TreeNode *parent = nullptr, *cur = _root;
		while (cur)
		{
			parent = cur;
			if (kv.first > cur->kv.first)
				cur = cur->right;
			else if (kv.first < cur->kv.first)
				cur = cur->left;
			else
				return false; // 不可重复插入，直接返回插入失败
		}

		newnode->parent = parent; // 代码执行到这里说明newnode结点应该插入的位置已经找到，其双亲节点已经确定，只是不清楚应该是在左右哪个孩子位置插入
		if (kv.first < parent->kv.first)
			parent->left = newnode;
		else if (kv.first > parent->kv.first)
			parent->right = newnode;

		// 情况2：被插入的节点的双亲节点是黑色，此时什么都不用做
		if (parent->color == Color::BLACK)
			return true;
		// 情况3：被插入节点的双亲节点是红色，此时要分三种情况（实际是六种，左右对称）讨论
		else 
		{

		}
		
	}

	void erase(const std::pair<K, V> &kv)
	{
		// TODO
	}

	void InOrder()
	{
		// TODO
	}

private:
	TreeNode *_root;
};
