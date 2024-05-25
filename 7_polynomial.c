#include <stdio.h>
#include <stdlib.h>

struct poly{
    int cos;
    int exp;
    struct poly *next;
};

struct poly *accept(int n) {
    struct poly *head = NULL;
    struct poly *curr = NULL;

    printf("Enter the coefficient, exponent pairs in descending order of exponent:\n");
    for (int i = 0; i < n; i++) {
        struct poly *p = (struct poly *)malloc(sizeof(struct poly));
        if (p == NULL) {
            printf("Memory allocation failed.\n");
            exit(EXIT_FAILURE);
        }

        printf("Term %d: ", i + 1);
        scanf("%d %d", &p->cos, &p->exp);

        if (curr != NULL) {
            curr->next = p;
        } else {
            head = p;
        }
        curr = p;
    }
    
    if (curr != NULL) {
        curr->next = NULL;
    }

    return head;
}

struct poly *add(struct poly *p1, struct poly *p2){
    struct poly *p3 = NULL;
    struct poly *head = p3;

    while(p1 != NULL && p2 != NULL){
        if(head == NULL){    
            p3 = (struct poly *)malloc(sizeof(struct poly));
            head = p3;
            p3->next = NULL;
        }
        else{
            p3->next = (struct poly *)malloc(sizeof(struct poly));
            p3 = p3->next;
            p3->next = NULL;
        }
            if(p1->exp == p2->exp){
                p3->cos = p1->cos + p2->cos;
                p3->exp = p1->exp;
                p1 = p1->next;
                p2 = p2->next;
            }
            else if(p1->exp > p2->exp){
                p3->exp = p1->exp;
                p3->cos = p1->cos;
                p1 = p1->next;
            }
            else{
                p3->exp = p2->exp;
                p3->cos = p2->cos;
                p2 = p2->next;
            }
    }

    while(p1 != NULL){
        p3->next = (struct poly *)malloc(sizeof(struct poly));
        p3 = p3->next;
        p3->next = NULL;
        p3->cos = p1->cos;
        p3->exp = p1->exp;
        p1 = p1->next;
    }

    while(p2 != NULL){
        p3->next = (struct poly *)malloc(sizeof(struct poly));
        p3 = p3->next;
        p3->next = NULL;
        p3->cos = p2->cos;
        p3->exp = p2->exp;
        p2 = p2->next;
    }
    return head;
}

void display(struct poly *p){
    printf("Your polynomial expression is : ");
    while (p != NULL){
        printf("%dx^%d", p->cos, p->exp);
        p = p->next;
        if(p != NULL){
            printf("+");
        }
    }
    printf("\n");
    free(p);
}

int main(){
    struct poly *poly1, *poly2 , *poly3;
    int a, b;

    printf("No of terms for poly1 and poly2: ");
    scanf("%d %d", &a, &b);

    poly1 = accept(a);
    poly2 = accept(b);

    display(poly1);
    display(poly2);

    poly3 = add(poly1,poly2);

    display(poly3);

    free(poly1);
    free(poly2);
    free(poly3);
    return 0;
}
