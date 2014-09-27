/*
 * File:    QuickSort.c
 *
 * Description: This is an implemenation of the quick sort sorting algorithm
 *
 */

#include <stdio.h>
#include <stdlib.h>

#define MAX 15

int partition(int a[], int lo, int hi)
{
    int i, wall, temp, x;

    x = a[hi];

    wall = lo;

    for(i=lo; i<hi; i++)
    {
        if (a[i]<x)
        {
            temp = a[i];
            a[i] = a[wall];
            a[wall++] = temp;
        }
    }
    temp = a[hi];
    a[hi] = a[wall];
    a[wall] = temp;
    return wall;
}


void quickSort(int a[], int lo, int hi)
{
    if (lo<hi)
    {
        int pivotLocation = partition(a, lo, hi);
        quickSort(a, lo, pivotLocation-1);
        quickSort(a, pivotLocation+1, hi);
    }

}


int main(void)
{

    int a[MAX];
    int n = 15;
    int k = 0;
    int i = 0;
    int q = 0;

    printf("Please insert 10 integerss.\n");
    
    for(i=0; i<MAX; i++)
    {
        scanf("%d", &a[i]);
        q++;
    }

    quickSort(a, 0, MAX);

    while(k<n)
    {
        printf("%d\n", a[k]);
        k++;
    }



}
