#include <stdio.h>
#include <stdlib.h>

// Structure for a binary tree node
struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};

// Function to create a new node
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    return newNode;
}

// Stack structure for non-recursive traversal
struct Stack {
    int top;
    unsigned capacity;
    struct Node** array;
};

// Function to create a stack
struct Stack* createStack(unsigned capacity) {
    struct Stack* stack = (struct Stack*)malloc(sizeof(struct Stack));
    stack->capacity = capacity;
    stack->top = -1;
    stack->array = (struct Node**)malloc(stack->capacity * sizeof(struct Node*));
    return stack;
}

// Function to check if stack is full
int isFull(struct Stack* stack) {
    return stack->top == stack->capacity - 1;
}

// Function to check if stack is empty
int isEmpty(struct Stack* stack) {
    return stack->top == -1;
}

// Function to push node onto stack
void push(struct Stack* stack, struct Node* node) {
    if (isFull(stack))
        return;
    stack->array[++stack->top] = node;
}

// Function to pop node from stack
struct Node* pop(struct Stack* stack) {
    if (isEmpty(stack))
        return NULL;
    return stack->array[stack->top--];
}

// Function to perform postorder traversal iteratively
void postorderTraversal(struct Node* root) {
    if (root == NULL)
        return;

    struct Stack* stack1 = createStack(100);
    struct Stack* stack2 = createStack(100);
    push(stack1, root);

    while (!isEmpty(stack1)) {
        struct Node* temp = pop(stack1);
        push(stack2, temp);

        if (temp->left)
            push(stack1, temp->left);
        if (temp->right)
            push(stack1, temp->right);
    }

    while (!isEmpty(stack2)) {
        struct Node* temp = pop(stack2);
        printf("%d ", temp->data);
    }
    printf("\n");
}

// Function to perform inorder traversal iteratively
void inorderTraversal(struct Node* root) {
    if (root == NULL)
        return;

    struct Stack* stack = createStack(100);
    struct Node* current = root;

    while (current != NULL || !isEmpty(stack)) {
        while (current != NULL) {
            push(stack, current);
            current = current->left;
        }

        current = pop(stack);
        printf("%d ", current->data);
        current = current->right;
    }
    printf("\n");
}

// Function to perform preorder traversal iteratively
void preorderTraversal(struct Node* root) {
    if (root == NULL)
        return;

    struct Stack* stack = createStack(100);
    push(stack, root);

    while (!isEmpty(stack)) {
        struct Node* temp = pop(stack);
        printf("%d ", temp->data);

        if (temp->right)
            push(stack, temp->right);
        if (temp->left)
            push(stack, temp->left);
    }
    printf("\n");
}

// Function to display leaf nodes of the tree
void displayLeafNodes(struct Node* root) {
    if (root == NULL)
        return;

    struct Stack* stack = createStack(100);
    push(stack, root);

    while (!isEmpty(stack)) {
        struct Node* temp = pop(stack);

        if (temp->left == NULL && temp->right == NULL)
            printf("%d ", temp->data);

        if (temp->right)
            push(stack, temp->right);
        if (temp->left)
            push(stack, temp->left);
    }
    printf("\n");
}

// Function to mirror the binary tree
void mirrorTree(struct Node* root) {
    if (root == NULL)
        return;

    struct Stack* stack = createStack(100);
    push(stack, root);

    while (!isEmpty(stack)) {
        struct Node* temp = pop(stack);
        struct Node* tempSwap = temp->left;
        temp->left = temp->right;
        temp->right = tempSwap;

        if (temp->left)
            push(stack, temp->left);
        if (temp->right)
            push(stack, temp->right);
    }
}

// Driver program
int main() {
    // Creating a sample binary tree
    struct Node* root = createNode(1);
    root->left = createNode(2);
    root->right = createNode(3);
    root->left->left = createNode(4);
    root->left->right = createNode(5);

    int choice;
    while (1) {
        printf("Menu:\n");
        printf("1. Postorder Traversal\n");
        printf("2. Inorder Traversal\n");
        printf("3. Preorder Traversal\n");
        printf("4. Display Leaf Nodes\n");
        printf("5. Mirror the Tree\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Postorder Traversal: ");
                postorderTraversal(root);
                break;
            case 2:
                printf("Inorder Traversal: ");
                inorderTraversal(root);
                break;
            case 3:
                printf("Preorder Traversal: ");
                preorderTraversal(root);
                break;
            case 4:
                printf("Leaf Nodes: ");
                displayLeafNodes(root);
                break;
            case 5:
                mirrorTree(root);
                printf("Tree has been mirrored.\n");
                break;
            case 6:
                printf("Exiting...\n");
                exit(0);
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}
