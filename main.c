#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <stdbool.h>
#include "functions.h"

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
        tree = deleteNode(tree, delete);

        inOrderTraverseTree(tree);

    } while (num != 0);
}