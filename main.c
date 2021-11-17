#include "header_files.h"

int main()
{
    struct RBNode *new_node = NULL;
    const int n;
    int i, val;

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

struct RBNode *deleteNode(struct RBNode *tree, struct RBNode *node_to_delete)
{
    if (node_to_delete != NULL)
    {
        if (node_to_delete == tree)
        {
            free(node_to_delete);
            return NULL;
        }
        if (node_to_delete->left == NULL && node_to_delete->right == NULL)
        {
            if (node_to_delete->node_color == RED)
            {
                free(node_to_delete);
                return tree;
            }
            else
            {
                if (siblingOf(node_to_delete) != NULL && siblingOf(node_to_delete)->node_color == RED)
                {
                    siblingOf(node_to_delete)->node_color == BLACK;
                    parentOf(node_to_delete)->node_color == RED;
                    if (node_to_delete == leftChildOf(node_to_delete->parent))
                        left_rotation(tree, node_to_delete->parent);
                    else
                        right_rotation(tree, node_to_delete->parent);
                    tree = deleteNode(tree, node_to_delete);
                }
                else
                {
                    siblingOf(node_to_delete)->node_color = RED;
                    if (parentOf(node_to_delete)->node_color = RED)
                    {
                        parentOf(node_to_delete)->node_color = BLACK;
                        free(node_to_delete);
                        return tree;
                    }
                    else
                    {
                        tree = deleteFixUp(tree, parentOf(node_to_delete));
                        free(node_to_delete);
                        return tree;
                    }
                }
            }
        }
        else
        {
            struct RBNode *inOrderSuccessor = inOrderSuccessorOf(tree, node_to_delete);
            node_to_delete->key = inOrderSuccessor->key;
            tree = deleteNode(tree, inOrderSuccessor);
        }
    }
}

struct RBNode *deleteFixUp(struct RBNode *tree, struct RBNode *node_to_fix)
{
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

struct RBNode *inOrderSuccessorOf(struct RBNode *tree, struct RBNode *node_i)
{
    if (node_i->right != NULL)
        return minValue(node_i->right);

    struct RBNode *parentNode = parentOf(node_i);

    while (parentNode != NULL && node_i == parentNode->right)
    {
        node_i = parentNode;
        node_i->parent = parentOf(parentNode);
    }
    return parentNode;
}