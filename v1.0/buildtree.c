#include <stdlib.h>
#include <stdio.h>
#include "buildtree.h"
#include "node.h"



node_t *insert (node_t *trees, int val, int lv) {

	if (trees == NULL) {
		node_t *temp = (node_t *) malloc(sizeof(node_t));
		temp->tree_val = val;
		temp->tree_count = 1;
		temp->left = NULL;
		temp->right = NULL;
		temp->tree_level = lv;
		return temp;
	}

	else if (val == trees->tree_val)
		trees->tree_count += 1;

	else if (val < trees->tree_val)
		trees->left = insert(trees->left, val, lv+1);

	else if (val > trees->tree_val)
		trees->right = insert(trees->right, val, lv+1);

	return trees;
}