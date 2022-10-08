#include <stdio.h>
#include <stdlib.h>

typedef struct Linkedtree lt;

struct Linkedtree{
    int data;
    struct Linkedtree *right;
    struct Linkedtree *left;
};

lt *root=NULL;

//Creates new node

lt *createNode(int val){
    lt *temp = (lt*)malloc(sizeof(lt));
    temp->data = val;
    temp->left=NULL;
    temp->right=NULL;
    return temp;
}


void insertNode();
lt* deleteNode();
void searchNodeRecursion(); // uses recursion method for searching
void searchNode(); // uses iterative method for searching
void printInOrder();


int main()
{

    int choice;
    printf("---------------------\n");
    printf("BINARY SEARCH TREE\n");
    printf("---------------------\n");

    do{
    printf("\n____________________________");
    printf("\nCHOOSE AN OPERATION\n(1)INSERT\n(2)DELETE\n(3)SEARCH\n(4)DISPLAY\n(5)IS TREE BST\n(6)EXIT\n");
    printf("____________________________");

    printf("\nENTER YOUR CHOICE :");
    scanf("%d",&choice);

    switch(choice)
    {
        case 1:{
                int val;
                printf("\nENTER A NODE: ");
                scanf(" %d",&val);
                insertNode(val);
               }
               break;

    case 2: {
             int val;
             printf("\nENTER A NODE: ");
             scanf(" %d",&val);
             deleteNode(root,val);
            }
            break;

    case 3: {
             int key;
             printf("\nENTER A KEY FOR SEARCH : ");
             scanf(" %d",&key);
             if(root==NULL) printf("\nBINARY SEARCH TREE EMPTY");
             else{
                //searchNodeRecursion(root,key);
                searchNode(key);
             }
            }
            break;

    case 4: {
                printf("\n----------------------------");
                printf("\nCHOOSE A DISPLAY OPERATION\n\n(1)PRINT TREE\n(2)PRINT INORDER\n(3)PRINT PREORDER\n(4)PRINT POSTORDER\n(5)EXIT\n");
                printf("\n----------------------------");
                int option;
                printf("\nENTER YOUR CHOICE :");
                scanf("%d",&option);
                printf("\n----------------------------");
                switch(option){
                    case 1:
                            break;


                    case 2: printf("\nIN-ORDER TRAVERSAL : ");
                            printInOrder(root);
                            break;

                    case 3: printf("\nPRE-ORDER TRAVERSAL : ");
                            printPreOrder(root);
                            break;

                    case 4: printf("\nPOST-ORDER TRAVERSAL : ");
                            printPostOrder(root);
                            break;

                    case 5: printf("\nEXIT\n");
                            break;

                    default: printf("\nINVALID CHOICE!!\nPLEASE ENTER A VALID OPTION\n");
                }

            }
            break;

    case 5: if(root==NULL) printf("\nBINARY SEARCH TREE EMPTY");
            else{
                if(isBST(root)) printf("\nIT'S A BINARY SEARCH TREE");
                else printf("\nNOT A BINARY SEARCH TREE");
            }
            break;

    case 6: printf("\nEXIT");
            break;

    default: printf("\nINVALID CHOICE!!\nPLEASE ENTER A VALID OPTION\n");

    }
  }while(choice!=6);


    getch();
    return 0;
}

//Print InOrder of the Binary Search Tree

void printInOrder(lt *root){
    if(root==NULL) printf("BINARY SEARCH TREE EMPTY");

    else{
        if(root->left!=NULL)
        printInOrder(root->left);

        printf("%d ",root->data);

        if(root->right!=NULL)
        printInOrder(root->right);

    }

}

// Print PreOrder traversal of the BInary Search Tree

void printPreOrder(lt *root){

    if(root==NULL) printf("BINARY SEARCH TREE EMPTY");

    else{
            printf("%d ",root->data);

            if(root->left!=NULL)
            printPreOrder(root->left);

            if(root->right!=NULL)
            printPreOrder(root->right);
        }

}

//Print PostOrder traversal of the Binary Search Tree

void printPostOrder(lt *root){
    if(root==NULL) printf("BINARY SEARCH TREE EMPTY");

    else{
        if(root->left!=NULL)
        printPostOrder(root->left);

        if(root->right!=NULL)
        printPostOrder(root->right);

        printf("%d ",root->data);
    }


}

int isBST(lt *root){

   static lt *prev=NULL;
   if(root!=NULL){
    if(!isBST(root->left)){
        printf("\nNOT A BINARY SEARCH TREE");
        return 0;
    }
    if(prev!=NULL && root->data<=prev->data){
        printf("\nNOT A BINARY SEARCH TREE");
        return 0;
    }

    prev=root;
    return isBST(root->right);

   }
   else{
    return 1;
   }

}

// Searching a Node with in BST using recursion

void searchNodeRecursion(lt *root, int key){


    if(root!=NULL){

        if(root->data==key){

              printf("\nNODE : %d FOUND",root->data);
              return ;
        }

        else if(key<root->data) searchNodeRecursion(root->left,key);

        else searchNodeRecursion(root->right,key);

    }
    else{
        printf("\nNODE : %d NOT FOUND",key);
    }

}

// Searching a Node with in BST using iteration

void searchNode(int key){

        lt* ptr = root;
        while(ptr!=NULL){

            if(ptr->data==key){

              printf("\nNODE : %d FOUND",ptr->data);
              return ;
            }

            else if(key<ptr->data) ptr = ptr->left;

            else ptr = ptr->right;
        }

        printf("\nNODE : %d NOT FOUND",key);

}

// Insert nodes in the Binary Search Tree

void insertNode(int val){

    if(root==NULL){
        lt *temp = createNode(val);
        root = temp;
    }
    else{
        lt *prev = NULL;
        lt *ptr = root;
        while(ptr!=NULL){
        prev = ptr;
        if(ptr->data==val){

          printf("\nCANNOT INSERT NODE ALREADY EXIST IN BST!!!");
          return ;
        }

        else if(val<ptr->data) ptr = ptr->left;

        else ptr = ptr->right;
        }
        lt *temp = createNode(val);

        if(val<prev->data) prev->left = temp;

        else prev->right = temp;
    }


}

//Searches for InOrder Successor

lt *searchInOrderSuccessor(lt* root){
    root = root->right;
    while(root->left!=NULL){
        root=root->left;
    }
    return root;
}

//Searches for InOrder Predecessor

lt *searchInOrderPredecessor(lt* root){
    root = root->left;
    while(root->right!=NULL){
        root=root->right;
    }
    return root;
}

//Deletes a node  from the Binary Search Tree

lt *deleteNode(lt *root, int val) {

  if(root==NULL){
      printf("\nBINARY SEARCH TREE EMPTY");
      return NULL;
    }


  // finding the node to be deleted
  if (val < root->data)
    root->left = deleteNode(root->left, val);

  else if (val > root->data)
    root->right = deleteNode(root->right, val);

  else {
    // if the node has only one child or no child
    if (root->left == NULL) {
      lt *temp = root->right;
      free(root);
      return temp;
    }
    else if (root->right == NULL) {
      lt *temp = root->left;
      free(root);
      return temp;
    }

    // If the node has two children
    lt *temp = searchInOrderSuccessor(root);
    //lt *temp = searchInOrderPredecessor(root);
    root->data = temp->data;
    root->right = deleteNode(root->right, temp->data);
    //root->left = deleteNode(root->left, temp->data);
  }
  return root;
}






