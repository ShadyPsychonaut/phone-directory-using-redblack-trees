#include <stdio.h>
#include "functions.h"

void swapValues(struct RBNode *u, struct RBNode *v)
{
    int temp;
    temp = u->key;
    u->key = v->key;
    v->key = temp;
}

void swapColors(struct RBNode *u, struct RBNode *v)
{
    enum COLOR temp;
    temp = u->node_color;
    u->node_color = v->node_color;
    v->node_color = temp;
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

struct RBNode *BSTReplace(struct RBNode *node)
{
    if (node->left != NULL && node->right != NULL)
        return inOrderSuccessorOf(node);

    if (node->left == NULL && node->right == NULL)
        return NULL;

    if (node->left != NULL)
        return node->left;
    else
        return node->right;
}

struct RBNode *minValue(struct RBNode *node)
{
    struct RBNode *current = node;

    /* loop down to find the leftmost leaf */
    while (current->left != NULL)
    {
        current = current->left;
    }
    return current;
}

struct RBNode *inOrderSuccessorOf(struct RBNode *node_i)
{
    return minValue(node_i->right);
}