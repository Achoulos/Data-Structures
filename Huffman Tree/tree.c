/*
* File:    tree.c
*
* Description: This is a program that creates a Huffman Tree using a Binary Min Heap.
*
This is an ADT utilizing a binary tree
*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "tree.h"

typedef struct tree TREE;

struct tree
{
	int data;
	TREE *parent;
	TREE *left;
	TREE *right;
};

void detach(TREE *root) //Sets a parent node's left or right pointers to null if it has a child. O(1). 
{
	if (root->parent==NULL)
		return;
	if(root->parent->left==root)
		root->parent->left = NULL;
	if(root->parent->right==root)
		root->parent->right=NULL;
}

TREE *createTree(int data, TREE *left, TREE *right) //Creates a tree using given data and two child nodes and returns a pointer to the new tree's root. O(1).
{
	TREE *tp;

	tp = (TREE *)malloc(sizeof(TREE));

	assert(tp!=NULL);
	
	tp->data = data;
	tp->left = left;
	tp->right = right;
	tp->parent = NULL;

	if(left!=NULL) //removes other parent pointers to the left node passed into createTree
	{
		detach(left);
		left->parent = tp;
	}
	if(right!=NULL) //removes other parent pointers to the right node passed into createTree
	{
		detach(right); 
		right->parent = tp;
	}

	return tp;

}

void destroyTree(TREE *root) //Traverses a tree in post-order and frees every node. O(n).
{
	assert(root!=NULL);
	if(root->parent==NULL)
		return;
	destroyTree(root->left);
	destroyTree(root->right);
	free(root);
}

int getData(TREE *root) //Returns the integer data in a node. O(1).
{
	assert(root!=NULL);
	return root->data;
}

TREE *getLeft(TREE *root) //Returns a pointer to the left child node of a root. O(1).
{
	assert(root!=NULL);
	return root->left;
}

TREE *getRight(TREE *root) //Returns a pointer to the right child node of a root. O(1).
{
	assert(root!=NULL);
	return root->right;
}

TREE *getParent(TREE *root) //Returns a pointer to the parent of a node. O(1).
{
	assert(root!=NULL);
	return root->parent;
}

void setLeft(TREE *root, TREE *left) //Detaches a root's left node, then replaces it with the left node passed in. O(1).
{
	assert(root!=NULL);
	assert(left!=NULL);

	if(root->left!=NULL)
	{
		detach(root->left);
	}

	root->left = left;
	root->left->parent=root;

}

void setRight(TREE *root, TREE *right) //Detaches a root's right node, then replaces it with the right node passed in. O(1). 
{
	assert(root!=NULL);
	assert(right!=NULL);

	if(root->right!=NULL)
	{	
		detach(root->right);
	}

	root->right = right;
	root->right->parent=root;
}
