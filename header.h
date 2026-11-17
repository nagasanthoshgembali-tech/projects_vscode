#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>

static inline void swapping(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

static inline void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}
static inline void scanArray(int arr[], int n) {
    for (int i = 0; i < n; i++) 
        scanf("%d", &arr[i]);
}
static inline void copyArray(int a[],int b[],int n){
    for (int i =0;i<n;i++)
        b[i]=a[i];
}
static inline int comArray(int a[],int b[],int n){
    int check=0;
    for(int i=0;i<n;i++)
    if(a[i]!=b[i])
        check=1;
    return check;    
    
}

static inline void merge(int a[], int lb, int mid, int ub){
    int i, j, k, b[ub+1];
    i = lb;
    j = mid + 1;
    k = lb;

    while (i <= mid && j <= ub)
    {
        if (a[i] <= a[j])
        {
            b[k] = a[i];
            i++;
        }
        else
        {
            b[k] = a[j];
            j++;
        }
        k++;
    }

    while (i <= mid)
    {
        b[k] = a[i];
        i++;
        k++;
    }

    while (j <= ub)
    {
        b[k] = a[j];
        j++;
        k++;
    }

    for (i = lb; i <= ub; i++)
        a[i] = b[i];
}
static inline void mergesort(int a[], int lb, int ub){
    int mid;
    if (lb < ub)
    {
        mid = lb + (ub - lb) / 2;
        mergesort(a, lb, mid);
        mergesort(a, mid + 1, ub);
        merge(a, lb, mid, ub);
    }
}

#endif