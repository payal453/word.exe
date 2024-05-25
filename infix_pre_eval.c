#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX 100

typedef struct {
    int top;
    int items[MAX];
} Stack;

void push(Stack* s, int value) {
    if (s->top == MAX - 1) {
        printf("Stack overflow\n");
        return;
    }
    s->items[++(s->top)] = value;
}

int pop(Stack* s) {
    if (s->top == -1) {
        printf("Stack underflow\n");
        return -1;
    }
    return s->items[(s->top)--];
}

int isEmpty(Stack* s) {
    return s->top == -1;
}

char peek(Stack* s) {
    return s->items[s->top];
}

int precedence(char op) {
    switch (op) {
        case '+':
        case '-': return 1;
        case '*':
        case '/': return 2;
        case '^': return 3;
        default: return 0;
    }
}

int isOperator(char ch) {
    return ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^';
}

void reverse(char* exp) {
    int len = strlen(exp);
    for (int i = 0; i < len / 2; i++) {
        char temp = exp[i];
        exp[i] = exp[len - i - 1];
        exp[len - i - 1] = temp;
    }
}

void infixToPrefix(char infix[], char prefix[]) {
    Stack s;
    s.top = -1;
    reverse(infix);
    for (int i = 0; i < strlen(infix); i++) {
        if (infix[i] == '(') {
            infix[i] = ')';
        } else if (infix[i] == ')') {
            infix[i] = '(';
        }
    }

    int j = 0;
    for (int i = 0; i < strlen(infix); i++) {
        char ch = infix[i];

        if (isdigit(ch)) {
            prefix[j++] = ch;
        } else if (ch == '(') {
            push(&s, ch);
        } else if (ch == ')') {
            while (!isEmpty(&s) && peek(&s) != '(') {
                prefix[j++] = pop(&s);
            }
            pop(&s); // Remove '(' from stack
        } else if (isOperator(ch)) {
            while (!isEmpty(&s) && precedence(peek(&s)) > precedence(ch)) {
                prefix[j++] = pop(&s);
            }
            push(&s, ch);
        }
    }

    while (!isEmpty(&s)) {
        prefix[j++] = pop(&s);
    }

    prefix[j] = '\0';
    reverse(prefix);
}

int evaluatePrefix(char prefix[]) {
    Stack s;
    s.top = -1;
    int len = strlen(prefix);

    for (int i = len - 1; i >= 0; i--) {
        char ch = prefix[i];

        if (isdigit(ch)) {
            push(&s, ch - '0');
        } else if (isOperator(ch)) {
            int val1 = pop(&s);
            int val2 = pop(&s);
            switch (ch) {
                case '+': push(&s, val1 + val2); break;
                case '-': push(&s, val1 - val2); break;
                case '*': push(&s, val1 * val2); break;
                case '/': push(&s, val1 / val2); break;
                case '^': push(&s, val1 ^ val2); break;
            }
        }
    }

    return pop(&s);
}

int main() {
    char infix[MAX], prefix[MAX];

    printf("Enter an infix expression: ");
    scanf("%s", infix);

    infixToPrefix(infix, prefix);

    printf("Prefix expression: %s\n", prefix);

    int result = evaluatePrefix(prefix);

    printf("Result of evaluation: %d\n", result);

    return 0;
}