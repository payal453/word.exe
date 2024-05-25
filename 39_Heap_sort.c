#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int n;
int count = 0;

struct stud {
    int roll;
    char name[20];
    int marks;
};

void swap(struct stud *a, struct stud *b) {
    struct stud temp = *a;
    *a = *b;
    *b = temp;
    count++;
}

void heapify(struct stud arr[], int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left].roll > arr[largest].roll)
        largest = left;

    if (right < n && arr[right].roll > arr[largest].roll)
        largest = right;

    if (largest != i) {
        swap(&arr[i], &arr[largest]);
        heapify(arr, n, largest);
    }
}

void sort(struct stud arr[]) {
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(arr, n, i);
    }

    for (int i = n - 1; i >= 0; i--) {
        swap(&arr[0], &arr[i]);
        heapify(arr, i, 0);
    }
}

int main() {
    printf("Enter how many entries you want to add: ");
    scanf("%d", &n);

    struct stud *s = malloc(n * sizeof(struct stud));
    
    if (s == NULL) {
        printf("Memory allocation failed");
        return 1;
    }

    printf("Enter the roll no, name, and marks:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &s[i].roll);
        scanf("%s", s[i].name); 
        scanf("%d", &s[i].marks);
    }

    printf("Array before sorting:\n");
    for (int i = 0; i < n; i++) {
        printf("Roll no: %d, Name: %s, Marks: %d\n", s[i].roll, s[i].name, s[i].marks);
    }

    sort(s);

    printf("\nArray after sorting:\n");
    for (int i = 0; i < n; i++) {
        printf("Roll no: %d, Name: %s, Marks: %d\n", s[i].roll, s[i].name, s[i].marks);
    }

    printf("\nThe number of swaps performed: %d\n", count);

    free(s);
    return 0;
}
