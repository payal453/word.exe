#include <stdio.h>
#include <stdlib.h>

#define MAX 100  // Define the maximum size of the array

struct TwoQueues {
    int arr[MAX];
    int front1, rear1;
    int front2, rear2;
};

// Initialize the queues
void initializeQueues(struct TwoQueues* q) {
    q->front1 = q->rear1 = -1;
    q->front2 = q->rear2 = MAX;
}

// Function to add an element to queue 1
void addq1(struct TwoQueues* q, int value) {
    if (q->rear1 < q->rear2 - 1) {
        if (q->front1 == -1) q->front1 = 0;
        q->arr[++q->rear1] = value;
    } else {
        printf("Queue 1 Overflow\n");
    }
}

// Function to add an element to queue 2
void addq2(struct TwoQueues* q, int value) {
    if (q->rear1 < q->rear2 - 1) {
        if (q->front2 == MAX) q->front2 = MAX - 1;
        q->arr[--q->rear2] = value;
    } else {
        printf("Queue 2 Overflow\n");
    }
}

// Function to delete an element from queue 1
int delq1(struct TwoQueues* q) {
    if (q->front1 == -1) {
        printf("Queue 1 Underflow\n");
        return -1;
    } else {
        int value = q->arr[q->front1];
        if (q->front1 == q->rear1) {
            q->front1 = q->rear1 = -1;
        } else {
            q->front1++;
        }
        return value;
    }
}

// Function to delete an element from queue 2
int delq2(struct TwoQueues* q) {
    if (q->front2 == MAX) {
        printf("Queue 2 Underflow\n");
        return -1;
    } else {
        int value = q->arr[q->front2];
        if (q->front2 == q->rear2) {
            q->front2 = q->rear2 = MAX;
        } else {
            q->front2--;
        }
        return value;
    }
}

// Function to display queue 1
void displayQueue1(struct TwoQueues* q) {
    if (q->front1 == -1) {
        printf("Queue 1 is empty\n");
    } else {
        printf("Queue 1: ");
        for (int i = q->front1; i <= q->rear1; i++) {
            printf("%d ", q->arr[i]);
        }
        printf("\n");
    }
}

// Function to display queue 2
void displayQueue2(struct TwoQueues* q) {
    if (q->front2 == MAX) {
        printf("Queue 2 is empty\n");
    } else {
        printf("Queue 2: ");
        for (int i = q->front2; i >= q->rear2; i--) {
            printf("%d ", q->arr[i]);
        }
        printf("\n");
    }
}

int main() {
    struct TwoQueues q;
    initializeQueues(&q);

    // Add elements to Queue 1
    addq1(&q, 10);
    addq1(&q, 20);
    addq1(&q, 30);
    displayQueue1(&q);

    // Add elements to Queue 2
    addq2(&q, 100);
    addq2(&q, 200);
    addq2(&q, 300);
    displayQueue2(&q);

    // Delete elements from Queue 1
    printf("Deleted from Queue 1: %d\n", delq1(&q));
    displayQueue1(&q);

    // Delete elements from Queue 2
    printf("Deleted from Queue 2: %d\n", delq2(&q));
    displayQueue2(&q);

    return 0;
}
