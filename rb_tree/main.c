#include "rbt.h"

int main()
{
    node *root;
    root = create_root(NULL, 5);
    printf("%s:a = %d\n",__func__, (int)root);
    /*
    insert_node(root, 34);
    insert_node(root, 23);
    insert_node(root, 54);
    insert_node(root, 1);
    insert_node(root, 25);
    insert_node(root, 12);
    insert_node(root, 18);
//    insert_node(root, 5);
    insert_node(root, 13);
 //   insert_node(root, 13);
    insert_node(root, 29);
*/
    //in_order(root);
/*
    if (bst_search(root, 15)) {
        printf(" found\n");
    }else {
        printf("not found\n");
    }
    
    printf("min node = %d\n", min_value_node(bst_search(root, 23))->value);
    printf("min node = %d\n", min_value_node(bst_search(root, 23))->value);
    printf("max node = %d\n", max_value_node(root)->value);

    printf("pre node = %d\n", node_secessor(root, bst_search(root, 23))->value);
    printf("pre node = %d\n", node_secessor(root, bst_search(root, 5))->value);
    printf("pre node = %d\n", node_secessor(root, bst_search(root, 1))->value);
    */

//    delete_node(root, rbt_search(root, 54));
    in_order(root);
}
