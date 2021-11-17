#include <stdio.h>
#include "functions.h"

struct RBNode *insertNode(struct RBNode *tree, struct RBNode *new_node)
{
    struct RBNode *ptr, *focus;
    ptr = tree;
    focus = NULL;
    while (ptr != NULL)
    {
        focus = ptr;
        if (new_node->key < ptr->key)
            ptr = ptr->left;
        else
            ptr = ptr->right;
    }

    // if (focus != NULL)
    //     printf("\nfocusNode is %d", focus->key);
    new_node->parent = focus;

    if (focus == NULL)
        tree = new_node;
    else if (new_node->key < focus->key)
        focus->left = new_node;
    else
        focus->right = new_node;

    printf("\nNode inserted");

    return insertFixUp(tree, new_node); // for the reqd rotations
}

struct RBNode *insertFixUp(struct RBNode *tree, struct RBNode *node_to_fix)
{
    struct RBNode *ptr;
    struct RBNode *parentNode = parentOf(node_to_fix);
    struct RBNode *grandParentNode, *uncle;

    if (parentNode == NULL)
    {
        tree->node_color = BLACK;
        return tree;
    }

    printf("\nParent node key and color = %d %d", parentNode->key, parentNode->node_color);

    while (parentNode != NULL && parentNode->node_color == RED)
    {
        parentNode = parentOf(node_to_fix);
        grandParentNode = grandParentOf(node_to_fix);
        printf("\nGrand parent node key and color = %d %d", grandParentNode->key, grandParentNode->node_color);
        uncle = uncleOf(node_to_fix);

        if (parentNode == grandParentNode->left)
        {
            if (uncle != NULL && uncle->node_color == RED)
            {
                parentNode->node_color = BLACK;
                uncle->node_color = BLACK;
                printf("\nUncle key n color is %d %d", uncle->key, uncle->node_color);
                grandParentNode->node_color = RED;
                node_to_fix = grandParentNode;
                parentNode = parentOf(node_to_fix);
            }
            else if (node_to_fix == parentNode->right) // forms a triangle
            {
                node_to_fix = parentNode;
                tree = left_rotation(tree, node_to_fix);

                parentNode = parentOf(node_to_fix);
                grandParentNode = grandParentOf(node_to_fix);

                parentNode->node_color = BLACK;
                grandParentNode->node_color = RED;
                tree = right_rotation(tree, grandParentNode);
            }
            else if (node_to_fix == parentNode->left) // forms a line
            {
                parentNode->node_color = BLACK;
                grandParentNode->node_color = RED;
                tree = right_rotation(tree, grandParentNode);
            }
        }
        else // parentNode is in the right of grandParentNode
        {
            if (uncle != NULL && uncle->node_color == RED)
            {
                printf("\nUncle key is %d %d", uncle->key, uncle->node_color);
                parentNode->node_color = BLACK;
                uncle->node_color = BLACK;
                grandParentNode->node_color = RED;
                node_to_fix = grandParentNode;
                parentNode = parentOf(node_to_fix);
                if (parentNode)
                    printf("\n%d %d", parentNode->key, parentNode->node_color);
            }
            else if (node_to_fix == parentNode->left)
            {
                node_to_fix = parentNode;
                tree = right_rotation(tree, node_to_fix);

                parentNode = parentOf(node_to_fix);
                grandParentNode = grandParentOf(node_to_fix);

                parentNode->node_color = BLACK;
                grandParentNode->node_color = RED;
                tree = left_rotation(tree, grandParentNode);
            }
            else if (node_to_fix == parentNode->right)
            {
                parentNode->node_color = BLACK;
                grandParentNode->node_color = RED;
                tree = left_rotation(tree, grandParentNode);
            }
        }
    }

    tree->node_color = BLACK;

    printf("\nNode fixed\n");
    // printf("Color of newNode is : %d \n\n", node_to_fix->node_color);

    printf("\nRoot node has the key n color = %d %d \n", tree->key, tree->node_color);

    return tree;
}