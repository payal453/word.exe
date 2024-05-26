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

// Function to insert a node into the BST
struct Node* insertNode(struct Node* root, int data) {
    if (root == NULL) {
        return createNode(data);
    }

    if (data < root->data) {
        root->left = insertNode(root->left, data);
    } else if (data > root->data) {
        root->right = insertNode(root->right, data);
    }

    return root;
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
}

// Function to count leaf nodes of the tree
int countLeafNodes(struct Node* root) {
    if (root == NULL)
        return 0;

    struct Stack* stack = createStack(100);
    int leafCount = 0;
    push(stack, root);

    while (!isEmpty(stack)) {
        struct Node* temp = pop(stack);

        if (temp->left == NULL && temp->right == NULL) {
            leafCount++;
        }

        if (temp->right)
            push(stack, temp->right);
        if (temp->left)
            push(stack, temp->left);
    }

    return leafCount;
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
    struct Node* root = NULL;
    int choice, value, count;

    while (1) {
        printf("\nMenu:\n");
        printf("1. Insert Node\n");
        printf("2. Inorder Traversal\n");
        printf("3. Display Number of Leaf Nodes\n");
        printf("4. Mirror Image of Tree\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter value to insert: ");
                scanf("%d", &value);
                root = insertNode(root, value);
                break;
            case 2:
                printf("Inorder Traversal: ");
                inorderTraversal(root);
                printf("\n");
                break;
            case 3:
                count = countLeafNodes(root);
                printf("Number of Leaf Nodes: %d\n", count);
                break;
            case 4:
                printf("Mirror Image of Tree:\n");
                mirrorTree(root);
                printf("Inorder Traversal of Mirror Image: ");
                inorderTraversal(root);
                printf("\n");
                break;
            case 5:
                exit(0);
                break;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }

    return 0;
}
