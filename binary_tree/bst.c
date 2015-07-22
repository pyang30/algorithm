#include "bst.h"

/**
 * insert a node to a tree whose root is "root",
 * if root is NULL, create a new tree, and return root
 */
node * insert_node(node* root, int value)
{
    node *p, *cur;
    node *n;

    if (root == NULL) {
        root = (node*)malloc(sizeof(node));
        root->value = value;
        root->left = NULL;
        root->right = NULL;
        root->parent = NULL;

        return root;
    }

    n = (node*)malloc(sizeof(node));
    n->value = value;
    n->right = n->left = NULL;

    if (root->value == value) {
        printf("value already exists\n");
        return root;
    }

    if (root->value > value) {
        root->left = insert_node(root->left, value);
        root->left->parent = root;
    } else {
        root->right = insert_node(root->right, value);
        root->right->parent = root;
    }

    return root; 
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
node * bst_search(node* root, int value)
{
    if (root != NULL) {
        if (root->value == value) {
            return root;
        } else if (root->value > value) {
            return bst_search(root->left, value);
        } else {
            return bst_search(root->right, value);
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
