#include <stdio.h>

void findSwappedElements(int A[], int n, int *x, int *y) {
    int i;
    *x = -1;
    *y = -1;

    // Traverse the array to find the two positions where order is violated
    for (i = 0; i < n - 1; i++) {
        if (A[i] > A[i + 1]) {
            if (*x == -1) {
                // First violation
                *x = i;
            } else {
                // Second violation
                *y = i + 1;
                break;
            }
        }
    }

    if (*y == -1) {
        *y = *x + 1;
    }
}

int main() {
    int s;
    printf("\nEnter the size of an array : ");
    scanf("%d",&s);
    int A[s];
    printf("\nEnter the sorted array where two of it's elements are swapped : ");
    for(int i=0;i<s;i++){
        scanf("%d",&A[i]);
    }
    int n = sizeof(A) / sizeof(A[0]);
    int x, y;

    findSwappedElements(A, n, &x, &y);

    printf("Swapped elements are %d and %d at positions %d and %d\n", A[x], A[y], x, y);

    return 0;
}
