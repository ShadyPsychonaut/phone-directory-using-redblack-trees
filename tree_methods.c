#include <stdio.h>
#include "functions.h"

void create_RBTree(struct RBNode *tree)
{
    tree = NULL;
}

struct RBNode *create_node(int val)
{
    struct RBNode *new_node;
    new_node = (struct RBNode *)malloc(sizeof(struct RBNode));
    new_node->key = val;
    new_node->node_color = RED;
    new_node->parent = NULL;
    new_node->left = NULL;
    new_node->right = NULL;

    printf("Node created");

    return new_node;
}

void inOrderTraverseTree(struct RBNode *tree)
{
    if (tree != NULL)
    {
        inOrderTraverseTree(tree->left);
        printf("%d\n", tree->key);
        inOrderTraverseTree(tree->right);
    }
}

struct RBNode *nodeHavingValue(struct RBNode *tree, int val)
{
    struct RBNode *curr;
    if (tree == NULL)
    {
        printf("\nThe tree is empty");
        return NULL;
    }
    curr = tree;
    if (curr->key == val)
        return curr;
    while (curr != NULL && val != curr->key)
        curr = (val < curr->key) ? curr->left : curr->right;
    if (curr == NULL)
    {
        printf("Not found");
        return NULL;
    }
    else
        return curr;
}