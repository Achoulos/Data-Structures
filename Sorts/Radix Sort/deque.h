/*
 * File:	deque.h
 *
 * Description:	This file has the function declarations for a deque of integers. 
 *
 */

# ifndef DEQUE_H
# define DEQUE_H

typedef struct deque DEQUE;

extern DEQUE *createDeque(void);

extern void destroyDeque(DEQUE *dp);

extern int numItems(DEQUE *dp);

extern void addFirst(DEQUE *dp, int x);

extern void addLast(DEQUE *dp, int x);

extern int removeFirst(DEQUE *dp);

extern int removeLast(DEQUE *dp);

extern int getFirst(DEQUE *dp);

extern int getLast(DEQUE *dp);

# endif /* DEQUE_H */
