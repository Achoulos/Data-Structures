/*
 * File:        set.h
 *
 * Description: This file contains the function and type
 *              declarations for a set ADT for strings.
 *
 */

# ifndef SET_H
# define SET_H

typedef struct set SET;

SET *createSet(int maxElts); //returns a pointer to a new set with a maximum capacity of maxElts

void destroySet(SET *sp); //deallocate memory associated with the set pointed to by sp

int numElements(SET *sp); //return the number of elements in the set pointed to by sp

bool hasElement(SET *sp, char *elt); //return whether elt is a member of the set pointed to by sp

bool addElement(SET *sp, char *elt); //add elt to the set pointed to by sp, and return whether the set changed

bool removeElement(SET *sp, char *elt); //remove elt from the set pointed to by sp, and return whether the set changed.

# endif /* SET_H */