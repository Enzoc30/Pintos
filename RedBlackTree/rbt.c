#include <stdio.h>
#include <stdlib.h>

enum Color { RED, BLACK};


struct nodeRedBlack
{
    int data;
    struct nodeRedBlack *left;
    struct nodeRedBlack *right;
    enum Color color;
    struct nodeRedBlack *parent;
};

struct Value{
    struct nodeRedBlack elem;    
    int priority;
};


struct RedBlackTree
{
    struct nodeRedBlack *root;
    struct nodeRedBlack nill;
    int count;
};

void createNode(struct RedBlackTree* tree,struct nodeRedBlack *newNode)
{
    newNode->data = -1;
    newNode->parent = &tree->nill;
    newNode->left = &tree->nill;
    newNode->right = &tree->nill;
    newNode->color = BLACK;
}

void createNodeRedBlackTree(struct RedBlackTree *tree, struct nodeRedBlack *node)
{
    node->left = &tree->nill;
    node->right = &tree->nill;
    node->data = -1;
    node->parent = &tree->nill;
    node->color = BLACK;
}

void rbt_init(struct RedBlackTree *tree){   
    createNode(tree,&tree->nill);
    //tree->nill.color = WHITE;
    tree->nill.color = BLACK;
    tree->root = &tree->nill;
    tree->count = 0;
}

void value_init(struct RedBlackTree* tree ,  struct Value *p, int data){
    createNode(tree , &(p->elem)); 
    p->priority = data; 
    (p->elem.data) = data;
}

void leftRotate(struct RedBlackTree *tree, struct nodeRedBlack *x){
    struct nodeRedBlack *y = x->right;
    x->right = y->left;

    if (y->left != &tree->nill)
    {
        y->left->parent = x;
    }

    y->parent = x->parent;

    if (x->parent == &tree->nill)
    {
        tree->root = y;
    }
    else if (x == x->parent->left)
    {
        x->parent->left = y;
    }
    else
    {
        x->parent->right = y;
    }

    y->left = x;
    x->parent = y;
}

void rightRotate(struct RedBlackTree *tree, struct nodeRedBlack *y){
    struct nodeRedBlack *x = y->left;
    y->left = x->right;

    if (x->right != &tree->nill)
    {
        x->right->parent = y;
    }

    x->parent = y->parent;

    if (y->parent == &tree->nill)
    {
        tree->root = x;
    }
    else if (y == y->parent->left)
    {
        y->parent->left = x;
    }
    else
    {
        y->parent->right = x;
    }

    x->right = y;
    y->parent = x;
}

