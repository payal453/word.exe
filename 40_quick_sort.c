#include <stdio.h>
#include <stdlib.h>
int count=0;
struct emp {
    int emp_no;
    char name[10];
    int salary;
};

void swap(struct emp *p, struct emp *p1) {
    struct emp q = *p;
    *p = *p1;
    *p1 = q;
    count++;
}

int partition(struct emp *arr, int low, int high) {
    int pivot = low;
    int i = low + 1;
    int j = high;

    while (i <= j) {
        while (i <= high && arr[i].emp_no <= arr[pivot].emp_no) {
            i++;
        }

        while (arr[j].emp_no > arr[pivot].emp_no) {
            j--;
        }

        if (i < j) {
            swap(&arr[i], &arr[j]);
        }
    }

    swap(&arr[pivot], &arr[j]);

    return j;
}

void quicksort(struct emp *arr, int low, int high) {
    if (low < high) {
        int part = partition(arr, low, high);

        quicksort(arr, low, part - 1);
        quicksort(arr, part + 1, high);
    }
}

int main() {
    int n;
    printf("Enter how many entry do you want to add :");
    scanf("%d",&n);

    struct emp *s = malloc(n * sizeof(struct emp));

    for (int i = 0; i < n; i++) {
        printf("Enter emp_no no: ");
        scanf("%d", &s[i].emp_no);
        printf("Enter Name: ");
        scanf("%s", s[i].name);
        printf("Enter Salary: ");
        scanf("%d", s[i].salary);
    }

    quicksort(s, 0, n - 1);
    printf("Sorted: \n");

    for (int i = 0; i < n; i++) {
        printf("emp_no no: %d\n", s[i].emp_no);
        printf("Name: %s\n", s[i].name);
        printf("Salary: %d\n", s[i].salary);
    }

    printf("\nThe number of swaps performed: %d\n", count);

    free(s);
    return 0;
}
