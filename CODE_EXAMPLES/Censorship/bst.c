//Radhika Sinha
//November 24th, 2021
//implementation of binary search tree

#include <stddef.h> //check later
#include <string.h>

#include "bst.h"

uint64_t branches = 0;

/*
 * Function: bst_create
 * Description: constructs an empty tree (NULL)
 * Parameters: void
 * Return: NULL because it is an empty tree
 */
Node *bst_create(void) {
    return NULL;
}

/*
 * Function: bst_height
 * Description: returns the height of the binary search tree rooted at root
 * Parameters: root: the first entry in the binary search tree
 * Return: the height of the bst
 */
uint32_t bst_height(Node *root) {
    if (root == NULL) {
        return 0;
    }
    uint32_t left_height = bst_height(root->left);
    uint32_t right_height = bst_height(root->right);
    uint32_t max_height;
    if (left_height - right_height > 0) {
        max_height = left_height;
    } else {
        max_height = right_height;
    }
    return max_height + 1;
}

/*
 * Function: bst_size
 * Description: returns the size of the binary search tree rooted at root
 * Parameters: root: the first entry in the binary search tree
 * Return: the number of nodes in the tree
 */ //branches + 1 ?
uint32_t bst_size(Node *root) {
    if (root == NULL) {
        return 0;
    }
    return bst_size(root->left) + 1 + bst_size(root->right);
}

/*
 * Function: bst_find
 * Description: 
 * 	searches for a node containing old speak in the binary search
 *	tree rooted at root.
 * Parameters: 
 * 	root: the root of the binary search tree
 * 	oldspeak: the value to search for
 * Return:
 * 	pointer to node if found
 * 	NULL pointer if not found
 */
Node *bst_find(Node *root, char *oldspeak) {
    branches++;
    if (root == NULL || strcmp(root->oldspeak, oldspeak) == 0) {
        return root;
    }
    if (strcmp(root->oldspeak, oldspeak) < 0) {
        return bst_find(root->right, oldspeak);
    }
    return bst_find(root->left, oldspeak);
}

/*
 * Function: bst_insert
 * Description: 
 * 	inserts a new node containing specified oldspeak and
 *	and newspeak into the binary search tree rooted at root.
 *	avoids inserting duplicates.
 * Parameters: 
 * 	root: the root of the binary search tree
 * 	oldspeak: string showing old word that should not be used
 * 	newspeak: string showing new way to say something
 * Return: the node that was inserted into the tree
 */
Node *bst_insert(Node *root, char *oldspeak, char *newspeak) {
    branches++;
    if (root == NULL) {
        return node_create(oldspeak, newspeak);
    }
    if (strcmp(root->oldspeak, oldspeak) > 0) {
        root->left = bst_insert(root->left, oldspeak, newspeak);
    }
    if (strcmp(root->oldspeak, oldspeak) < 0) {
        root->right = bst_insert(root->right, oldspeak, newspeak);
    }
    return root;
}

/*
 * Function: bst_print
 * Description: prints out each node using inorder traversal
 * Parameters: root: the root of the binary search tree
 * Return: void
 */
void bst_print(Node *root) {
    if (root == NULL) {
        return;
    }
    bst_print(root->left);
    node_print(root);
    bst_print(root->right);
}

/*
 * Function: bst_delete
 * Description: deletes a binary search tree using postorder traversal
 * Parameters: root: pointer to root node of tree
 * Return: void
 */
void bst_delete(Node **root) {
    if (*root == NULL) {
        return;
    }
    bst_delete(&(*root)->left);
    bst_delete(&(*root)->right);
    node_delete(root);
}
