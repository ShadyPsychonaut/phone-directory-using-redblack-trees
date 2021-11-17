#ifndef RB_DELETION_H_INCLUDED
#define RB_DELETION_H_INCLUDED

struct RBNode *deleteNode(struct RBNode *tree, struct RBNode *node_to_delete);
struct RBNode *deleteFixUp(struct RBNode *tree, struct RBNode *node_to_fix);

#endif