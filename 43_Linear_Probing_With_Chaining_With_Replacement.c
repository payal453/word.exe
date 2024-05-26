#include <stdio.h>
#include <stdlib.h>
int count = 0;
 void insert(int item, int arr[], int chain[], int n) {
    int key = item % n, origKey = key;
    if (arr[key] == -1) {
        // If the slot is empty, directly insert the item
        arr[key] = item;
    } else {
        int startKey = key; // Remember where we started to avoid infinite loops
        while (1) {
            if (arr[key] == -1) {
                // Found an empty slot; insert here
                arr[key] = item;
                break;
            } else if (item > arr[key]) {
                // Replace if new item is greater
                int oldItem = arr[key];
                arr[key] = item; // Place the new item
                item = oldItem; // Prepare to re-insert the old item
                count++;
            }
            origKey = key; // Move the origin key to current
            key = (key + 1) % n; // Move to the next slot
            if (key == startKey) {
                printf("Hash table is full or cannot place the item\n");
                break; // If we come full circle, stop trying to insert
            }
        }
    }
 }
 void display(int arr[], int n) {
    printf("\nHash Table\n");
    for (int i = 0; i < n; i++) {
        printf("%d -> %d\n", i, arr[i]);
    }
    printf("Total number of collisions: %d\n", count); 
 }
 int main() {
    int n, c, item;
    printf("Enter size of hash table: ");
    scanf("%d", &n);
    int arr[n];
    for (int i = 0; i < n; i++) {
        arr[i] = -1;
    }
    printf("1.Insert, 2.Display\n");
    do {
        printf("Enter choice: ");
        scanf("%d", &c);
        switch (c) {
            case 1:
                printf("Enter item to insert: ");
                scanf("%d", &item);
                insert(item, arr, NULL, n); // Ignore chain
                break;
            case 2:
                display(arr, n);
                break;
        }
    } while (c != 2); // Continue until 'Display' is chosen
    return 0;
 }
