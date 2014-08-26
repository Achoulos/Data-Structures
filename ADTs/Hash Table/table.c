/*
 * File:        table.c
 *
 * Description: This is an ADT that allows a user to manipulate a set of strings with
 * add, remove, and delete functions. It is powered by hash functions and tables.
 *
 */

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "set.h"

#define EMPTY 0
#define FILLED 1
#define DELETED 2

struct set
{
	int count; //number of words currently being stored
	int length; //total number of spaces for string pointers
	char **elts; //pointer to array of string pointers
	char *flags;
};

SET *createSet(int maxElts) //Allocates memory for the set and creates it. O(1)
{
	SET *sp;
	sp = malloc(sizeof(SET));
	assert(sp!=NULL);
	int i;

	sp->count =  0;
	sp->length = maxElts;
	sp->elts = malloc(sizeof(char*)*maxElts);
	sp->flags = malloc(sizeof(char*)*maxElts);
	for(i=0;i<sp->length;i++)
		sp->flags[i]=EMPTY;
	assert((sp->elts!=NULL)&&(sp->flags!=NULL));

	return sp;
}

int numElements(SET *sp) //Returns the total number of strings in the set. O(1)
{
	assert(sp!=NULL);
	return sp->count;
}

void destroySet(SET *sp) //Frees all memory allocated by the set. O(n)
{
	int i;
	assert(sp!=NULL);
	for(i=0;i<sp->count;i++)
	{
		if(sp->flags[i]==FILLED)	
			free(sp->elts[i]);
	}
	free(sp->flags);
	free(sp->elts);
	free(sp);
	return;
}

unsigned hashString(char *s) //Maps a string to an unsigned value for use in a hash table. O(n)
{
	unsigned hash = 0;

	while (*s != '\0')
		hash = 31 * hash + *s ++;

	return hash;
}


int findElement(SET *sp, char *elt, bool *found) //Searches for strings within hash table and returns the position they are at or the position they should be at. O(1), with worst-case runtime O(n)
{
	assert(sp!=NULL&&elt!=NULL);
	
	unsigned hash;

	int i;

	bool deletefound = false;

	int firstdeleteposition = -1;

	unsigned position;

	hash = hashString(elt);

	for(i=0; i<sp->length; i++)
	{
		position = (hash+i)%sp->length;

		if(sp->flags[position]==EMPTY)
		{
			if(firstdeleteposition==-1)
			{	
				*found = false;
				return position;
			}
			else
				*found = false;
				return firstdeleteposition;
		}

		else if(sp->flags[position]==FILLED)
		{
			if(strcmp(elt, sp->elts[(hash+i)%sp->length])==0)
			{
				*found = true;
				return position;
			}
		}
		else if((deletefound==false)&&(sp->flags[position]==DELETED))
		{
			deletefound = true;
			firstdeleteposition = position;
		}
	}

	*found = false;
	return firstdeleteposition;
	
}

bool hasElement(SET *sp, char *elt) //Checks to see if an element exists in the array. O(1), with worst-case runtime O(n)
{
	bool found;
	assert((sp!=NULL)&&(elt!=NULL));
	findElement(sp, elt, &found);
	return found;
}

bool addElement(SET *sp, char *elt) //Adds element in position returned by findElement. O(1), with worst-case runtime O(n)
{
	assert((sp!=NULL)&&(elt!=NULL));

    bool found;
	int position;

	position = findElement(sp, elt, &found);
	
	if (found==true)
		return false;

	elt = strdup(elt);
	
	sp->elts[position]=elt;
	sp->flags[position] = FILLED;
	sp->count++;

	return true;

}

bool removeElement(SET *sp, char *elt) //Removes element in position returned by findElement. O(1), with worst-case runtime O(n)
{

	assert((sp!=NULL)&&(elt!=NULL));

    int position;
    bool found;

    position = findElement(sp, elt, &found);

    if(found==false)
    	return false;
	
	free(sp->elts[position]);
	sp->flags[position] = DELETED;
	sp->count--;

	return false;
}
























