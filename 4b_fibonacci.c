
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 20

int stack[MAX];
int top = -1;

void push(int a) {
    if (top == MAX-1) {
        printf("Stack full\n");
    } else {
        top++;
        stack[top] = a;
    }
}

int pop() {
    if (top == -1) {
        printf("Stack empty\n");
        return '\0';
    } else {
        int data = stack[top];
        top--;
        return data;
    }
}

int isEmpty() {
    return top == -1;
}

int isFull()
{
    return top == MAX-1;
}

int main()
{
    int n;
    printf("Enter number:\n");
    scanf("%d",&n);
    push(0);
    push(1);

    printf("Fibonacci Series up to %d terms:\n", n);
    printf("0 ");
    printf("1 ");
    for(int i = 2 ; i < n ; i++)
    {
        int a = pop();
        int b = pop();
        push(a);
        push(a+b);
        int x = pop();
        printf("%d ", x);
        push(x);

    }
    
    printf("\n");
    return 0;
}