void insertFixup(struct RedBlackTree *tree, struct nodeRedBlack *z){
    while (z->parent->color == RED)
    {
        if (z->parent == z->parent->parent->left)
        {
            struct nodeRedBlack *y = z->parent->parent->right;
            if (y->color == RED)
            {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            }
            else
            {
                if (z == z->parent->right)
                {
                    z = z->parent;
                    leftRotate(tree, z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                rightRotate(tree, z->parent->parent);
            }
        }
        else
        {
            struct nodeRedBlack *y = z->parent->parent->left;
            if (y->color == RED)
            {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            }
            else
            {
                if (z == z->parent->left)
                {
                    z = z->parent;
                    rightRotate(tree, z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                leftRotate(tree, z->parent->parent);
            }
        }
    }
    tree->root->color = BLACK;
}

void insert(struct RedBlackTree *tree, struct nodeRedBlack *newNode){
    struct nodeRedBlack *y = &tree->nill;
    struct nodeRedBlack *x = tree->root;
    tree->count = tree->count + 1;
    while (x != &tree->nill){
        y = x;
        if (newNode->data < x->data){
            x = x->left;
        }
        else {
            x = x->right;
        }
    }

    newNode->parent = y;

    if (y == &tree->nill){
        tree->root = newNode;
    }
    else if (newNode->data < y->data){
        y->left = newNode;
    }
    else{
        y->right = newNode;
    }

    newNode->left = &tree->nill;
    newNode->right = &tree->nill;
    newNode->color = RED;

    insertFixup(tree, newNode);
}

void printTree(struct RedBlackTree* tree,struct nodeRedBlack *root, int level)
{
    if (root != &tree->nill){
        printTree(tree,root->right, level + 1);
        for (int i = 0; i < level; i++){
            printf("\t");
        }

        printf("(%d, %s)\n", root->data, root->color == RED ? "RED" : "BLACK");

    /*
    if (root != NULL && root->color == RED)
    {
        printf("(%d, %s)\n", root->data, "RED");
    }
    else if (root != NULL && root->color == BLACK)
    {
        printf("(%d, %s)\n", root->data, "BLACK");
    }
    else
    {
        // Handle the case when the color is "White"
        printf("(%d, %s)\n", root->data, "WHITE");
    }
    */
        printTree(tree ,root->left, level + 1);
    }
}

struct nodeRedBlack *searchNode(struct RedBlackTree* tree ,struct nodeRedBlack *node, int data){
    // Can be change, there are two condition, can be one
    if (node == &tree->nill || node->data == data){
        return node;
    }
    if (data < node->data){
        return searchNode(tree,node->left, data);
    }

    return searchNode(tree,node->right, data);
}

struct nodeRedBlack *search(struct RedBlackTree *tree, int data){
    return searchNode(tree,tree->root, data);
}

void fixDeletion(struct RedBlackTree *tree, struct nodeRedBlack *x) {
    struct nodeRedBlack *w;

    while ( x != &tree->nill || x != tree->root && x->color == BLACK) {
        if (x == x->parent->left) {
            w = x->parent->right;

            if (w->color == RED) {
                w->color = BLACK;
                x->parent->color = RED;
                leftRotate(tree, x->parent);
                w = x->parent->right;
            }

            if (w->left->color == BLACK && w->right->color == BLACK) {
                w->color = RED;
                x = x->parent;
            } else {
                if (w->right->color == BLACK) {
                    w->left->color = BLACK;
                    w->color = RED;
                    rightRotate(tree, w);
                    w = x->parent->right;
                }

                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->right->color = BLACK;
                leftRotate(tree, x->parent);
                x = tree->root; 
            }
        } else {
            w = x->parent->left;

            if (w->color == RED) {
                w->color = BLACK;
                x->parent->color = RED;
                rightRotate(tree, x->parent);
                w = x->parent->left;
            }

            if ( w->right->color == BLACK && w->left->color == BLACK) {
                w->color = RED;
                x = x->parent;
            } else {
                if (w->left->color == BLACK) {
                    w->right->color = BLACK;
                    w->color = RED;
                    leftRotate(tree, w);
                    w = x->parent->left;
                }

                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->left->color = BLACK;
                rightRotate(tree, x->parent);
                x = tree->root; 
            }
        }
    }
    x->color = BLACK;
}

struct nodeRedBlack *findMinimum(struct RedBlackTree *tree ,struct nodeRedBlack *node)
{
    while (node->left != &tree->nill)
    {
        node = node->left;
    }
    return node;
}

struct nodeRedBlack *findMaximum(struct nodeRedBlack *node)
{
    while (node->right != NULL)
    {
        node = node->right;
    }
    return node;
}

void transplant(struct RedBlackTree *tree, struct nodeRedBlack *u, struct nodeRedBlack *v)
{
    if (u->parent == &tree->nill){
        tree->root = v;
    }else if (u == u->parent->left){
        u->parent->left = v;
    }else{
        u->parent->right = v;
    }
    v->parent = u->parent;
}

void deleteNode(struct RedBlackTree *tree, struct nodeRedBlack *z)
{
    struct nodeRedBlack *y = z;
    struct nodeRedBlack *x;
    enum Color yOriginalColor = y->color;

    if (z->left == &tree->nill)
    {
        x = z->right;
        transplant(tree,     z, z->right);
    }
    else if (z->right == &tree->nill)
    {
        x = z->left;
        transplant(tree, z, z->left);
    }
    else
    {
        y = findMinimum(tree,z->right);
        yOriginalColor = y->color;
        x = y->right;

        if (y->parent == z)
        {
            x->parent = y;
        }
        else
        {
            transplant(tree, y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }

        transplant(tree, z, y);
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;
    }

    if (yOriginalColor == BLACK){
        fixDeletion(tree, x);
    }
}

void delete(struct RedBlackTree *tree, int data){
    struct nodeRedBlack *result = searchNode(tree,tree->root, data);
    if (result != &tree->nill){
        deleteNode(tree, result);
        tree->count = tree->count - 1;
    }
}


int main(){
    struct RedBlackTree tree;
    rbt_init(&tree);


    // Crear threads para las inserciones
    int values[] = {10, 12, 3, 24, 55, 66, 198,654,7,2,16,874,35,849,431,135,877 ,18, 92, 86, 49};
    int numValues = sizeof(values) / sizeof(values[0]);

    struct Value ppp [numValues];

    for(int i = 0 ; i < numValues; i++){ 
        value_init(&tree, &(ppp[i]), values[i]);
    }

    for (int i = 0; i < numValues; i++){   
        insert(&tree, &ppp[i].elem);
    }

    printf("\nNumero de elemeneto %d\n", tree.count);
    
    printf("Árbol Rojo-Negro:\n");
    printTree(&tree,tree.root, 0);
    printf("------------------------\n");
    for (int i = numValues -1 ; i >= 0; i--){
        int keyToDelete = values[i];
        delete(&tree, keyToDelete);
        printf("\nEliminado el nodo con el valor %d\n", keyToDelete);
        printf("\nÁrbol Rojo-Negro después de la eliminación:\n");
        printTree(&tree ,tree.root, 0);
        printf("\nNumero de elemeneto %d\n", tree.count);

        printf("==========================================================\n");

    }
    
    

    return 0;
}

/*

    struct RedBlackTree tree;
    rbt_init(&tree);

    // Ejemplo de uso: Insertar nodos en el árbol rojo-negro
    struct nodeRedBlack node1, node2, node3;
    createNodeRedBlackTree(&tree, &node1);
    createNodeRedBlackTree(&tree, &node2);
    createNodeRedBlackTree(&tree, &node3);

    node1.data = 5;
    node2.data = 3;
    node3.data = 7;

    insert(&tree, &node1);
    insert(&tree, &node2);
    insert(&tree, &node3);


    printf("Árbol Rojo-Negro:\n");
    printTree(tree.root, 0);


*/