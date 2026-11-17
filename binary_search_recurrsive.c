#include <stdio.h>
#include "header.h"

int binarySearch(int a[], int low, int high, int key) {
    if (low > high)
        return -1;

    int mid = low + (high - low) / 2;

    if (a[mid] == key)
        return mid;
    else if (a[mid] > key)
        return binarySearch(a, low, mid - 1, key);
    else
        return binarySearch(a, mid + 1, high, key);
}

int main() {
    int n, key, position;

    printf("enter number of elements: ");
    scanf("%d", &n);

    int a[n];int b[n];

    printf("enter sorted elements: ");
    scanArray(a,n);

    copyArray(a,b,n);
    mergesort(b,0,n-1);
    if(comArray(a,b,n)){
        puts("entered array is not sorted");
        return 1;
    }

    printf("enter element to search: ");
    scanf("%d", &key);

    

    position = binarySearch(a, 0, n - 1, key);

    if (position == -1)
        puts("Element not found");
    else
        printf("\nposition = %d",position+1);

    return 0;
}