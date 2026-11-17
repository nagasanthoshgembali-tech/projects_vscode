#include <stdio.h>

void bubbleSort(int a[], int n)
{
    int comp = 0, swaps = 0;
 
    for (int i = 0; i < n - 1; i++)
    {
        int check = 0;
        for (int j = 0; j < n - i - 1; j++)
        {
            comp++;
            if (a[j] > a[j + 1])
            {
                int temp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = temp;
                swaps++;
                check = 1;
            }
        }
        if (check == 0)
            break;

        printf("\nPass %d: ", i + 1);
        for (int j = 0; j < n; j++)
            printf("%d ", a[j]);
    }
    
    printf("\nSorted Array: ");
    for (int i = 0; i < n; i++)
        printf("%d ", a[i]);
 
    printf("\nTotal Comparisons = %d", comp);
    printf("\nTotal Swaps = %d\n", swaps);
}

int main()
{
    int a[100], n;
 
    printf("Enter number of elements: ");
    scanf("%d", &n);
 
    printf("Enter array elements:\n");
    for (int i = 0; i < n; i++)
        scanf("%d", &a[i]);
 
    bubbleSort(a, n);
 
    return 0;
}
