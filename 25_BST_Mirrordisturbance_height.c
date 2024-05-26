#include <stdio.h>
#include <stdlib.h>

// Structure for a binary tree node
struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};

// Queue structure for level order traversal and calculating height
struct Queue {
    int front, rear, size;
    unsigned capacity;
    struct Node** array;
};

// Function to create a queue
struct Queue* createQueue(unsigned capacity) {
    struct Queue* queue = (struct Queue*)malloc(sizeof(struct Queue));
    queue->capacity = capacity;
    queue->front = queue->size = 0;
    queue->rear = capacity - 1;
    queue->array = (struct Node**)malloc(queue->capacity * sizeof(struct Node*));
    return queue;
}

// Function to check if the queue is full
int isFull(struct Queue* queue) {
    return (queue->size == queue->capacity);
}

// Function to check if the queue is empty
int isEmpty(struct Queue* queue) {
    return (queue->size == 0);
}

// Function to add an item to the queue
void enqueue(struct Queue* queue, struct Node* item) {
    if (isFull(queue))
        return;
    queue->rear = (queue->rear + 1) % queue->capacity;
    queue->array[queue->rear] = item;
    queue->size = queue->size + 1;
}

// Function to remove an item from the queue
struct Node* dequeue(struct Queue* queue) {
    if (isEmpty(queue))
        return NULL;
    struct Node* item = queue->array[queue->front];
    queue->front = (queue->front + 1) % queue->capacity;
    queue->size = queue->size - 1;
    return item;
}

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

// Function to create a mirror image of the BST without disturbing the original tree
struct Node* mirrorTree(struct Node* root) {
    if (root == NULL) {
        return NULL;
    }

    struct Node* newNode = createNode(root->data);
    newNode->left = mirrorTree(root->right);
    newNode->right = mirrorTree(root->left);

    return newNode;
}

// Function to create a mirror image of the BST by modifying the original tree
void mirrorTreeInPlace(struct Node* root) {
    if (root == NULL) {
        return;
    }

    struct Node* temp = root->left;
    root->left = root->right;
    root->right = temp;

    mirrorTreeInPlace(root->left);
    mirrorTreeInPlace(root->right);
}

// Function to print level order traversal of the tree
void printLevelOrder(struct Node* root) {
    if (root == NULL) {
        return;
    }

    struct Queue* queue = createQueue(100);
    enqueue(queue, root);

    while (!isEmpty(queue)) {
        struct Node* node = dequeue(queue);
        printf("%d ", node->data);

        if (node->left) {
            enqueue(queue, node->left);
        }
        if (node->right) {
            enqueue(queue, node->right);
        }
    }
}

// Function to calculate the height of the tree using level order traversal (non-recursive)
int calculateHeight(struct Node* root) {
    if (root == NULL) {
        return 0;
    }

    struct Queue* queue = createQueue(100);
    enqueue(queue, root);
    int height = 0;

    while (1) {
        int nodeCount = queue->size;
        if (nodeCount == 0) {
            return height;
        }

        height++;

        while (nodeCount > 0) {
            struct Node* node = dequeue(queue);
            if (node->left) {
                enqueue(queue, node->left);
            }
            if (node->right) {
                enqueue(queue, node->right);
            }
            nodeCount--;
        }
    }
}

// Driver program
int main() {
    struct Node* root = NULL;
    struct Node* mirrorRoot = NULL;
    int choice, value;

    while (1) {
        printf("\nMenu:\n");
        printf("1. Insert Node\n");
        printf("2. Display Level Order\n");
        printf("3. Display Mirror Image (without disturbing original tree)\n");
        printf("4. Display Mirror Image (in-place)\n");
        printf("5. Calculate Height of the Tree\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter value to insert: ");
                scanf("%d", &value);
                root = insertNode(root, value);
                break;
            case 2:
                printf("Level Order Traversal: ");
                printLevelOrder(root);
                printf("\n");
                break;
            case 3:
                mirrorRoot = mirrorTree(root);
                printf("Mirror Image (without disturbing original tree): ");
                printLevelOrder(mirrorRoot);
                printf("\n");
                break;
            case 4:
                mirrorTreeInPlace(root);
                printf("Mirror Image (in-place): ");
                printLevelOrder(root);
                printf("\n");
                break;
            case 5:
                printf("Height of the Tree: %d\n", calculateHeight(root));
                break;
            case 6:
                exit(0);
                break;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }

    return 0;
}
