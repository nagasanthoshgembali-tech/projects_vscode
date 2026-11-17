#include <stdio.h>
#include <stdlib.h>

struct node
{
    int data;
    struct node *next;
};

// Global variables for the linked list version of selection sort
struct node *head = NULL;
struct node *i = NULL;
struct node *j = NULL;
struct node *minNode = NULL;
struct node *newNode = NULL;
struct node *temp = NULL;
int n, data, k, swap;

void insertAtEnd()
{
    newNode = (struct node *)malloc(sizeof(struct node));
    if (newNode == NULL)
    {
        printf("Memory allocation failed.\n");
        exit(1);
    }

    newNode->data = data;
    newNode->next = NULL;

    if (head == NULL)
    {
        head = newNode;
        return;
    }

    temp = head;
    while (temp->next != NULL)
    {
        temp = temp->next;
    }
    temp->next = newNode;
}

void selectionSort()
{
    if (head == NULL || head->next == NULL)
    {
        return;
    }

    // This is same as selection sort in array using i and j
    for (i = head; i->next != NULL; i = i->next)
    {
        minNode = i;

        for (j = i->next; j != NULL; j = j->next)
        {
            if (j->data < minNode->data)
            {
                minNode = j;
            }
        }

        if (minNode != i)
        {
            swap = i->data;
            i->data = minNode->data;
            minNode->data = swap;
        }
    }
}

void display()
{
    temp = head;

    printf("Sorted list: ");
    while (temp != NULL)
    {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

void freeList()
{
    temp = head;
    while (temp != NULL)
    {
        struct node *nextNode = temp->next;
        free(temp);
        temp = nextNode;
    }
    head = NULL;
}

int main()
{
    printf("Enter the number of elements: ");
    if (scanf("%d", &n) != 1 || n < 0)
    {
        printf("Invalid input.\n");
        return 1;
    }

    for (k = 0; k < n; k++)
    {
        printf("Enter element %d: ", k + 1);
        if (scanf("%d", &data) != 1)
        {
            printf("Invalid element input.\n");
            freeList();
            return 1;
        }
        insertAtEnd();
    }

    selectionSort();
    display();
    freeList();

    return 0;
}