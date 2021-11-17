#include "header_files.h"

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
struct RBNode *siblingOf(struct RBNode *node)
{
    return leftChildOf(parentOf(node)) ? parentOf(node)->right : parentOf(node)->left;
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