#ifndef NODE_H
#define NODE_H

typedef struct tree_node {
	int tree_level;
	int tree_val;
	int tree_count;

	struct tree_node *left;
	struct tree_node *right;
} node_t;

#endif