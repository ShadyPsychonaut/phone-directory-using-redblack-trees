#include <stdio.h>
#include "functions.h"

struct RBNode *left_rotation(struct RBNode *tree, struct RBNode *node_to_rotate)
{
    struct RBNode *ptr;
    struct RBNode *parentNode = parentOf(node_to_rotate);
    ptr = node_to_rotate->right;
    node_to_rotate->right = ptr->left;
    if (ptr->left != NULL)
    {
        struct RBNode *leftChild = leftChildOf(ptr);
        leftChild->parent = node_to_rotate;
    }
    ptr->parent = parentNode;
    if (parentNode == NULL)
        tree = ptr;
    else if (node_to_rotate == parentNode->left)
        parentNode->left = ptr;
    else
        parentNode->right = ptr;
    ptr->left = node_to_rotate;
    node_to_rotate->parent = ptr;

    printf("\nLeft rotated\n");

    return tree;
}

struct RBNode *right_rotation(struct RBNode *tree, struct RBNode *node_to_rotate)
{
    struct RBNode *ptr;
    struct RBNode *parentNode = parentOf(node_to_rotate);
    ptr = node_to_rotate->left;
    node_to_rotate->left = ptr->right;
    if (ptr->right != NULL)
    {
        struct RBNode *rightChild = rightChildOf(ptr);
        rightChild->parent = node_to_rotate;
    }
    ptr->parent = parentNode;
    if (parentNode == NULL)
        tree = ptr;
    else if (node_to_rotate == parentNode->right)
        parentNode->right = ptr;
    else
        parentNode->left = ptr;
    ptr->right = node_to_rotate;
    node_to_rotate->parent = ptr;

    printf("\nRight rotated\n");

    return tree;
}