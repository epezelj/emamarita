#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct _binaryTree *Position;
typedef struct _binaryTree{

    int number;
    Position left;
    Position right;

}binaryTree;

int Choose(Position root);
Position Insert(Position root, int number);
Position AddNumber(int number);
Position Preorder(Position root);
Position Inorder(Position root);
Position Postorder(Position root);
Position Levelorder(Position root);
Position DeleteNumber(Position root, int number);
bool FindNumber(Position root, int number);



int main(){

    binaryTree root = {.number = 0, .left = NULL, .right = NULL};

    Choose(&root);
}

int Choose(Position root){

    int number = 0, choice = 0, check = 0;
    Position check_address;
    
     while(1)
    {
        printf("Izaberite:\n1-insert number\n2-preorder\n3-inorder\n4-postorder\n5-level order\n6-delete element\n7-find element\n");
        scanf("%d", &choice);

        if(choice == 1)
        {
            printf("Unesite broj: ");
            scanf("%d", &number);

            if(check == 0)
            {
                root->number = number;
                check = 1;
            }
            else
            {
                check_address = Insert(root, number);
                if(check_address != root)
                    return -1;
            }
        }

        if(choice == 2)
        {
            printf("Preorder: ");
            check_address = Preorder(root);

            if(check_address != root)
                    return -1;

            printf("\n");
        }
            
        if(choice == 3)
        {
            printf("Inorder: ");
            check_address = Inorder(root);

            if(check_address != root)
                    return -1;

            printf("\n");
        }

        if(choice == 4)
        {
            printf("Postorder: ");
            check_address = Postorder(root);

            if(check_address != root)
                    return -1;

            printf("\n");
        }

        if(choice == 5)
        {
            printf("Levelorder: ");
            Levelorder(root);

            printf("\n");
        }

        if(choice == 6)
        {
            printf("koji broj zelite izbrisati: ");
            scanf("%d", &number);
            DeleteNumber(root, number);
            Preorder(root);

        }

        if(choice == 7)
        {
            printf("Unesite broj: ");
            scanf("%d", &number);

            if(FindNumber(root, number) == true)
                printf("Broj %d nalazi se u stablu\n", number);

            else 
                printf("Broj %d ne nalazi se u stablu\n", number);
    
        }

    }

}
Position Insert(Position root, int number){

    if(root == NULL)
        root = AddNumber(number);

    else if(number <= root->number)
        root->left = Insert(root->left, number);

    else if(number > root->number)
        root->right = Insert(root->right, number);

    return root;
}

Position AddNumber(int number){

    Position newNumber = (Position)malloc(sizeof(binaryTree));

    newNumber->number = number;
    newNumber->left = NULL;
    newNumber->right = NULL;
    
    return newNumber;
}

Position Preorder(Position root){

    if(root != NULL)
    {
        printf("%d ", root->number);
        Preorder(root->left);
        Preorder(root->right);
    }
    return root;
}

Position Inorder(Position root){

    if(root != NULL)
    {
        Inorder(root->left);
        printf("%d ", root->number);
        Inorder(root->right);
    }

    return root;

}

Position Postorder(Position root){

    if(root != NULL)
    {
        Postorder(root->left);
        Postorder(root->right);
        printf("%d ", root->number);
    }

    return root;

}

Position Levelorder(Position root){

    if(root == NULL)
        return 0;

    Position queue[1000];
    int currPos = 0, queueSize = 0;

    queue[queueSize++] = root;

    while(currPos != queueSize)
    {
        Position current = queue[currPos++];

        printf(" %d ", current->number);

        if(current->left  != NULL)
            queue[queueSize++] = current->left;

        if(current->right != NULL)
            queue[queueSize++] = current->right;

    }
    return 0;
}

bool FindNumber(Position root, int number){

    bool istrue = false;

    if(root != NULL)
    {
        if(istrue == true)
            return istrue;

        else
        {
            if(number < root->number)
                istrue = FindNumber(root->left, number);

            else if(number > root->number)
                istrue = FindNumber(root->right, number);

            else 
                istrue = true;
        }

    }
    return istrue;

} 

Position DeleteNumber(Position root, int number){

    Position temp;
    Position new;

    if(root == NULL)
        return root;

    if(number < root->number)
        root->left = DeleteNumber(root->left, number);
    
    else if (number > root->number)
        root->right = DeleteNumber(root->right, number);

    else 
    {
        if(root->right == NULL && root->left == NULL)
        {
            free(root);
            return NULL;

        }
        else if(root->left == NULL && root->right != NULL)
        {
            temp = root->right;
            free(root);
            return temp;

        }
        else if(root->right == NULL && root->left != NULL)
        {
            temp = root->left;
            free(root);
            return temp;

        }
        else
        {
            temp = root->right;

            while(temp->left != NULL)
                temp = temp->left;

            root->number = temp->number;
            root->right = DeleteNumber(root->right, temp->number);
        }

    }
    return root;
}