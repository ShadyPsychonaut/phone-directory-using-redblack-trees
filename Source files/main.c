#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <stdbool.h>
#include "functions.h"

// Root declaration
struct RBNode *tree;

int main()
{
    struct RBNode *new_node = NULL;
    const int n;
    int i, val, num;

    create_RBTree(tree);

    printf("Enter the number of elements in the tree : ");
    scanf("%d", &n);
    for (i = 0; i < n; i++)
    {
        printf("\nEnter key value : ");
        scanf("%d", &val);
        new_node = create_node(val);
        tree = insertNode(tree, new_node);
    }
    inOrderTraverseTree(tree);

    do
    {
        printf("\nInput 0 to exit");
        printf("\nInput the number to be deleted : ");
        scanf("%d", &num);

        struct RBNode *delete = nodeHavingValue(tree, num);
        if (delete == NULL)
            continue;
        tree = deleteNode(tree, delete);

        // printf("\nRoot node is : ", tree->key);

        inOrderTraverseTree(tree);

    } while (num != 0);
}

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

void inOrderTraverseTree(struct RBNode *root)
{
    if (root != NULL)
    {
        inOrderTraverseTree(root->left);
        printf("%d\n", root->key);
        inOrderTraverseTree(root->right);
    }
}