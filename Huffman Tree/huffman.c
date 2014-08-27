/*
 * File:    huffman.c
 *
 * Description: This is a program that creates a Huffman Tree using a Binary Min Heap.
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <ctype.h>
#include <math.h>
#include "tree.h"

//Global Variables

struct tree *leaves[257]; //Global array of the leaves of the Huffman tree. Stores the tree as well as the ASCII value of each leaf.

struct tree *heap[257]; //Global Binary Min Heap.

int heapcounter;

//Function Declarations

int findLeaf(struct tree *leaf);

int findLeafInHeap(struct tree *leaf);

void printBitString(void);

void insertTree(struct tree *root);

void heapBalanceDown(struct tree *root);

void heapBalanceUp(struct tree *newLeaf);

struct tree *getMin(void);

int
main(int argc, char*argv[]) 
{
	FILE *fp;
	int i = 0;
	int j = 0;
	int z = 0;
	int k = 0;
	int d = 0;
	int b = 0;
	int q =0;
	int c;
	int combinedvalue;
	heapcounter = 0;

	struct tree *end;

	end = createTree(0, NULL, NULL); //creates a tree for the EOF marker.

	struct tree *min1;
	struct tree *min2;
	struct tree *huffman;

	int counts[256]; //initialize the count array to all 0s.
		for(z=0; z<256; z++)
			counts[z]=0;

	for(j=0; j<257; j++) //initialize the leaves array to null.
		leaves[j]=NULL;

	fp = fopen(argv[1], "r"); 

	assert(fp!=NULL);

	while((c=getc(fp))!=EOF) //add characters by index to count array and increases their count.
		counts[c]++;

	for(k=0; k<256; k++) //creates array of tree leaves with characters with counts greater than 0.
	{
		if(counts[k]>0)
			leaves[k]=(createTree(counts[k], NULL, NULL));
	}
	
	leaves[256] = end; //adds EOF tree to the end of the leaves array.

	for(d=0; d<257; d++) //inserts each leaf that isn't null into the binary min heap.
	{
		if(leaves[d]!=NULL)
		{
			insertTree(leaves[d]);
		}
	}

	while(1) //creates the huffman tree by continuously grabbing two minimum values from the heap and creating a parentnode with minimum nodes as children.
	{
		min1 = getMin();
		min2 = getMin();

		if(min1==min2)
		{
			break;
		}
		
		combinedvalue = (getData(min1))+(getData(min2)); //combines the value of the minimum nodes for the huffman tree.
		huffman = createTree(combinedvalue, min1, min2);

		insertTree(huffman);

	}

	printBitString();

	fclose(fp);
	fclose(dp);

}

int leftChild(int i) //returns the array index position of the left child node in a heap.
{
	return( 2*i+1);
}

int rightChild(int i) //returns the array index position of the right child node in a heap.
{
	return (2*i+2);
}

struct tree *getMin(void) //Returns the minimum value node from a binary min heap and removes said minimum node from the heap.
{
	int i=0;
	struct tree *minnode = NULL;
	int child;
	int x;

	minnode = heap[0];
	x=heapcounter-1;
	heapcounter--;

	
	while(leftChild(i)<heapcounter) //loop to reheap from the root of the heap. Runs as long as the left child is within the heap.
	{
		child = leftChild(i); //assumes the left child node of the root is going to be smaller than the root.
		if(((rightChild(i)<heapcounter)&&(getData(heap[leftChild(i)])>(getData(heap[rightChild(i)]))))) //Checks that the right child node is within the heap, then compares the data of the left and right child nodes.
			child = rightChild(i);
		if(getData(heap[x])>getData(heap[child])) //checks if the data in the new root is larger than it's smallest child. 
		{
			heap[i]=heap[child];
			i = child;
		}
		else
			break;
	}
	heap[i]=heap[x];
	return minnode;
}

void insertTree(struct tree *root) //inserts a tree into the last position of the heap
{
	heap[heapcounter]=root;
	if(heapcounter>0)
	{
		heapBalanceUp(root);
	}
	heapcounter++;
	return;		
}

void heapBalanceUp(struct tree *newLeaf) //recursively balances the tree from the leaves.
{
	int parent;
	int child;

	parent = (findLeafInHeap(newLeaf)-1)/2;
	child = findLeafInHeap(newLeaf);

	if(findLeafInHeap(newLeaf)==0) //if the newLeaf is the root of the heap
	{
		return;
	}
	if(getData(newLeaf) < getData(heap[((findLeafInHeap(newLeaf)-1)/2)])) //checks if newLeaf is smaller than it's parent. If it is, the trees are swapped within the heap.
	{
		struct tree *temp;
		
		temp = heap[parent];

		heap[parent] = heap[child];

		heap[child] = temp;

		heapBalanceUp(heap[parent]);
	}
	return;
}


int findLeafInHeap(struct tree *leaf) //returns the array index of a leaf node in the heap.
{
	int i=0;
	for(i=0; i<257; i++)
	{
		if(leaf==heap[i])
		return i;
	}
	return -1;

}

int findLeaf(struct tree *leaf) //returns the array index of a leaf node in the array of leaves.
{
	int i=0;
	for(i=0; i<257; i++)
	{
		if(leaf==leaves[i])
		return i;
	}
	return -1;

}

void printBits(struct tree *leaf) //recursively prints the bitstring of a given leaf by traversing up the tree, then printing on the way back down to the leaf.
{
	if(getParent(leaf)==NULL)
	{
		return;
	}

	printBits(getParent(leaf));
	if((getLeft(getParent(leaf)))==leaf) //checks if it leaf is the left or right child of a parent node.
	{
		printf("0");
		return;
	}
	else if((getRight(getParent(leaf)))==leaf)
	{
		printf("1");
		return;
	}
	else
		return;

}

void printBitString(void) //Loops through the leaves array printing the bitstring of each valid leaf along with the character it represents. 
{
	int i = 0;

	for(i = 0; i<257; i++)
	{
		if(leaves[i]!=NULL)
		{
			if(isprint(i)) //if a character isn't printable, prints the octal value of the character.
				printf("%c:", findLeaf(leaves[i]));
			else
				printf("%o:", findLeaf(leaves[i]));
			printBits(leaves[i]);
			printf("\n");
	
		}	
	}
}





