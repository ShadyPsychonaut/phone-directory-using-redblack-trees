#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include "functions.h"

struct RBNode *create_node(char *name, char *no, char *mailid)
{
    struct RBNode *new_node;
    new_node = (struct RBNode *)malloc(sizeof(struct RBNode));

    new_node->contactName = malloc(strlen(name) + 1); // +1 to store null
    strcpy(new_node->contactName, name);
    new_node->contactNo = malloc(strlen(no) + 1);
    strcpy(new_node->contactNo, no);
    new_node->email = malloc(strlen(mailid) + 1);
    strcpy(new_node->email, mailid);

    new_node->node_color = RED;
    new_node->parent = NULL;
    new_node->left = NULL;
    new_node->right = NULL;

    printf("Node created");

    return new_node;
}

struct RBNode *insertNode(struct RBNode *tree, struct RBNode *new_node)
{
    struct RBNode *ptr, *focus;
    int val;
    ptr = tree;
    focus = NULL;
    while (ptr != NULL)
    {
        focus = ptr;
        val = strcmp(new_node->contactName, ptr->contactName);
        if (val < 0)
            ptr = ptr->left;
        else
            ptr = ptr->right;
    }

    new_node->parent = focus;

    if (focus == NULL)
        tree = new_node;
    else if (strcmp(new_node->contactName, focus->contactName) < 0)
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
    grandParentNode = NULL;
    uncle = NULL;

    if (parentNode == NULL)
    {
        tree->node_color = BLACK;
        return tree;
    }

    while (parentNode != NULL && parentNode->node_color == RED)
    {
        parentNode = parentOf(node_to_fix);
        grandParentNode = grandParentOf(node_to_fix);
        uncle = uncleOf(node_to_fix);

        if (parentNode == grandParentNode->left)
        {
            if (uncle != NULL && uncle->node_color == RED)
            {
                parentNode->node_color = BLACK;
                uncle->node_color = BLACK;
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
                parentNode->node_color = BLACK;
                uncle->node_color = BLACK;
                grandParentNode->node_color = RED;
                node_to_fix = grandParentNode;
                parentNode = parentOf(node_to_fix);
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

    return tree;
}