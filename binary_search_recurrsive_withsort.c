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

int partition(int a[], int low, int high) {
    int pivot = a[low];
    int start = low;
    int end = high;

    while (start < end) {
        while (a[start] <= pivot && start < high)
            start++;

        while (a[end] > pivot)
            end--;

        if (start < end)
            swapping(&a[start], &a[end]);
    }

    swapping(&a[low], &a[end]);
    return end;
}

void quickSort(int a[], int low, int high) {
    if (low < high) {
        int loc = partition(a, low, high);
        quickSort(a, low, loc - 1);
        quickSort(a, loc + 1, high);
    }
}

int main() {
    int n, key, position;

    printf("enter number of elements: ");
    scanf("%d", &n);

    int a[n];

    printf("enter %d elements: ", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }

    quickSort(a, 0, n - 1);

    printf("Sorted array: ");
    printArray(a, n);

    printf("enter element to search: ");
    scanf("%d", &key);

    position = binarySearch(a, 0, n - 1, key);

    if (position == -1)
        printf("Element not found\n");
    else
        printf("position = %d in sorted array",position+1);

    return 0;
}