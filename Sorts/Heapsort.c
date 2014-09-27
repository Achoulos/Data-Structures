/*
 * File:    HeapSort.c
 *
 * Description: This is an implemenation of a heap sort sorting algorithm using a binary heap
 *
 */

#include <stdio.h>
#include <stdlib.h>

#define MAX 10


int p(int i)
{
    return ((i-1)/2);
}

int lc(int i)
{
    return 2*i+1;
}

int rc(int i)
{
    return 2*i+2;
}

int delete(int heap[], int *count)
{
    int i, x, child, max;
    
    max = heap[0];
    x= heap[--(*count)];
    i = 0;
    while(lc(i)<*count)
    {
        child = lc(i);
        if(rc(i)<*count&&heap[lc(i)]<heap[rc(i)])
            child = rc(i);
        if (x<heap[child])
        {
            heap[i]=heap[child];
            i=child;
        }
        else
            break;
    }
    heap[i]=x;
    return max;
    
}


void insert(int heap[], int *count, int x)
{
    
    int i;
    
    i=(*count)++;
    
    while(i>0&&heap[p(i)]<x)
    {
        heap[i]=heap[p(i)];
        i=p(i);
    }
    heap[i]=x;
}



int main(void)
{
    int i, count;
    int k = 0;
    int q = 0;
    int d = 0;
    
    count = 0;
    
    int a[MAX];
    
    printf("Please insert 10 integers to sort\n");
    
    for(k=0; k<MAX; k++)
    {
        scanf("%d", &a[k]);
        q++;
    }
    
    int n = MAX;
    
    for(i = 0; i<n; i++)
        insert(a, &count, a[i]);
    
    for(i=0; i<n; i++)
        a[n-i-1] = delete(a, &count);
    
    while(d<n)
    {
        printf("%d\n", a[d]);
        d++;
    }
}

