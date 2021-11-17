#ifndef HELPER_METHODS_H_INCLUDED
#define HELPER_METHODS_H_INCLUDED

void swapValues(struct RBNode *, struct RBNode *);
void swapColors(struct RBNode *, struct RBNode *);
struct RBNode *BSTReplace(struct RBNode *node);
struct RBNode *minValue(struct RBNode *);
struct RBNode *inOrderSuccessorOf(struct RBNode *node_i);

#endif