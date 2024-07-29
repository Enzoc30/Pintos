#include <stdio.h>
#include <stdlib.h>




struct nodeRedBlack
{
    int data;
    struct nodeRedBlack *left;
    struct nodeRedBlack *right;
    int color;
    struct nodeRedBlack *parent;
};

struct RedBlackTree
{
    struct nodeRedBlack *root;
};

// int to Node
void createNode(struct nodeRedBlack *newNode)
{
    newNode->data = -1;
    newNode->parent = NULL;
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->color = 0; 
}

void createNodeRedBlackTree(struct RedBlackTree *tree, struct nodeRedBlack *node)
{
    node->left = NULL;
    node->right = NULL;
    node->data = -1;
    node->parent = NULL;
    node->color = 1;
};

void rbt_init(struct RedBlackTree *tree)
{
    tree->root = NULL;
}

// ----------------------
void leftRotate(struct RedBlackTree *tree, struct nodeRedBlack *x)
{
    struct nodeRedBlack *y = NULL;
    y = x->right;
    x->right = y->left;

    if (y->left != NULL)
    {
        y->left->parent = x;
    }

    y->parent = x->parent;

    if (x->parent == NULL)
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

void rightRotate(struct RedBlackTree *tree, struct nodeRedBlack *y)
{
    struct nodeRedBlack *x = NULL;
    x = y->left;
    y->left = x->right;

    if (x->right != NULL)
    {
        x->right->parent = y;
    }

    x->parent = y->parent;

    if (y->parent == NULL)
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

void fixInsertion(struct RedBlackTree *tree, struct nodeRedBlack *newNode)
{
    while (newNode->parent != NULL && newNode->parent->color == 0)
    {
        if (newNode->parent == newNode->parent->parent->left)
        {
            struct nodeRedBlack *y = NULL;
            y = newNode->parent->parent->right;
            if (y != NULL && y->color == 0)
            {
                newNode->parent->color = 1;
                y->color = 1;
                newNode->parent->parent->color = 0;
                newNode = newNode->parent->parent;
            }
            else
            {
                if (newNode == newNode->parent->right)
                {
                    newNode = newNode->parent;
                    leftRotate(tree, newNode);
                }
                newNode->parent->color = 1;
                newNode->parent->parent->color = 0;
                rightRotate(tree, newNode->parent->parent);
            }
        }
        else
        {
            struct nodeRedBlack *y = NULL;
            y = newNode->parent->parent->left;

            if (y != NULL && y->color == 0)
            {
                newNode->parent->color = 1;
                y->color = 1;
                newNode->parent->parent->color = 0;
                newNode = newNode->parent->parent;
            }
            else
            {
                if (newNode == newNode->parent->left)
                {
                    newNode = newNode->parent;
                    rightRotate(tree, newNode);
                }
                newNode->parent->color = 1;
                newNode->parent->parent->color = 0;
                leftRotate(tree, newNode->parent->parent);
            }
        }
    }
    tree->root->color = 1;
}

// Insert to threads (can be nodes)
void insert(struct RedBlackTree *tree, struct nodeRedBlack *newNode)
{
    // If the data is not a int, pass this line

    struct nodeRedBlack *y = NULL;
    struct nodeRedBlack *x;
    x = tree->root;

    while (x != NULL)
    {
        y = x;
        if (newNode->data < x->data)
            x = x->left;
        else
            x = x->right;
    }

    newNode->parent = y;

    if (y == NULL)
        tree->root = newNode;
    else if (newNode->data < y->data)
        y->left = newNode;
    else
        y->right = newNode;

    fixInsertion(tree, newNode);
}

void printTree(struct nodeRedBlack *root, int level)
{
    if (root != NULL)
    {
        printTree(root->right, level + 1);
        for (int i = 0; i < level; i++)
        {
            printf("\t");
        }
        printf("(%d, %s)\n", root->data, root->color == 0 ? "RED" : "BLACK");
        printTree(root->left, level + 1);
    }
}

struct nodeRedBlack *searchNode(struct nodeRedBlack *node, int data)
{
    // Can be change, there are two condition, can be one
    if (node == NULL || node->data == data)
    {
        return node;
    }
    if (data < node->data)
    {
        return searchNode(node->left, data);
    }

    return searchNode(node->right, data);
}

struct nodeRedBlack *search(struct RedBlackTree *tree, int data)
{
    return searchNode(tree->root, data);
}

void fixDeletion(struct RedBlackTree *tree, struct nodeRedBlack *x)
{
    while (x != NULL && (x == NULL || x->color == 1))
    {
        if (x == x->parent->left)
        {
            struct nodeRedBlack *w;
            w = x->parent->right;
            if (w->color == 0)
            {
                w->color = 1;
                x->parent->color = 0;
                leftRotate(tree, x->parent);
                w = x->parent->right;
            }
            if ((w->left == NULL || w->left->color == 1) &&
                (w->right == NULL || w->right->color == 1))
            {
                w->color = 0;
                x = x->parent;
            }
            else
            {
                if (w->right == NULL || w->right->color == 1)
                {
                    w->left->color = 1;
                    w->color = 0;
                    rightRotate(tree, w);
                    w = x->parent->right;
                }
                w->color = x->parent->color;
                x->parent->color = 1;
                w->right->color = 1;
                leftRotate(tree, x->parent);
                x = tree->root;
            }
        }
        else
        {
            struct nodeRedBlack *w;
            w = x->parent->left;
            if (w->color == 0)
            {
                w->color = 1;
                x->parent->color = 0;
                rightRotate(tree, x->parent);
                w = x->parent->left;
            }
            if ((w->right == NULL || w->right->color == 1) &&
                (w->left == NULL || w->left->color == 1))
            {
                w->color = 0;
                x = x->parent;
            }
            else
            {
                if (w->left == NULL || w->left->color == 1)
                {
                    w->right->color = 1;
                    w->color = 0;
                    leftRotate(tree, w);
                    w = x->parent->left;
                }
                w->color = x->parent->color;
                x->parent->color = 1;
                w->left->color = 1;
                rightRotate(tree, x->parent);
                x = tree->root;
            }
        }
    }
    if (x != NULL)
        x->color = 1;
}

struct nodeRedBlack *findMinimum(struct nodeRedBlack *node)
{
    while (node->left != NULL)
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
    if (u == NULL || u->parent == NULL)
    {
        return;
    }
    if (u->parent == NULL)
        tree->root = v;
    else if (u == u->parent->left)
        u->parent->left = v;
    else
        u->parent->right = v;
    if (v != NULL)
        v->parent = u->parent;
}

void deleteNode(struct RedBlackTree *tree, struct nodeRedBlack *z)
{
    struct nodeRedBlack *y;
    y = z;
    struct nodeRedBlack *x;

    int yOriginalColor = y->color;

    if (z->left == NULL)
    {
        x = z->right;
        transplant(tree, z, z->right);
    }
    else if (z->right == NULL)
    {
        x = z->left;
        transplant(tree, z, z->left);
    }
    else
    {
        y = findMinimum(z->right);
        yOriginalColor = y->color;
        x = y->right;
        if (y->parent == z)
            x->parent = y;
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

    if (yOriginalColor == 1)
    {
        fixDeletion(tree, x);
    }
}

void delete(struct RedBlackTree *tree, int data)
{
    struct nodeRedBlack *result = searchNode(tree->root, data);
    if (result != NULL)
    {
        deleteNode(tree, result);
    }
}

int main()
{
    struct RedBlackTree tree;
    rbt_init(&tree);

    // Crear threads para las inserciones
    int values[] = {1, 2, 3, 4, 5, 6, 18, 92, 86, 49};
    int numValues = sizeof(values) / sizeof(values[0]);

    for (int i = 0; i < numValues; i++)
    {
        struct nodeRedBlack *newNode = (struct nodeRedBlack *)malloc(sizeof(struct nodeRedBlack));
        createNodeRedBlackTree(&tree, newNode);
        newNode->data = values[i];
        insert(&tree, newNode);
    }

    printTree(tree.root, 0);



    return 0;
}
