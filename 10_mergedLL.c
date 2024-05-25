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

// Function to insert a node at the end
void insertAtEnd(struct Node** head, int data) {
    struct Node* newNode = createNode(data);
    if (*head == NULL) {
        *head = newNode;
        return;
    }
    struct Node* temp = *head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newNode;
    newNode->prev = temp;
}

// Function to print the list
void printList(struct Node* node) {
    while (node != NULL) {
        printf("%d ", node->data);
        node = node->next;
    }
    printf("\n");
}

// Function to merge two sorted doubly linked lists
struct Node* mergeLists(struct Node* head1, struct Node* head2) {
    struct Node* mergedHead = NULL;
    struct Node* temp;

    if (head1 == NULL) return head2;
    if (head2 == NULL) return head1;

    if (head1->data <= head2->data) {
        mergedHead = head1;
        head1 = head1->next;
    } else {
        mergedHead = head2;
        head2 = head2->next;
    }

    temp = mergedHead;

    while (head1 != NULL && head2 != NULL) {
        if (head1->data <= head2->data) {
            temp->next = head1;
            head1->prev = temp;
            head1 = head1->next;
        } else {
            temp->next = head2;
            head2->prev = temp;
            head2 = head2->next;
        }
        temp = temp->next;
    }

    if (head1 != NULL) {
        temp->next = head1;
        head1->prev = temp;
    } else if (head2 != NULL) {
        temp->next = head2;
        head2->prev = temp;
    }

    return mergedHead;
}

int main() {
    struct Node* head1 = NULL;
    struct Node* head2 = NULL;
    struct Node* mergedHead = NULL;

    // Create first sorted doubly linked list: 1 <-> 3 <-> 5 <-> 7
    insertAtEnd(&head1, 1);
    insertAtEnd(&head1, 2);
    insertAtEnd(&head1, 5);
    insertAtEnd(&head1, 7);

    // Create second sorted doubly linked list: 2 <-> 4 <-> 6 <-> 8
    insertAtEnd(&head2, 2);
    insertAtEnd(&head2, 4);
    insertAtEnd(&head2, 6);
    insertAtEnd(&head2, 8);

    printf("List 1: ");
    printList(head1);

    printf("List 2: ");
    printList(head2);

    // Merge the two sorted lists
    mergedHead = mergeLists(head1, head2);

    printf("Merged List: ");
    printList(mergedHead);

    return 0;
}
