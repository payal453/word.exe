#include <stdio.h>
#include <stdlib.h>

// Define the structure for a doubly linked list node
struct Node {
    int data;
    struct Node* next;
    struct Node* prev;
};

// Function to create a new node
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;
    newNode->prev = NULL;
    return newNode;
}

// Function to push an element onto the stack
void push(struct Node** head, int data) {
    struct Node* newNode = createNode(data);
    if (*head != NULL) {
        newNode->next = *head;
        (*head)->prev = newNode;
    }
    *head = newNode;
    printf("%d pushed to stack\n", data);
}

// Function to pop an element from the stack
int pop(struct Node** head) {
    if (*head == NULL) {
        printf("Stack underflow\n");
        return -1; // or other appropriate value to indicate failure
    }
    struct Node* temp = *head;
    int poppedData = temp->data;
    *head = (*head)->next;
    if (*head != NULL) {
        (*head)->prev = NULL;
    }
    free(temp);
    return poppedData;
}

// Function to print the stack
void printStack(struct Node* node) {
    while (node != NULL) {
        printf("%d ", node->data);
        node = node->next;
    }
    printf("\n");
}

int main() {
    struct Node* head = NULL;

    // Test push operation
    push(&head, 10);
    push(&head, 20);
    push(&head, 30);

    printf("Stack after pushes: ");
    printStack(head);

    // Test pop operation
    printf("Popped from stack: %d\n", pop(&head));
    printf("Stack after pop: ");
    printStack(head);

    printf("Popped from stack: %d\n", pop(&head));
    printf("Stack after pop: ");
    printStack(head);

    printf("Popped from stack: %d\n", pop(&head));
    printf("Stack after pop: ");
    printStack(head);

    // Test pop on empty stack
    printf("Popped from stack: %d\n", pop(&head));

    return 0;
}
