#include <stdio.h>
#include <stdlib.h>

struct Node{
    int data;
    struct Node* next;
};

struct Node* newNode(int data)
{
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node -> data = data;
    node -> next = NULL;
    return node;
}

void print(struct Node* head)
{
    while(head != NULL)
    {
        printf("%d ",head->data);
        head = head -> next;
    }

    printf("\n");
}

void reverse(struct Node** head)
{
    struct Node *prev = NULL, *current = *head, *nextNode;
    while(current != NULL)
    {
        nextNode = current->next;
        current->next = prev;
        prev = current;
        current = nextNode;
    }
    *head = prev;
}

int main()
{
    struct Node* head = newNode(5);
    head->next = newNode(4);
    head->next->next = newNode(3);
    head->next->next->next = newNode(2);
    head->next->next->next->next = newNode(1);

    printf("Original List: ");
    print(head);

    reverse(&head);

    printf("Reversed List: ");
    print(head);

    // while (head != NULL) {
    //     struct Node* temp = head;
    //     head = head->next;
    //     free(temp);
    // }

    return 0;
}