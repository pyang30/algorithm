#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
    red,
    black
} Color;

typedef struct node_t{
    int  value;
    Color color;
    struct node_t *left;
    struct node_t *right;
    struct node_t *parent;
}node, pNode;

node * insert_node(node* root, int value);

node * rotate_left(node * n);

node * rotate_right(node * n);

int is_red(node * n);

node* flip_color(node *n);

void print_node(node * n);

void in_order(node * root);

node * rbt_search(node* root, int value);

node* min_value_node(node * root);

node* max_value_node(node * root);

node * node_predecessor(node *root, node * target);

node * node_secessor(node *root, node * target);

void free_node(node * n);

void delete_node(node* root, node* target);
