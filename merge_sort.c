#include <stdio.h>

void merge(int a[], int lb, int mid, int ub)
{
    int i, j, k, b[50];
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

void mergesort(int a[], int lb, int ub)
{
    int mid;
    if (lb < ub)
    {
        mid = lb + (ub - lb) / 2;
        mergesort(a, lb, mid);
        mergesort(a, mid + 1, ub);
        merge(a, lb, mid, ub);
    }
}

int main()
{
    int  n, i;
    printf("Enter no. of elements less than 50: ");
    scanf("%d", &n);

    int a[n];

    printf("Enter elements:\n");
    for (i = 0; i < n; i++)
        scanf("%d", &a[i]);

    ;
    mergesort(a, 0, n - 1);

    printf("\nSorted Array:\n");
    for (i = 0; i < n; i++)
        printf("%d ", a[i]);
    printf("\n");

    return 0;
}