#include<stdio.h>
#include<stdlib.h>

struct node{
    int data;
    struct node *next;
}*newnode,*head=NULL;

void push(){
    int val;
    printf("enter value to push: ");
    scanf("%d",&val);
    newnode=(struct node*)malloc(sizeof(struct node));
    if(newnode ==  NULL){
        puts("memory not allocated");
        return;
    }
    newnode->data = val;
    newnode->next = head;
    head=newnode;       
}

void pop(){
    int val;
    if(head == NULL){
        puts("stack is empty");
        return;
    }
    val = head->data;
    newnode = head;
    head = head->next;
    free(newnode);
    printf("popped value: %d\n", val);
}

void peek(){
    if(head == NULL){
        puts("stack is empty");
        return;
    }
    printf("top value: %d\n", head->data);
}

void display(){
    if(head == NULL){
        puts("stack is empty");
        return;
    }
    newnode = head;
    printf("stack elements: ");
    while(newnode != NULL){
        printf("%d ", newnode->data);
        puts("");
        newnode = newnode->next;
    }
    puts("");
}

int main(){
    int choice;
    while(1){
        system("cls");
        printf("1. Push\n2. Pop\n3. Peek\n4. Display\n5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d",&choice);
        switch(choice){
            case 1:
                push();
                break;
            case 2:
                pop();
                break;
            case 3:
                peek();
                break;
            case 4:
                display();
                break;
            case 5:
                exit(0);
            default:
                puts("Invalid choice");
        }

        system("pause");
    }
    return 0;
}