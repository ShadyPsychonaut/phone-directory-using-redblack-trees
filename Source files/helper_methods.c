#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "functions.h"

void swapValues(struct RBNode *u, struct RBNode *v)
{
    char *temp;
    temp = u->contactName;
    u->contactName = v->contactName;
    v->contactName = temp;

    temp = u->contactNo;
    u->contactNo = v->contactNo;
    v->contactNo = temp;

    temp = u->email;
    u->email = v->email;
    v->email = temp;
}

void swapColors(struct RBNode *u, struct RBNode *v)
{
    enum COLOR temp;
    temp = u->node_color;
    u->node_color = v->node_color;
    v->node_color = temp;
}

struct RBNode *nodeHavingValue(struct RBNode *tree, char *search)
{
    struct RBNode *curr;
    if (tree == NULL)
    {
        printf("\nThe tree is empty");
        return NULL;
    }
    curr = tree;
    if (strcmp(curr->contactName, search) == 0)
        return curr;
    while (curr != NULL && strcmp(search, curr->contactName) != 0)
        curr = (strcmp(search, curr->contactName) < 0) ? curr->left : curr->right;
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