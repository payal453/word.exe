#include <stdio.h>
#include <stdlib.h>

// Structure for doubly linked list node
struct Node {
    int data;
    struct Node* prev;
    struct Node* next;
};

// Structure for stack
struct Stack {
    int top;
    unsigned capacity;
    int* array;
};

// Function to create a new doubly linked list node
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->prev = NULL;
    newNode->next = NULL;
    return newNode;
}

struct Stack* createStack(unsigned capacity) {
    struct Stack* stack = (struct Stack*)malloc(sizeof(struct Stack));
    stack->top = -1;
    stack->capacity = capacity;
    stack->array = (int*)malloc(stack->capacity * sizeof(int));
    return stack;
}

void push(struct Stack* stack, int item) {
    if (stack->top == stack->capacity - 1) {
        printf("Stack Overflow\n");
        return;
    }
    stack->array[++stack->top] = item;
}

int pop(struct Stack* stack) {
    if (stack->top == -1) {
        printf("Stack Underflow\n");
        return -1;
    }
    return stack->array[stack->top--];
}

void enqueue(struct Node** front, struct Node** rear, struct Stack* stack, int data) {
    struct Node* newNode = createNode(data);

    if (*rear == NULL) {
        *front = *rear = newNode;
    } else {
        (*rear)->next = newNode;
        newNode->prev = *rear;
        *rear = newNode;
    }

    push(stack, data);
}

int dequeue(struct Node** front, struct Node** rear) {
    if (*front == NULL) {
        printf("Queue is empty\n");
        return -1;
    }

    struct Node* temp = *front;
    int data = temp->data;

    *front = (*front)->next;
    if (*front == NULL)
        *rear = NULL;
    else
        (*front)->prev = NULL;

    free(temp);
    return data;
}

void displayQueue(struct Node* front) {
    if (front == NULL) {
        printf("Queue is empty\n");
        return;
    }

    printf("Queue: ");
    while (front != NULL) {
        printf("%d ", front->data);
        front = front->next;
    }
    printf("\n");
}

int main() {
    struct Node* front = NULL;
    struct Node* rear = NULL;
    struct Stack* stack = createStack(100); // Adjust the capacity as needed

    enqueue(&front, &rear, stack, 10);
    enqueue(&front, &rear, stack, 20);
    enqueue(&front, &rear, stack, 30);

    displayQueue(front);

    printf("Deleted element: %d\n", dequeue(&front, &rear));

    displayQueue(front);

    return 0;
}
