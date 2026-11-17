#include <stdio.h>

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int partition(int arr[], int low, int high) {
    int pivot = arr[low];   // choosing first element as pivot
    int start = low;
    int end = high;

    while (start < end) {
        while (arr[start] <= pivot && start < high)
            start++;
        while (arr[end] > pivot)
            end--;
        if (start < end)
            swap(&arr[start], &arr[end]);
    }
    swap(&arr[low], &arr[end]);  // place pivot in correct position
    return end;
}

void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int loc = partition(arr, low, high);

        quickSort(arr, low, loc - 1);
        quickSort(arr, loc + 1, high);
    }
}

int main() {
    int n;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    int arr[n];

    printf("Enter %d elements: ", n);
    for (int i = 0; i < n; i++)
        scanf("%d", &arr[i]);

    quickSort(arr, 0, n - 1);

    printf("Sorted array: ");
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");

    return 0;
}