#include "BinaryTree.h"

TreeNode *BuyNode(BTDataType x)
{
	TreeNode *node = (TreeNode *)malloc(sizeof(TreeNode));
	if (node == NULL)
	{
		perror("malloc fail");
		return NULL;
	}

	node->data = x;
	node->left = NULL;
	node->right = NULL;

	return node;
}

TreeNode *CreatTree()
{
	TreeNode *node1 = BuyNode(1);
	TreeNode *node2 = BuyNode(2);
	TreeNode *node3 = BuyNode(3);
	TreeNode *node4 = BuyNode(4);
	TreeNode *node5 = BuyNode(5);
	TreeNode *node6 = BuyNode(6);
	TreeNode *node7 = BuyNode(7);

	node1->left = node2;
	node1->right = node3;
	node2->left = node4;
	node2->right = node5;
	node3->left = node6;
	node3->right = node7;

	return node1;
}
void test1()
{
	TreeNode *node = CreatTree();

	printf("PreOrder:\n");
	PreOrder(node);
	printf("\nInOrder:\n");
	InOrder(node);
	printf("\nPostOrder:\n");
	PostOrder(node);
	printf("\n");

	printf("TreeHeight：%d\n", TreeHeight(node));
	printf("TreeSize：%d\n", TreeSize(node));
	printf("TreeLeafSize：%d\n", TreeLeafSize(node));
	LevelOrder(node);
	printf("BinaryTreeComplete：%d\n", BinaryTreeComplete(node));
	printf("BinaryTreeLevelKSize：%d\n", BinaryTreeLevelKSize(node, 2));
	printf("BinaryTreeFind：%p\n", BinaryTreeFind(node, 3));

	char a[] = "ABD##E#H##CF##G##";
	int pi = 0;
	TreeNode *newroot = BinaryTreeCreate(a, &pi);
	PreOrder(newroot);
	printf("\n");
}

int main()
{
	test1();
	return 0;
}
