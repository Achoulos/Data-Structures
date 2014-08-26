/*
 * File:    deque.c
 *
 * Description: This is a deque utilizing a circular doubly linked-list
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "deque.h"
#include <stdbool.h>
#include <assert.h>

#define NODE struct node

struct node
{
	int data;
	NODE *next;
	NODE *prev;
};

struct deque
{
	int count;
	NODE *head;
};

DEQUE *createDeque(void) //allocates memory for the deque and creates a sentinel, then returns a pointer to the deque. O(1) 
{
	DEQUE *dp;
	dp = malloc(sizeof(DEQUE));
	
	assert(dp!=NULL);

	dp->count = 0;
	dp->head = malloc(sizeof(NODE));

	assert(dp->head!=NULL);

	dp->head->next = dp->head;
	dp->head->prev = dp->head;

	return dp;
}

void destroyDeque(DEQUE *dp) //traverses list and removes all items, then frees the deque itself. O(n)
{
	assert(dp!=NULL);

	int i = 0;
	NODE *ahead;
	ahead = dp->head->next;

	for(i=0; i<dp->count-1; i++)//Starts at the first node with a value and removes the previous, then traverses and repeats.
	{
		free(ahead->prev);
		ahead = ahead->next;
	}
	free(ahead); //Must remove self outside of loop, as there is nothing "in front" of a node in a list when it is the only node.

	free(dp);

	return;

}

int numItems(DEQUE *dp) //returns number of items in the list. O(1)
{
	assert(dp!=NULL);
	return dp->count;
}

void addFirst(DEQUE *dp, int x) //adds a node to the first position in the list with the data passed into it. O(1)
{
	assert(dp!=NULL);

	NODE *new;
	new = malloc(sizeof(NODE));
	
	assert(new!=NULL);

	dp->head->next->prev = new; //Points the first node's previous pointer to the new node.
	new->next = dp->head->next;
	new->prev = dp->head;
	dp->head->next = new;

	dp->count++;

	new->data = x;

	return;

}

void addLast(DEQUE *dp, int x) //adds a node to the last position in the list with the data passed in. O(1)
{
	assert(dp!=NULL);
	NODE *new;
	new = malloc(sizeof(NODE));

	assert(new!=NULL);

	dp->head->prev->next = new; //Points the last node's next pointer to the next node.
	new->prev = dp->head->prev;
	dp->head->prev = new;
	new->next = dp->head;

	dp->count++;

	new->data = x;

	return;
}

int removeFirst(DEQUE *dp) //removes the first node in the list and returns the data in it. O(1)
{
	assert(dp!=NULL);
	assert(dp->count!= 0);
	
	NODE *deleted;
	deleted = dp->head->next;

	int data = deleted->data;

	dp->head->next = deleted->next;

	deleted->next->prev = dp->head;

	dp->count--;

	free(deleted);

	return data;
	
}

int removeLast(DEQUE *dp) //removes the last node in the list and returns the data in it. O(1)
{
	assert(dp!=NULL);
	assert(dp->count!=0);
	
	NODE *deleted; 
	deleted = dp->head->prev;
	
	int data = deleted->data;

	deleted->prev->next = dp->head;
	dp->head->prev = deleted->prev;

	dp->count--;

	free(deleted);
	
	return data;

}

int getFirst(DEQUE *dp) //returns the data in the first position in the deque. O(1)
{
	assert(dp!=NULL);
	assert(dp->count!=0);

	return dp->head->next->data;
}

int getLast(DEQUE *dp) //returns the data in the last position in the deque. O(1)
{
	assert(dp!=NULL);
	assert(dp->count!=0);

	return dp->head->prev->data;

}

