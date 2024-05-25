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
        char data = stack[top];
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
    int n,result=1;
    printf("Enter number:\n");
    scanf("%d",&n);
    for(int i = 1 ; i<=n ; i++)
    {
        push(i);
    }
    
     while (!isEmpty()) {
        result *= pop();
    }

    printf("%d",result);
    
}


