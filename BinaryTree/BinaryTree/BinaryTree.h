#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

typedef int BTDataType;

typedef struct TreeNode
{
	BTDataType data;
	struct TreeNode* left;
	struct TreeNode* right;

}TreeNode;


void PreOrder(TreeNode* root);//前序遍历
void InOrder(TreeNode* root);//中序遍历
void PostOrder(TreeNode* root);//后序遍历

int TreeSize(TreeNode* root);//二叉树节点个数
int TreeHeight(TreeNode* root);//二叉树深度(高度)
int TreeLeafSize(TreeNode* root);//二叉树叶子节点个数

void LevelOrder(TreeNode* root);//层序遍历
int BinaryTreeLevelKSize(TreeNode* root, int k);//二叉树第k层节点个数
TreeNode* BinaryTreeFind(TreeNode* root, BTDataType x);//二叉树查找值为x的节点


TreeNode* BinaryTreeCreate(char* a, int* pi);//通过前序遍历的数组"ABD##E#H##CF##G##"构建二叉树
void BinaryTreeDestory(TreeNode** root);//二叉树销毁


bool BinaryTreeComplete(TreeNode* root);//判断二叉树是否是完全二叉树













