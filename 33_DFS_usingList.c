#include <stdio.h>
#include <stdlib.h>

#define MAX 100

struct node {
    int data;
    struct node *next;
};

struct node *A[10];

struct StackNode {
    int data;
    struct StackNode* next;
};

struct StackNode* top = NULL;

int isEmpty() {
    return top == NULL;
}

void push(int data) {
    struct StackNode* newNode = (struct StackNode*)malloc(sizeof(struct StackNode));
    if (newNode == NULL) {
        printf("\nStack Overflow\n");
        return;
    }
    newNode->data = data;
    newNode->next = top;
    top = newNode;
}

int pop() {
    if (isEmpty()) {
        printf("\nStack Underflow\n");
        return -1;
    }
    struct StackNode* temp = top;
    int data = temp->data;
    top = top->next;
    free(temp);
    return data;
}

void DFS(struct node *A[], int n) {
    int visited[10], v;
    struct node *p;

    for (int i = 1; i <= n; i++) {
        visited[i] = 0;
    }

    printf("\nEnter start vertex : ");
    scanf("%d", &v);

    visited[v] = 1;
    printf("-%d", v);
    push(v);

    while (!isEmpty()) {
        v = top->data;
        p = A[v];
        int found = 0;

        while (p != NULL) {
            if (visited[p->data] == 0) {
                visited[p->data] = 1;
                printf("-%d", p->data);
                push(p->data);
                found = 1;
                break;
            }
            p = p->next;
        }

        if (!found) {
            pop();
        }
    }
}

void displayGraph(struct node *A[], int n) {
    printf("\nAdjacency List:\n");
    for (int i = 1; i <= n; i++) {
        struct node *p = A[i];
        printf("%d: ", i);
        while (p != NULL) {
            printf("%d -> ", p->data);
            p = p->next;
        }
        printf("NULL\n");
    }
}

int main() {
    int u, v, n;
    char ch;
    printf("Enter the no of vertex : ");
    scanf("%d", &n);

    for (int i = 1; i <= n; i++) {
        A[i] = NULL;
    }

    struct node *new, *p;
    do {
        printf("\nEnter edge :");
        scanf("%d %d", &u, &v);

        new = (struct node *)malloc(sizeof(struct node));
        new->data = v;
        new->next = NULL;
        p = A[u];

        if (p == NULL) {
            A[u] = new;
        } else {
            while (p->next != NULL) {
                p = p->next;
            }
            p->next = new;
        }

        new = (struct node *)malloc(sizeof(struct node));
        new->data = u;
        new->next = NULL;
        p = A[v];

        if (p == NULL) {
            A[v] = new;
        } else {
            while (p->next != NULL) {
                p = p->next;
            }
            p->next = new;
        }
        printf("\nYou want to enter more edges (y/n) : ");
        scanf(" %c", &ch);
    } while (ch == 'y' || ch == 'Y');

    displayGraph(A, n);
    DFS(A, n);
    return 0;
}
