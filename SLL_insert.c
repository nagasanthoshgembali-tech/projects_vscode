#include <stdio.h>
#include <stdlib.h>

struct node
{
    int data;
    struct node *next;
} *head = NULL, *newnode, *temp;

/* Insertion at the Front (Beginning) */
void insertBeginning()
{
    char ch;
    do
    {
        newnode = (struct node *)malloc(sizeof(struct node));

        if (newnode == NULL)
        {
            printf("Memory allocation failed");
            return;
        }

        printf("Enter data: ");
        scanf("%d", &newnode->data);

        newnode->next = head;
        head = newnode;
        printf("Add another node? (y/n): ");
        scanf(" %c", &ch);
    } while (ch == 'y' || ch == 'Y');
}

/* Create SLL / Insertion at the End (merged) */
void insertEnd()
{
    char ch;

    do
    {
        newnode = (struct node *)malloc(sizeof(struct node));

        if (newnode == NULL)
        {
            printf("Memory allocation failed");
            return;
        }

        printf("Enter data: ");
        scanf("%d", &newnode->data);

        newnode->next = NULL;

        if (head == NULL)
        {
            head = newnode;
        }
        else
        {
            temp = head;
            while (temp->next != NULL)
            {
                temp = temp->next;
            }
            temp->next = newnode;
        }

        printf("Add another node? (y/n): ");
        scanf(" %c", &ch);

    } while (ch == 'y' || ch == 'Y');
}

/* Insertion at a Given Position */
void insertPosition()
{
    int pos, i;
    char ch;
    do
    {
        newnode = (struct node *)malloc(sizeof(struct node));

        if (newnode == NULL)
        {
            printf("Memory allocation failed");
            return;
        }

        printf("Enter data: ");
        scanf("%d", &newnode->data);

        printf("Enter position: ");
        scanf("%d", &pos);

        if (pos <= 0)
        {
            printf("Invalid position\n");
            free(newnode);
            break;
        }

        if (pos == 1)
        {
            newnode->next = head;
            head = newnode;
        }
        else
        {
            temp = head;
            for (i = 1; i < pos - 1 && temp != NULL; i++)
            {
                temp = temp->next;
            }

            if (temp == NULL)
            {
                printf("Position out of range\n");
                free(newnode);
                break;
            }

            newnode->next = temp->next;
            temp->next = newnode;
        }

        printf("Add another node? (y/n): ");
        scanf(" %c", &ch);
    } while (ch == 'y' || ch == 'Y');
}

/* Display the Linked List */
void display()
{
    temp = head;

    if (temp == NULL)
    {
        printf("List is empty\n");
        return;
    }

    while (temp != NULL)
    {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

int main()
{
    int choice;

    while (1)
    {
        system("cls");
        printf("\n1. Insert at Beginning\n");
        printf("2. Create SLL / Insert at End\n");
        printf("3. Insert at Position\n");
        printf("4. Display\n");
        printf("5. Exit\n");

        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            insertBeginning();
            break;
        case 2:
            insertEnd();
            break;
        case 3:
            insertPosition();
            break;
        case 4:
            display();
            break;
        case 5:
            exit(0);

        default:
            printf("Invalid choice\n");
        }

        system("pause");
    }

    return 0;
}