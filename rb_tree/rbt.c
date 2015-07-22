#include "rbt.h"

/*
 *create a tree root
 */
node * create_root(int value)
{
    node *root;
    root = insert_node(NULL, value);
    root->color = black;
    printf("root = %d\n", (int)root);
    return root;
}
/**
 * insert a node to a tree whose root is "root",
 * if root is NULL, create a new tree, and return root
 */
node * insert_node(node* root, int value)
{
    node *n;

    if (root == NULL) {
        root = (node*)malloc(sizeof(node));
        root->value = value;
        root->color = red;
        root->left = NULL;
        root->right = NULL;
        root->parent = NULL;
        return root;
    }

    if (root->value == value) {
        printf("value already exists\n");
        return root;
    }

    n = (node*)malloc(sizeof(node));
    n->value = value;
    n->right = n->left = NULL;

    if (root->value > value) {
        root->left = insert_node(root->left, value);
        root->left->parent = root;
    } else {
        root->right = insert_node(root->right, value);
        root->right->parent = root;
    }

    if (is_red(root->right) && !is_red(root->left))
        root = rotate_left(root);
    if (is_red(root->left) && is_red(root->left->left))
        root = rotate_right(root);
    if (is_red(root->left) && is_red(root->right))
        root = flip_color(root);

    return root; 
}
int is_red(node *n) 
{
    if (n == NULL)
        return 0;
    return n->color == red;
}

node * rotate_right(node * n)
{
    node *x;

    x = n->left;
    n->left = x->right;
    x->right = n;
    x->color = n->color;
    n->color = red;

    return x;
}

node * rotate_left(node * n)
{
    node *x;
    
    x = n->right;
    n->right = x->left;
    x->left = n;
    x->color = n->color;
    n->color = red;

    return x;
}

node * flip_color(node *n)
{
    n->left->color = black;
    n->right->color = black;
    n->color = red;

    return n;
}

/**
 * print the node's value
 */
void print_node(node * n)
{
    if (n) {
        printf("%d\n", n->value);
    } else {
        printf("%s: n is null\n", __func__);
    }
}

/**
 * in_order walk 
 */
void in_order(node * root)
{
    if (root) {
        in_order(root->left);
        print_node(root);
        in_order(root->right);
    }
}

/**
 * search from the root and return the node
 */
node * rbt_search(node* root, int value)
{
    if (root != NULL) {
        if (root->value == value) {
            return root;
        } else if (root->value > value) {
            return rbt_search(root->left, value);
        } else {
            return rbt_search(root->right, value);
        }
    } 

    return NULL;
}

/**
 * find the min value node from the root
 */
node* min_value_node(node * root)
{
    node *p, *cur;

    if (root != NULL) {
        p = root;
        cur = p->left;
        while (cur != NULL) {
            p = cur;
            cur = p->left;
        }

        return p;
    }

    return NULL;
}

/**
 * find the max value node from the root
 */
node* max_value_node(node * root)
{
    node *p, *cur;

    if (root != NULL) {
        p = root;
        cur = p->right;
        while (cur != NULL) {
            p = cur;
            cur = p->right;
        }

        return p;
    }
}

/**
 * find the predecessor node of the target
 */
node * node_predecessor(node *root, node * target)
{
    node * p, *cur;

    if (root == NULL) {
        printf("%s: root is null\n", __func__);
        return NULL;
    }

    if (target == NULL) {
        printf("%s: target is null\n", __func__);
        return NULL;
    }

    if (target->left != NULL) {
        return max_value_node(target->left);
    }
    
    cur = target;
    p = target->parent;
    while (p != NULL && p->right != cur) {
        cur = p;
        p = cur->parent;
    }
    return p;
}

/**
 * find the secessor node of the target
 */
node * node_secessor(node *root, node * target)
{
    node * p, *cur;

    if (root == NULL) {
        printf("%s: root is null\n", __func__);
        return NULL;
    }

    if (target == NULL) {
        printf("%s: target is null\n", __func__);
        return NULL;
    }

    if (target->right != NULL) {
        return min_value_node(target->right);
    }
    
    cur = target;
    p = target->parent;
    while (p != NULL && p->left != cur) {
        cur = p;
        p = cur->parent;
    }
    return p;
}

/**
 * free node memory
 */
void free_node(node * n)
{
    n->left = NULL;
    n->right = NULL;
    n->parent = NULL;

    free(n);
}

/**
 * delete "target" from tree
 */
void delete_node(node* root, node* target)
{
    node *p, *cur; 
    node *r, *l; 
    node *tmp_target;

    if (target == NULL) {
        printf("%s, target is null\n", __func__);
    }
    if (target->left == NULL && target->right == NULL) {
        p = target->parent;
        if (p == NULL) {
            free_node(target);
        } else if (p->right == target) {
            p->right = NULL;
        } else if(p->left == target) {
            p->left = NULL;
        }
    }  else if (target->left == NULL) {
        r = target->right;
        target->value = r->value;
        target->left = r->left;
        target->right = r->right;

        free_node(r);
    } else if(target->right == NULL) {
        l = target->left;
        target->value = l->value;
        target->left = l->left;
        target->right = r->right;
    } else {
        tmp_target = node_secessor(root, target);
        target->value = tmp_target->value;
        delete_node(root, tmp_target);
    }
     
}
