#include <stdio.h>
#include <stdlib.h>
#include "functions.h"

struct RBNode *deleteNode(struct RBNode *tree, struct RBNode *node_to_delete)
{
    struct RBNode *inOrderSuccessor = BSTReplace(node_to_delete);
    struct RBNode *parentNode = parentOf(node_to_delete);

    boolean bothNodesAreBlack = ((inOrderSuccessor == NULL || inOrderSuccessor->node_color == BLACK) && node_to_delete->node_color == BLACK);

    if (inOrderSuccessor == NULL)
    {
        if (node_to_delete == tree)
        {
            free(node_to_delete);
            return NULL;
        }
        else
        {
            if (bothNodesAreBlack)
            {
                tree = deleteFixUp(tree, node_to_delete);
            }
            else
            {
                if (siblingOf(node_to_delete) != NULL)
                    siblingOf(node_to_delete)->node_color = RED;
            }
            if (node_to_delete == leftChildOf(parentNode))
                parentNode->left = NULL;
            else
                parentNode->right = NULL;
        }
        free(node_to_delete);
        return tree;
    }

    if (node_to_delete->left == NULL || node_to_delete->right == NULL)
    {
        if (node_to_delete == tree)
        {
            node_to_delete->key = inOrderSuccessor->key;
            node_to_delete->left = NULL;
            node_to_delete->right = NULL;
            tree = deleteNode(tree, inOrderSuccessor);
            return tree;
        }
        else
        {
            if (node_to_delete == leftChildOf(parentNode))
                parentNode->left = inOrderSuccessor;
            else
                parentNode->right = inOrderSuccessor;
            free(node_to_delete);
            inOrderSuccessor->parent = parentNode;
            if (bothNodesAreBlack)
                tree = deleteFixUp(tree, inOrderSuccessor);
            else
                inOrderSuccessor->node_color = BLACK;
        }
        return tree;
    }
    swapValues(inOrderSuccessor, node_to_delete);
    tree = deleteNode(tree, inOrderSuccessor);
    return tree;
}

struct RBNode *deleteFixUp(struct RBNode *tree, struct RBNode *node_to_fix)
{
    if (node_to_fix == tree)
        return tree;

    struct RBNode *sibling = siblingOf(node_to_fix);
    struct RBNode *parentNode = parentOf(node_to_fix);

    if (sibling == NULL)
        tree = deleteFixUp(tree, parentNode);
    else
    {
        if (sibling->node_color == RED)
        {
            parentNode->node_color = RED;
            sibling->node_color = BLACK;
            if (sibling == parentNode->left)
                tree = right_rotation(tree, parentNode);
            else
                tree = left_rotation(tree, parentNode);
            tree = deleteFixUp(tree, node_to_fix);
        }
        else // sibling is black
        {
            if (hasRedChild(sibling))
            {
                if (leftChildOf(sibling) != NULL && leftChildOf(sibling)->node_color == RED)
                {
                    if (sibling == leftChildOf(parentNode))
                    {
                        leftChildOf(sibling)->node_color = sibling->node_color;
                        sibling->node_color = parentNode->node_color;
                        tree = right_rotation(tree, parentNode);
                    }
                    else
                    {
                        leftChildOf(sibling)->node_color = parentNode->node_color;
                        tree = right_rotation(tree, sibling);
                        tree = left_rotation(tree, parentNode);
                    }
                }
                else
                {
                    if (sibling == leftChildOf(parentNode))
                    {
                        rightChildOf(sibling)->node_color = parentNode->node_color;
                        tree = left_rotation(tree, sibling);
                        tree = right_rotation(tree, parentNode);
                    }
                    else
                    {
                        rightChildOf(sibling)->node_color = sibling->node_color;
                        sibling->node_color = parentNode->node_color;
                        tree = left_rotation(tree, parentNode);
                    }
                }
                parentNode->node_color = BLACK;
            }
            else
            {
                sibling->node_color = RED;
                if (parentNode->node_color == BLACK)
                    tree = deleteFixUp(tree, parentNode);
                else
                    parentNode->node_color = BLACK;
            }
        }
    }
    return tree;
}