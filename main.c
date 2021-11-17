#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

enum COLOR
{
    RED,
    BLACK
};

struct RBNode
{
    int key;
    enum COLOR node_color;
    struct RBNode *parent;
    struct RBNode *left;
    struct RBNode *right;
};

// Relations
struct RBNode *parentOf(struct RBNode *node)
{
    return (node != NULL) ? node->parent : NULL;
}
struct RBNode *grandParentOf(struct RBNode *node)
{
    return parentOf(parentOf(node));
}
struct RBNode *leftChildOf(struct RBNode *node)
{
    return (node != NULL) ? node->left : NULL;
}
struct RBNode *rightChildOf(struct RBNode *node)
{
    return (node != NULL) ? node->right : NULL;
}
struct RBNode *uncleOf(struct RBNode *node)
{
    struct RBNode *const parentNode = parentOf(node);
    if (parentNode != NULL)
    {
        struct RBNode *const grandParentNode = grandParentOf(node);
        if (grandParentNode != NULL)
            return (parentNode == leftChildOf(grandParentNode)) ? rightChildOf(grandParentNode) : leftChildOf(grandParentNode);
    }
    return NULL;
}

// Root declaration
struct RBNode *tree;

// Rotation functions
struct RBNode *left_rotation(struct RBNode *tree, struct RBNode *node_to_rotate);
struct RBNode *right_rotation(struct RBNode *tree, struct RBNode *node_to_rotate);

// Operations
void create_RBTree(struct RBNode *);
struct RBNode *create_node(int);
struct RBNode *insertNode(struct RBNode *, struct RBNode *);
struct RBNode *insertFixUp(struct RBNode *tree, struct RBNode *node_to_fix);
struct RBNode *deleteNode(struct RBNode *tree, int);
void inOrderTraverseTree(struct RBNode *);

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

void create_RBTree(struct RBNode *tree)
{
    tree = NULL;
}

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

    printf("\nLeft rotated");

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

    printf("\nRight rotated");

    return tree;
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

struct RBNode *deleteNode(struct RBNode *tree, int val)
{
}

void inOrderTraverseTree(struct RBNode *tree)
{
    if (tree != NULL)
    {
        inOrderTraverseTree(tree->left);
        printf("%lld\n", tree->key);
        inOrderTraverseTree(tree->right);
    }
}