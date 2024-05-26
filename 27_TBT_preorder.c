#include<stdio.h>
#include<stdlib.h>

struct node {
   int data;
   struct node *left,*right;
   int lbit,rbit;
};
struct node *create(struct node *root,struct node *newnode);
struct node *insert(struct node *root, int data);

struct node *head=NULL;   


struct node *insert(struct node *root, int data)
{
    
    struct node *newnode;
 
    newnode = (struct node*)malloc(sizeof(struct node));
    newnode->data = data;
    newnode->rbit = newnode->lbit = 0;
    newnode->left = newnode->right = NULL;

    if(root==NULL)
    {
        root = newnode;
        head = (struct node*)malloc(sizeof(struct node));
        head->data = 100;
        head->rbit = 1;
        head->right = head;
        head->left = newnode;
        head->lbit = 1;
        root->right  = root->left= head;
        return root;
    }
    else
    {
        root = create(root,newnode);
    }
   return root;
}

struct node *create(struct node *root,struct node *newnode)
{
     if(root->data >newnode-> data)
     {
        if(root->lbit==0)
        {

            newnode->right = root;
            newnode->left = root->left;
            root->left = newnode;
            root->lbit = 1;
        }else
        {
            root->left = create(root->left,newnode);
        }
     }
     if(root->data < newnode->data)
     {
        if(root->rbit==0)
        {
            newnode ->left= root;
            newnode->right = root->right;
            root->right = newnode;
            root ->rbit = 1;

        }else
        {
            root->right = create(root->right,newnode);
        }
     }
     return root;


}


void inOrderTraversal(struct node* root) {
      struct node* current = root;

    // Find the leftmost node
    while (current->lbit == 1)
       { current = current->left;}

    // Traverse the tree in inorder manner
    while (current != head) {
        printf("%d ", current->data);

        // If right pointer is threaded, move to its successo
        if (current->rbit == 0)
            current = current->right;
        else {
            current = current->right;
            // Find the leftmost node of the right subtree
            while (current != NULL && current->lbit == 1)
                current = current->left;
        }
    }
}

void inorder(struct node *root)
{
    struct node *temp = root;
    while(temp->lbit==1)
    {
        temp = temp->left;
    }
    while(temp!=head)
     {
        printf("%d ",temp->data);
        if(temp->rbit==0)
        {
            temp = temp->right;
        }
        else
        {
            temp = temp->right;
            while(temp!=head && temp->lbit==1)
            {
                temp = temp->left;
            }
        }
     }
}

void preOrderTraversal(struct node* root) {
    struct node* current = root;

    while (current != head) {
        // Print the current node
        printf("%d ", current->data);
        // If left pointer is threaded, move to its successor
        if (current->lbit == 1)
            current = current->left;
        else if (current->rbit == 1)
                current = current->right;
        else if (current->rbit == 0)
            {    while(current->rbit == 0)
                {
                    current = current->right;
                }  
            
                current = current->right;}
        }
    }

    void preorder(struct node* root)
    {
        struct node *temp =root;
        while(temp!=head)
        {
            printf("%d ",temp->data);
            if(temp->lbit==1)
            {
                temp = temp->left;
            }
            else if(temp->rbit==1)
            {
                temp = temp->right;
            }
            else if(temp->rbit==0)
            {
                while(temp->rbit==0)
                {
                    temp = temp->right;
                }
                temp = temp->right;
            }
        }
    }

    void postorder(struct node* root) {
     struct node* current = root;
    struct node* prev = NULL;

    // Find the leftmost node
    while (current->lbit == 1)
        current = current->left;

    // Traverse the tree in postorder manner
    while (current != NULL) {
        // If right pointer is threaded, move to its predecessor
        if (current->rbit == 1 || current->right == prev) {
            printf("%d ", current->data);
            prev = current;
            current = current->right;
        } else {
            // Move to the right child
            if (current->right != NULL)
                current = current->right;
            // Move to the leftmost node of the right subtree
            while (current->lbit == 0 && current->left != prev)
                current = current->left;
            if (current->left != prev)
                current = current->left;
        }
    }
}

int main() {
    struct node *root = NULL;
    int n;
    int data;
    printf("Enter size : ");
    scanf("%d",&n);
    for(int i=0;i<n;i++)
    {   printf("Enter data : ");
        scanf("%d",&data);
      root = insert(root,data);
    }
   
    inorder(root);
    printf("\n");
    preorder(root);

}