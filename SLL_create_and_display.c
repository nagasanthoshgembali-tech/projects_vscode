#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *next;
} *nn, *head = NULL, *tail;

void createsll()
{
    head = NULL;
    tail = NULL;

    char ans;
    printf("Want to create a list? (y/n): ");
    scanf(" %c", &ans);

    while (ans == 'y' || ans == 'Y') {
        nn = (struct node *)malloc(sizeof(struct node));
        if (nn == NULL) {
            printf("\nMemory allocation failed\n");
            exit(0);
        }

        printf("Enter data: ");
        scanf("%d", &nn->data);
        nn->next = NULL;

        if (head == NULL) {
            head = nn;
            tail = nn;
        }
        else {
            tail->next = nn;
            tail = nn;
        }

        printf("Do you want to continue? (y/other): ");
        scanf(" %c", &ans);
    }
}

int main()
{
    createsll();
    return 0;
}

