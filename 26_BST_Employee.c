#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure for an employee
struct Employee {
    int emp_id;
    char name[100];
    struct Employee* left;
    struct Employee* right;
};

// Function to create a new employee node
struct Employee* createEmployee(int emp_id, char* name) {
    struct Employee* newEmployee = (struct Employee*)malloc(sizeof(struct Employee));
    newEmployee->emp_id = emp_id;
    strcpy(newEmployee->name, name);
    newEmployee->left = newEmployee->right = NULL;
    return newEmployee;
}

// Function to insert an employee into the BST
struct Employee* insertEmployee(struct Employee* root, int emp_id, char* name) {
    if (root == NULL) {
        return createEmployee(emp_id, name);
    }

    if (emp_id < root->emp_id) {
        root->left = insertEmployee(root->left, emp_id, name);
    } else if (emp_id > root->emp_id) {
        root->right = insertEmployee(root->right, emp_id, name);
    }

    return root;
}

// Function to search for an employee by emp_id
struct Employee* searchEmployee(struct Employee* root, int emp_id) {
    if (root == NULL || root->emp_id == emp_id) {
        return root;
    }

    if (emp_id < root->emp_id) {
        return searchEmployee(root->left, emp_id);
    }

    return searchEmployee(root->right, emp_id);
}

// Function to perform inorder traversal and print the employees in ascending order of emp_id
void inorderTraversal(struct Employee* root) {
    if (root != NULL) {
        inorderTraversal(root->left);
        printf("Employee ID: %d, Name: %s\n", root->emp_id, root->name);
        inorderTraversal(root->right);
    }
}

// Driver program
int main() {
    struct Employee* root = NULL;
    int choice, emp_id;
    char name[100];

    while (1) {
        printf("\nMenu:\n");
        printf("1. Insert Employee\n");
        printf("2. Search Employee\n");
        printf("3. Display Employees (sorted by Employee ID)\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter Employee ID: ");
                scanf("%d", &emp_id);
                printf("Enter Employee Name: ");
                scanf(" %[^\n]", name);  // Read string with spaces
                root = insertEmployee(root, emp_id, name);
                break;
            case 2:
                printf("Enter Employee ID to search: ");
                scanf("%d", &emp_id);
                struct Employee* employee = searchEmployee(root, emp_id);
                if (employee != NULL) {
                    printf("Employee found! ID: %d, Name: %s\n", employee->emp_id, employee->name);
                } else {
                    printf("Employee not found!\n");
                }
                break;
            case 3:
                printf("Employees (sorted by Employee ID):\n");
                inorderTraversal(root);
                break;
            case 4:
                exit(0);
                break;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }

    return 0;
}
