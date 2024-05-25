#include<stdio.h>
int count = 0;
void insert(int item, int arr[], int n, int prime){
    int h1=item%n,i=1;
    int key=h1;
    int h2=prime-(item%prime);
    if(arr[h1]==-1){
        arr[h1]=item;
    }
    else{
        count++;
        while(1){
            key=(h1+i*h2)%n;
            if(arr[key]==-1){
                arr[key]=item;
                break;
            }
            else{
                i++;
            }
        }
    }
}
void display(int arr[], int n){
    printf("\nHash Table\n");
    for(int i=0; i<n; i++){
        printf("%d\t%d\n",i,arr[i]);
    }
    printf("Total number of collisions: %d\n", count); 
}

void main(){
    int n,c,item,prime;
    printf("Enter size of hash table : ");
    scanf("%d",&n);
    printf("Enter prime no. : ");
    scanf("%d",&prime); 
    int arr[n];
    for(int i=0; i<n; i++){
        arr[i]=-1;
    }
    printf("1.Insert, 2.Display\n");
    while(c!=2){
        printf("Enter choice : ");
        scanf("%d",&c);
        switch(c){
        case 1:
            printf("Enter item to insert : ");
            scanf("%d",&item);
            insert(item,arr,n,prime);
            break;
        case 2:
            display(arr,n);
            break;
        }
    }
}
