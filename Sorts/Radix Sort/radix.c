/*
 * File:	radix.c
 *
 * Description:	This file is an implementation of Radix Sort using a deque.
 *
 */

#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include "deque.h"
#include <assert.h>
#define r 10

int main(void)
{
	int digits;
	int input;
	int max = 0;
	int i;
	int j;
	int divide=1;
	int temp;
	int truncated;

	DEQUE *buckets[9];

	DEQUE *main; 

	main = createDeque();

	assert(main!=NULL);

	printf("please input numbers to sort.\n");
	while(scanf("%d", &input)==1)//Loop for inputting each value into the main deque.
	{
		if(input<0)
		{
			printf("Please only enter values greater than or equal to 0.\n");
			continue;
		}
		addFirst(main, input);
		if(input>max) //Storing largest value inputted to determine the number of digits
			max = input;
	}

	digits = ceil(log(max+1)/log(r)); //Max digit determination

	for(i=0; i<r; i++) //Creation of an additional 10 deques to store each digit from 0-9
	{
		buckets[i] = createDeque();
		assert(buckets[i]!=NULL);
	}

	for(i=0; i<digits; i++) //Main sorting loop. It loops the same number as the maximum value of digits.
	{
		while(numItems(main)!=0)//Adds each value from the main deque to it's respective bucket based on the digit value
		{
			temp = removeFirst(main);
			truncated = (temp/divide)%r;	

			addFirst(buckets[truncated], temp); 
		}


		for(j=0; j<r; j++) //Nested loop which removes items from the buckets (in order for that place) and inputs them back into the main deque. 
		{
			while(numItems(buckets[j])!=0)
				addFirst(main, removeFirst(buckets[j]));
		}


		divide= divide*r; //Shift the digit we are sorting by for the next iteration of the loop.
	
	}

	while(numItems(main)!=0) //Prints the sorted values.
		printf("%d\n", removeLast(main));

}

