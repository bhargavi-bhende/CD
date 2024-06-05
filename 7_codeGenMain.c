#include <stdio.h>
#include <stdlib.h>

/* We will implement DAG as a Strictly Binary Tree where each node has zero or two children */

struct bin_tree {
    char data;
    int label;
    struct bin_tree *right, *left;
};
typedef struct bin_tree node;

/* R is a stack for storing registers */
int R[10];
int top;

/* op will be used for opcode name w.r.t. arithmetic operator e.g., ADD for + */
char *op;

/* Function to add nodes to the tree (DAG) */
void insertnode(node **tree, char val) {
    node *temp = NULL;

    if (!(*tree)) {
        temp = (node *)malloc(sizeof(node));
        temp->left = temp->right = NULL;
        temp->data = val;
        temp->label = -1;
        *tree = temp;
    }
}

void insert(node **tree, char val) {
    char l, r;
    int numofchildren;

    insertnode(tree, val);

    printf("\nEnter number of children of %c: ", val);
    scanf("%d", &numofchildren);

    if (numofchildren == 2) {
        printf("\nEnter Left Child of %c: ", val);
        scanf(" %c", &l);
        insertnode(&(*tree)->left, l);

        printf("\nEnter Right Child of %c: ", val);
        scanf(" %c", &r);
        insertnode(&(*tree)->right, r);

        insert(&(*tree)->left, l);
        insert(&(*tree)->right, r);
    }
}

/* Function to find the label of leaf nodes of tree (DAG) */
void findleafnodelabel(node *tree, int val) {
    if (tree->left != NULL && tree->right != NULL) {
        findleafnodelabel(tree->left, 1);
        findleafnodelabel(tree->right, 0);
    } else {
        tree->label = val;
    }
}

/* Function to find the label of interior nodes of tree (DAG) */
void findinteriornodelabel(node *tree) {
    if (tree->left->label == -1) {
        findinteriornodelabel(tree->left);
    } else if (tree->right->label == -1) {
        findinteriornodelabel(tree->right);
    } else {
        if (tree->left != NULL && tree->right != NULL) {
            if (tree->left->label == tree->right->label) {
                tree->label = (tree->left->label) + 1;
            } else {
                tree->label = (tree->left->label > tree->right->label) ? tree->left->label : tree->right->label;
            }
        }
    }
}

/* Function to print inorder traversal of nodes with their labels */
void print_inorder(node *tree) {
    if (tree) {
        print_inorder(tree->left);
        printf("%c with Label %d\n", tree->data, tree->label);
        print_inorder(tree->right);
    }
}

/* Function to swap the top and second top elements of the Register stack R */
void swap() {
    int temp;
    temp = R[top];
    R[top] = R[top - 1];
    R[top - 1] = temp;
}

/* Function to remove and return the topmost element of the stack */
int pop() {
    int temp = R[top];
    top--;
    return temp;
}

/* Function to increment top by one and insert element at the top position of the Register stack */
void push(int temp) {
    top++;
    R[top] = temp;
}

/* Function to get the opcode name w.r.t. the arithmetic operator */
char *nameofoperation(char temp) {
    switch (temp) {
        case '+': return "ADD";
        case '-': return "SUB";
        case '*': return "MUL";
        case '/': return "DIV";
        default: return "";
    }
}

/* Function to generate Assembly code w.r.t. labels of the tree (DAG) */
void gencode(node *tree) {
    if (tree->left != NULL && tree->right != NULL) {
        if (tree->left->label == 1 && tree->right->label == 0 && tree->left->left == NULL && tree->left->right == NULL && tree->right->left == NULL && tree->right->right == NULL) {
            printf("MOV %c, R[%d]\n", tree->left->data, R[top]);
            op = nameofoperation(tree->data);
            printf("%s %c, R[%d]\n", op, tree->right->data, R[top]);
        } else if (tree->left->label >= 1 && tree->right->label == 0) {
            gencode(tree->left);
            op = nameofoperation(tree->data);
            printf("%s %c, R[%d]\n", op, tree->right->data, R[top]);
        } else if (tree->left->label < tree->right->label) {
            int temp;
            swap();
            gencode(tree->right);
            temp = pop();
            gencode(tree->left);
            push(temp);
            swap();
            op = nameofoperation(tree->data);
            printf("%s R[%d], R[%d]\n", op, R[top - 1], R[top]);
        } else if (tree->left->label >= tree->right->label) {
            int temp;
            gencode(tree->left);
            temp = pop();
            gencode(tree->right);
            push(temp);
            op = nameofoperation(tree->data);
            printf("%s R[%d], R[%d]\n", op, R[top - 1], R[top]);
        }
    } else if (tree->left == NULL && tree->right == NULL && tree->label == 1) {
        printf("MOV %c, R[%d]\n", tree->data, R[top]);
    }
}

/* Function to free the memory allocated for the tree (DAG) */
void deltree(node *tree) {
    if (tree) {
        deltree(tree->left);
        deltree(tree->right);
        free(tree);
    }
}

/* Program execution will start from the main() function */
int main() {
    node *root;
    root = NULL;
    char val;
    int i, temp;

    /* Inserting nodes into the tree (DAG) */
    printf("\nEnter root of the tree: ");
    scanf(" %c", &val);

    insert(&root, val);

    /* Finding Labels of Leaf nodes */
    findleafnodelabel(root, 1);

    /* Finding Labels of Interior nodes */
    while (root->label == -1)
        findinteriornodelabel(root);

    /* Value of top = index of the topmost element of stack R = label of Root of the tree (DAG) minus one */
    top = root->label - 1;

    /* Allocating Stack Registers */
    temp = top;
    for (i = 0; i <= top; i++) {
        R[i] = temp;
        temp--;
    }

    /* Printing inorder traversal of nodes of the tree (DAG) */
    printf("\nInorder Display:\n");
    print_inorder(root);

    /* Printing assembly code w.r.t. labels of the tree (DAG) */
    printf("\nAssembly Code:\n");
    gencode(root);

    /* Deleting all nodes of the tree */
    deltree(root);

    return 0;
}

//(a+b) - (e - (c+d))
//(a*b) + c
