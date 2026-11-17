#include<stdio.h>
#include<stdlib.h>
#define MAX 5

int array[MAX];
int top = -1;

void push(){
    if(top == MAX-1){
        puts("stack overflow");
        return;
    }
    printf("enter value to push: ");
    int val;
    scanf("%d",&val);
    top++;
    array[top] = val;
    printf("%d pushed succesfully\n",val);
}

void pop(){
    if(top == -1){
        puts("stack underflow");
        return;
    }
    int val = array[top];
    top--;
    printf("popped %d successfully\n",val);
}

void peek(){
    if(top == -1){
        puts("stack underflow");
        return;
    }
    printf("top element is %d\n",array[top]);

}

void display(){
    if(top == -1){
        puts("stack underflow");
        return;
    }
    puts("STACK:");
    for(int i = top; i>=0; i--){
        printf("%d",array[i]);
        puts("");
    }
}

int main(){
    int choice;
    while(1){
        system("cls");
        puts("1.push");
        puts("2.pop");
        puts("3.peek");
        puts("4.display");
        puts("5.exit");
        printf("enter your choice: ");
        scanf("%d",&choice);

        switch(choice){
            case 1:push();break;
            case 2:pop();break;
            case 3:peek();break;
            case 4:display();break;
            case 5:exit(0);break;
            default:printf("Invalid choice %d",choice);
        }
        system("pause");
    }
    puts("Program terminated");
}