#ifndef RB_INSERTION_H_INCLUDED
#define RB_INSERTION_H_INCLUDED

struct RBNode *insertNode(struct RBNode *, struct RBNode *);
struct RBNode *insertFixUp(struct RBNode *tree, struct RBNode *node_to_fix);

#endif