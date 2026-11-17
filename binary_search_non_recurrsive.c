#include <stdio.h>

int binarySearch(int a[], int n, int target) {
    int low = 0;
    int high = n - 1;

    while (low <= high) {
        int mid = low + (high - low) / 2;

        if (a[mid] == target) {
            return mid;   
        }
        else if (a[mid] < target) {
            low = mid + 1; 
        }
        else {
            high = mid - 1;
        }
    }

    return -1;
}

int main() {
    int n, target, result;

    printf("number of elements: ");
    scanf("%d", &n);

    int a[n];
    printf("Enter %d numbers in sorted order:\n",n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }

    printf("Enter the number to search: ");
    scanf("%d", &target);

    result = binarySearch(a,n,target);

    if (result == -1) {
        printf("Number not found.\n");
    } else {
        printf("Number found at index %d\n", result);
    }

    return 0;
}
