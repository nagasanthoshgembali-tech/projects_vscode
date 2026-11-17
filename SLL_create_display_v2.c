#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *next;
};

struct node *nn;
struct node *head;
struct node *current;
struct node *tail;

void createsll(void)
{
    head = NULL;
    tail = NULL;

    char ans;
    printf("Want to create a list? (y/n): ");
    scanf(" %c", &ans);

    while (ans == 'y' || ans == 'Y') {
        nn = malloc(sizeof(struct node));
        if (nn == NULL) {
            printf("No memory space for new node\n");
            exit(EXIT_FAILURE);
        }

        printf("Enter int data: ");
        scanf("%d", &nn->data);
        nn->next = NULL;

        if (head == NULL) {
            head = nn;
            tail = nn;
        } else {
            tail->next = nn;
            tail = nn;
        }

        printf("Want to add elements in list? (y/n): ");
        scanf(" %c", &ans);
    }
}

void displaysll(void)
{
    if (head == NULL) {
        printf("List is empty\n");
    } else {
        current = head;
        while (current != NULL) {
            printf("%d -> ", current->data);
            current = current->next;
        }
        printf("NULL\n");
    }
}

int main(void)
{
    createsll();
    displaysll();
    return 0;
}

