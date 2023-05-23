#include <stdio.h>
#include <stdlib.h>
#include "node.h"
#include "traversals.h"

void levelorder(node_t *tree_t, char *filename)
{

    if (tree_t == NULL)
        return;

    else
    {

        levelorder(tree_t->left, filename);

        FILE *fp;
        if ((fp = fopen(filename, "a")) == NULL)
        {
            fprintf(stderr, "error opening file %s\n", filename);
            return;
        }

        fprintf(fp, "%*c%d:%-9d\n", tree_t->tree_level * 2, ' ',
                tree_t->tree_val,
                tree_t->tree_count);
        fclose(fp);

        levelorder(tree_t->right, filename);
    }
}

void preorder(node_t *tree_t, char *filename)
{

    if (tree_t == NULL)
        return;

    else
    {

        FILE *fp;
        if ((fp = fopen(filename, "a")) == NULL)
        {
            fprintf(stderr, "error opening file %s\n", filename);
            return;
        }

        // fprintf(fp,"%d:%d\n",tree->value, tree->counter);
        fprintf(fp, "%*c%d:%-9d\n", tree_t->tree_level * 2, ' ',
                tree_t->tree_val,
                tree_t->tree_count);
        fclose(fp);

        preorder(tree_t->left, filename);
        preorder(tree_t->right, filename);
    }
}

void postorder(node_t *tree_t, char *filename)
{

    if (tree_t == NULL)
        return;

    else
    {
        postorder(tree_t->left, filename);
        postorder(tree_t->right, filename);
        // printf("%d ",tree->value);

        FILE *fp;
        if ((fp = fopen(filename, "a")) == NULL)
        {
            fprintf(stderr, "error opening file %s\n", filename);
            return;
        }

        fprintf(fp, "%*c%d:%-9d\n", tree_t->tree_level * 2, ' ',
                tree_t->tree_val,
                tree_t->tree_count);
        fclose(fp);
    }
}