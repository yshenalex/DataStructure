#include <utility>
#include <iostream>
using namespace std;
enum Color
{
	RED,
	BLACK
};

template<typename K, typename V>
struct TreeNode
{
	TreeNode* left;
	TreeNode* right;
	TreeNode* parent;
	Color color;
	pair<K, V> kv;

	struct TreeNode(const pair<K, V>& kv)
		:kv(kv)
		, left(nullptr)
		, right(nullptr)
		, parent(nullptr)
		, color(Color::RED)
	{

	}

	struct TreeNode()
	{

	}
};


template<typename K, typename V>
class RedBlackTree
{
	typedef TreeNode<K, V> TreeNode;
public:
	RedBlackTree() :_root(nullptr)
	{

	}

	~RedBlackTree()
	{

	}


	void insert(const std::pair<K, V>& kv)
	{
		if (!_root)
		{
			_root = new TreeNode(kv);
			_root->color = Color::BLACK;
			return;
		}

		TreeNode* newNode = new TreeNode(kv);
		TreeNode* parent = nullptr;
		TreeNode* cur = _root;
		while (cur)
		{
			if (kv.first > cur->kv.first)
			{
				parent = cur;
				cur = cur->right;
			}
			else if (kv.first < cur->kv.first)
			{
				parent = cur;
				cur = cur->left;
			}
			else
			{
				cur->kv = kv;
				break;
			}
		}

		if (kv.first > parent->kv.first)
		{
			parent->right = newNode;
			newNode->parent = parent;
		}
		else if (kv.first < parent->kv.first)
		{
			parent->left = newNode;
			newNode->parent = parent;
		}


		if (parent->color == Color::BLACK)
			return;

		while ()
		{
			TreeNode* grand = parent->parent;
			if (parent == grand->left)
			{
				TreeNode* uncle = grand->right;

			}
		}

	}

	void InOrder()
	{

	}



private:
	TreeNode* _root;
};












