#include <stdio.h>
#include <stdlib.h>

#define MAX 100

struct TwoStacks {
    int arr[MAX];
    int top1;
    int top2;
};

// Initialize the two stacks
void init(struct TwoStacks* stacks) {
    stacks->top1 = -1;
    stacks->top2 = MAX;
}

// Check if Stack 1 is empty
int isEmpty1(struct TwoStacks* stacks) {
    return stacks->top1 == -1;
}

// Check if Stack 2 is empty
int isEmpty2(struct TwoStacks* stacks) {
    return stacks->top2 == MAX;
}

// Check if the two stacks are full
int isFull(struct TwoStacks* stacks) {
    return stacks->top1 + 1 == stacks->top2;
}

// Push an element to Stack 1
void push1(struct TwoStacks* stacks, int value) {
    if (isFull(stacks)) {
        printf("Stack 1 Overflow\n");
        return;
    }
    stacks->arr[++stacks->top1] = value;
}

// Push an element to Stack 2
void push2(struct TwoStacks* stacks, int value) {
    if (isFull(stacks)) {
        printf("Stack 2 Overflow\n");
        return;
    }
    stacks->arr[--stacks->top2] = value;
}

// Pop an element from Stack 1
int pop1(struct TwoStacks* stacks) {
    if (isEmpty1(stacks)) {
        printf("Stack 1 Underflow\n");
        exit(1);
    }
    return stacks->arr[stacks->top1--];
}

// Pop an element from Stack 2
int pop2(struct TwoStacks* stacks) {
    if (isEmpty2(stacks)) {
        printf("Stack 2 Underflow\n");
        exit(1);
    }
    return stacks->arr[stacks->top2++];
}

// Display elements of Stack 1
void display1(struct TwoStacks* stacks) {
    if (isEmpty1(stacks)) {
        printf("Stack 1 is empty\n");
        return;
    }
    printf("Stack 1 elements: ");
    for (int i = 0; i <= stacks->top1; i++) {
        printf("%d ", stacks->arr[i]);
    }
    printf("\n");
}

// Display elements of Stack 2
void display2(struct TwoStacks* stacks) {
    if (isEmpty2(stacks)) {
        printf("Stack 2 is empty\n");
        return;
    }
    printf("Stack 2 elements: ");
    for (int i = MAX - 1; i >= stacks->top2; i--) {
        printf("%d ", stacks->arr[i]);
    }
    printf("\n");
}

int main() {
    struct TwoStacks stacks;
    init(&stacks);

    int choice, value, stackNumber;
    while (1) {
        printf("\n1. Push to Stack 1\n");
        printf("2. Push to Stack 2\n");
        printf("3. Pop from Stack 1\n");
        printf("4. Pop from Stack 2\n");
        printf("5. Check if Stack 1 is empty\n");
        printf("6. Check if Stack 2 is empty\n");
        printf("7. Check if both Stacks are full\n");
        printf("8. Display Stack 1\n");
        printf("9. Display Stack 2\n");
        printf("10. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter value to push to Stack 1: ");
                scanf("%d", &value);
                push1(&stacks, value);
                break;
            case 2:
                printf("Enter value to push to Stack 2: ");
                scanf("%d", &value);
                push2(&stacks, value);
                break;
            case 3:
                printf("Popped from Stack 1: %d\n", pop1(&stacks));
                break;
            case 4:
                printf("Popped from Stack 2: %d\n", pop2(&stacks));
                break;
            case 5:
                if (isEmpty1(&stacks)) {
                    printf("Stack 1 is empty\n");
                } else {
                    printf("Stack 1 is not empty\n");
                }
                break;
            case 6:
                if (isEmpty2(&stacks)) {
                    printf("Stack 2 is empty\n");
                } else {
                    printf("Stack 2 is not empty\n");
                }
                break;
            case 7:
                if (isFull(&stacks)) {
                    printf("Both stacks are full\n");
                } else {
                    printf("Both stacks are not full\n");
                }
                break;
            case 8:
                display1(&stacks);
                break;
            case 9:
                display2(&stacks);
                break;
            case 10:
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}
