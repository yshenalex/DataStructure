#include"BinaryTree.h"
#include"Queue.h"

void PreOrder(TreeNode* root)
{
	if (root == NULL)
	{
		printf("NULL ");
		return;
	}

	printf("%d ", root->data);
	PreOrder(root->left);
	PreOrder(root->right);
}

void InOrder(TreeNode* root)
{
	if (root == NULL)
	{
		printf("NULL ");
		return;
	}

	InOrder(root->left);
	printf("%d ", root->data);
	InOrder(root->right);
}


void PostOrder(TreeNode* root)
{
	if (root == NULL)
	{
		printf("NULL ");
		return;
	}

	PostOrder(root->left);
	PostOrder(root->right);
	printf("%d ", root->data);
}

int TreeSize(TreeNode* root)
{
	return root == NULL ? 0 : TreeSize(root->left) + TreeSize(root->right) + 1;
}

int TreeHeight(TreeNode* root)
{
	if (root == NULL)
		return 0;

	int leftHeight = TreeHeight(root->left);
	int rightHeight = TreeHeight(root->right);

	return leftHeight > rightHeight ? leftHeight + 1 : rightHeight + 1;
}

int TreeLeafSize(TreeNode* root)
{
	if (root == NULL)
		return 0;

	if (root->left == NULL && root->right == NULL)
	{
		return 1;
	}

	return TreeLeafSize(root->left) + TreeLeafSize(root->right);
}


void LevelOrder(TreeNode* root)//层序遍历
{
	if (!root)
		return;

	//利用队列先进先出的性质实现层序遍历
	Queue q;
	QueueInit(&q);

	QueuePush(&q, root);//根节点入队列

	while (!QueueEmpty(&q))//只要队列不为空就循环继续
	{
		TreeNode* front = QueueFront(&q);
		QueuePop(&q);//出队头

		printf("%d ", front->data);

		//出完队头，就把该节点的左右子树节点入队尾
		if (front->left)
			QueuePush(&q, front->left);
		if (front->right)
			QueuePush(&q, front->right);
	}
	
	QueueDestroy(&q);
	printf("\n");
}



int BinaryTreeLevelKSize(TreeNode* root, int k)
{
	if (!root)
		return 0;

	if (k == 1)
		return 1;

	//分治：第k层的节点个数 = 其左右子树的k-1层节点个数之和
	return BinaryTreeLevelKSize(root->left, k - 1) + BinaryTreeLevelKSize(root->right, k - 1);
}

TreeNode* BinaryTreeFind(TreeNode* root, BTDataType x)//二叉树查找值为x的节点
{
	if (!root)
		return NULL;

	if (root->data == x)
		return root;

	//左右子树继续找
	TreeNode* node = BinaryTreeFind(root->left, x);
	if (node)
		return node;
	node = BinaryTreeFind(root->right, x);
	if (node)
		return node;

	return NULL;
}

TreeNode* BinaryTreeCreate(char* a, int* pi)//利用前序遍历的数组生成二叉树
{
	if (a[*pi] == '#')
	{
		(*pi)++;
		return NULL;
	}
	else
	{
		TreeNode* root = (TreeNode*)malloc(sizeof(TreeNode));
		if (!root)
		{
			perror("BinaryTreeCreate::");
			exit(-1);
		}
		root->data = a[*pi];
		(*pi)++;

		root->left = BinaryTreeCreate(a, pi);
		root->right = BinaryTreeCreate(a, pi);

		return root;
	}
}

void BinaryTreeDestory(TreeNode** proot)
{
	if (!*proot)
		return;

	//一定是后序遍历销毁，否则可能找不到原来的左右子树
	BinaryTreeDestory((*proot)->left);
	BinaryTreeDestory((*proot)->right);

	free(*proot);
	*proot = NULL;
}


bool BinaryTreeComplete(TreeNode* root)//判断二叉树是否是完全二叉树
{
	//思路：完全二叉树层序遍历的结果中非空和空节点彼此分离，不会混在一起

	if (!root)//空节点我们认为是完全二叉树
		return true;

	Queue q;//层序遍历：利用队列性质
	QueueInit(&q);
	QueuePush(&q, root);

	while (!QueueEmpty(&q))
	{
		TreeNode* front = QueueFront(&q);
		QueuePop(&q);

		if (!front)//一旦有空节点出，就退出循环
			break;

		//空节点也入队列
		QueuePush(&q, front->left);
		QueuePush(&q, front->right);
	}

	while (!QueueEmpty(&q))//判断持续出空节点的时候，中间是否掺杂非空节点
	{
		TreeNode* front = QueueFront(&q);
		QueuePop(&q);

		if (front)//掺杂非空节点，肯定不是完全二叉树
		{
			QueueDestroy(&q);
			return false;
		}
	}

	QueueDestroy(&q);
	return true;
}