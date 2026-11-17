#include<stdio.h>
#include<stdlib.h>

struct node {
    int data;
    struct node *next;
} *nn, *head, *current, *tail;

void createsll() {
    head = NULL;
    tail = NULL;
    char ans;

    printf("Want to create a list?(y/n): ");
    scanf(" %c", &ans);

    while (ans == 'y' || ans == 'Y') {
        nn = (struct node*)malloc(sizeof(struct node));
        if (nn == NULL) {
            printf("no memory space for newnode\n");
            exit(EXIT_FAILURE);
        }

        printf("enter int data: ");
        scanf("%d", &nn->data);
        nn->next = NULL;

        if (head == NULL) {
            head = nn;
            tail = nn;
        } else {
            tail->next = nn;
            tail = nn;
        }

        printf("Want to add elements in list?(y/n): ");
        scanf(" %c", &ans);
    }
}

void displaysll() {
    if (head == NULL) {
        printf("List is empty\n");
        return;
    }

    current = head;
    while (current != NULL) {
        printf("%d -> ", current->data);
        current = current->next;
    }
    printf("NULL\n");
}

int main() {
    createsll();
    displaysll();
    return 0;
}
