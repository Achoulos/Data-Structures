/*
 * File:    SelectionSort.c
 *
 * Description: This is an implemenation of the selection sort sorting algorithm
 *
 */

#include <stdlib.h>
#include <stdio.h>

#define MAX 10

int main(void)
{

    int a[MAX];
    int i, j, min, temp;
    int k = 0;
    int n = 0;
    int ddd = 0;
    int t = 0;

    printf("Please insert 10 integers to sort\n");

    for(k=0; k<MAX; k++)
    {
        scanf("%d", &a[k]);
        n++;
    }

    for(i=0; i<n-1; i++)
    {
        min = i;
        for(j = i+1; j<n; j++)
        {
            if(a[j]<a[min])
                min=j;
        }
        temp = a[min];
        a[min]=a[i];
        a[i]=temp;
    }
    while(t<n-1)
    {
        t++;
        printf("%d\n", a[t]);
    }
}


