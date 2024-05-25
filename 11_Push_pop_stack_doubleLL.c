#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* prev;
    struct Node* next;
} Node;

// Definition of the stack using a doubly linked list
typedef struct Stack {
    Node* top; 
} Stack;

Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) {
        printf("Memory allocation error\n");
        return NULL;
    }
    newNode->data = data;
    newNode->prev = NULL;
    newNode->next = NULL;
    return newNode;
}

void initializeStack(Stack* stack) {
    stack->top = NULL;
}

void push(Stack* stack, int data) {
    Node* newNode = createNode(data);
    if (!newNode) {
        return;
    }
    if (stack->top == NULL) {
        stack->top = newNode;
    } else {
        newNode->next = stack->top;
        stack->top->prev = newNode;
        stack->top = newNode;
    }
    printf("%d pushed onto stack\n", data);
}

int pop(Stack* stack) {
    if (stack->top == NULL) {
        printf("Stack Underflow\n");
        return -1;
    }
    Node* temp = stack->top;
    int poppedData = temp->data;
    stack->top = stack->top->next;
    if (stack->top != NULL) {
        stack->top->prev = NULL;
    }
    free(temp);
    printf("%d popped from stack\n", poppedData);
    return poppedData;
}

void displayStack(Stack* stack) {
    Node* current = stack->top;
    if (current == NULL) {
        printf("Stack is empty\n");
        return;
    }
    printf("Stack elements: ");
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

int main() {
    Stack stack;
    initializeStack(&stack);

    push(&stack, 10);
    push(&stack, 20);
    push(&stack, 30);
    displayStack(&stack);

    pop(&stack);
    displayStack(&stack);

    pop(&stack);
    displayStack(&stack);

    pop(&stack);
    displayStack(&stack);

    pop(&stack);

    return 0;
}
