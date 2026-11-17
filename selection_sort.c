#include <stdio.h>

void selection_sort(int a[], int n)
{
    int i, j, min, temp, comp = 0, swaps = 0;
    for (i = 0; i < n - 1; i++)
    {
        min = i;
        for (j = i + 1; j < n; j++)
        {
            comp++;
            if (a[j] < a[min])
                min = j;
        }
        if (min != i)
        {
            temp = a[min];
            a[min] = a[i];
            a[i] = temp;
            swaps++;
        }

        printf("\npass %d: ", i + 1);
        for (int k = 0; k < n; k++)
            printf("%d ", a[k]);
    }
    printf("\nTotal Comparisons = %d", comp);
    printf("\nTotal Swaps = %d\n", swaps);

    printf("Sorted array: ");
    for (i = 0; i < n; i++)
        printf("%d ", a[i]);
    printf("\n");
}

int main()
{
    int n;
    printf("Enter number of elements: ");
    scanf("%d", &n);

    int a[n];
    printf("Enter elements:\n");
    for (int i = 0; i < n; i++)
        scanf("%d", &a[i]);

    selection_sort(a, n);
    return 0;
}
