#include <stdio.h>
#include <stdlib.h>

// Stack structure for managing items
struct Stack {
    int top;
    int items[100];
};

// Stack operations
void init(struct Stack* stack) {
    stack->top = -1;
}

int isEmpty(struct Stack* stack) {
    return stack->top == -1;
}

int isFull(struct Stack* stack) {
    return stack->top == 100 - 1;
}

void push(struct Stack* stack, int value) {
    if (isFull(stack)) {
        printf("Stack overflow\n");
        return;
    }
    stack->items[++stack->top] = value;
}

int pop(struct Stack* stack) {
    if (isEmpty(stack)) {
        printf("Stack underflow\n");
        exit(1);
    }
    return stack->items[stack->top--];
}

int peek(struct Stack* stack) {
    if (isEmpty(stack)) {
        printf("Stack is empty\n");
        exit(1);
    }
    return stack->items[stack->top];
}

// Helper functions for infix to postfix conversion
int precedence(char op) {
    switch (op) {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
        case '^':
            return 3;
        default:
            return 0;
    }
}

int isOperator(char ch) {
    return ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^';
}

// Infix to postfix conversion function
void infixToPostfix(char* infix, char* postfix) {
    struct Stack stack;
    init(&stack);
    int j = 0;

    for (int i = 0; infix[i] != '\0'; i++) {
        if (isdigit(infix[i])) {
            postfix[j++] = infix[i];
        } else if (infix[i] == '(') {
            push(&stack, infix[i]);
        } else if (infix[i] == ')') {
            while (!isEmpty(&stack) && peek(&stack) != '(') {
                postfix[j++] = pop(&stack);
            }
            pop(&stack); // Remove '(' from stack
        } else if (isOperator(infix[i])) {
            while (!isEmpty(&stack) && precedence(peek(&stack)) >= precedence(infix[i])) {
                postfix[j++] = pop(&stack);
            }
            push(&stack, infix[i]);
        }
    }

    while (!isEmpty(&stack)) {
        postfix[j++] = pop(&stack);
    }

    postfix[j] = '\0';
}

// Postfix expression evaluation function
int evaluatePostfix(char* postfix) {
    struct Stack stack;
    init(&stack);

    for (int i = 0; postfix[i] != '\0'; i++) {
        if (isdigit(postfix[i])) {
            push(&stack, postfix[i] - '0');
        } else if (isOperator(postfix[i])) {
            int val2 = pop(&stack);
            int val1 = pop(&stack);
            switch (postfix[i]) {
                case '+': push(&stack, val1 + val2); break;
                case '-': push(&stack, val1 - val2); break;
                case '*': push(&stack, val1 * val2); break;
                case '/': push(&stack, val1 / val2); break;
                case '^': push(&stack, (int)pow(val1, val2)); break;
            }
        }
    }

    return pop(&stack);
}

int main() {
    char infix[100], postfix[100];
    printf("Enter infix expression: ");
    scanf("%s", infix);

    infixToPostfix(infix, postfix);
    printf("Postfix expression: %s\n", postfix);

    int result = evaluatePostfix(postfix);
    printf("Result of evaluation: %d\n", result);

    return 0;
}
