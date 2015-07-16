#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node_t{
    int  value;
    struct node_t *left;
    struct node_t *right;
    struct node_t *parent;
}node, pNode;

node * insert_node(node* root, int value);

void print_node(node * n);

void in_order(node * root);

node * bst_search(node* root, int value);

node* min_value_node(node * root);

node* max_value_node(node * root);

node * node_predecessor(node *root, node * target);

node * node_secessor(node *root, node * target);

void free_node(node * n);

void delete_node(node* root, node* target);
