#ifndef FUNCTIONS_H_INCLUDED
#define FUNCTIONS_H_INCLUDED

typedef enum
{
    F,
    T
} boolean;

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
struct RBNode *parentOf(struct RBNode *node);
struct RBNode *grandParentOf(struct RBNode *node);
struct RBNode *leftChildOf(struct RBNode *node);
struct RBNode *rightChildOf(struct RBNode *node);
struct RBNode *siblingOf(struct RBNode *node);
struct RBNode *uncleOf(struct RBNode *node);

// Root declaration
struct RBNode *tree;

// Rotation functions
struct RBNode *left_rotation(struct RBNode *tree, struct RBNode *node_to_rotate);
struct RBNode *right_rotation(struct RBNode *tree, struct RBNode *node_to_rotate);

// Operations
void create_RBTree(struct RBNode *);
struct RBNode *create_node(int);
struct RBNode *nodeHavingValue(struct RBNode *tree, int);
void inOrderTraverseTree(struct RBNode *);

#endif