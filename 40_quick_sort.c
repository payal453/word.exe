#include <stdio.h>
#include <stdlib.h>

int count = 0;

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
    int pivot = arr[low].emp_no;  // Use the value at arr[low] as pivot
    int i = low + 1;
    int j = high;

    while (i <= j) {
        while (i <= high && arr[i].emp_no <= pivot) {
            i++;
        }

        while (arr[j].emp_no > pivot) {
            j--;
        }

        if (i < j) {
            swap(&arr[i], &arr[j]);
        }
    }

    swap(&arr[low], &arr[j]);

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
    printf("Enter how many entries do you want to add: ");
    scanf("%d", &n);

    struct emp *s = malloc(n * sizeof(struct emp));

    for (int i = 0; i < n; i++) {
        printf("\nEnter %d Employe's details :\n",i+1);
        printf("Enter emp_no: ");
        scanf("%d", &s[i].emp_no);
        printf("Enter Name: ");
        scanf("%s", s[i].name);
        printf("Enter Salary: ");
        scanf("%d", &s[i].salary);
    }

    quicksort(s, 0, n - 1);

    printf("\nSorted details :\n");

    for (int i = 0; i < n; i++) {
        printf("emp_no: %d", s[i].emp_no);
        printf("\tName: %s", s[i].name);
        printf("\tSalary: %d", s[i].salary);
        printf("\n");
    }

    printf("\nThe number of swaps performed: %d\n", count);

    free(s);
    return 0;
}
