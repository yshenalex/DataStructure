#include <utility>
#include <iostream>

enum Color
{
	RED,
	BLACK
};

template <typename T>
struct TreeNode
{
	T value;
	Color color;
	TreeNode *lchild;
	TreeNode *rchild;

	struct TreeNode(const T &x) : value(x), color(Color::RED), lchild(nullptr), rchild(nullptr) {}
};

template <typename T>
class RedBlackTree
{
	using TreeNode = AVLTreeNode<T>;

public:
	RedBlackTree()
		: _root(nullptr)
	{
	}

	~RedBlackTree()
	{
	}

	bool insert(const T &x)
	{
		// TODO
	}

	void erase(const T &x)
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
