//Radhika Sinha
//November 24th, 2021
//simple implementation of node data structure

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

#include "node.h"

/*
 * Function: node_create
 * Description: creates a new node
 * Parameters: 
 * 	oldspeak: the old way to say something
 * 	newspeak: the new way to say something, can be NULL
 * Return: the new node that is created
 */
Node *node_create(char *oldspeak, char *newspeak) {
    Node *N = (Node *) calloc(1, sizeof(Node));
    if (N) {
        N->oldspeak = strdup(oldspeak); //double check implementation
        assert(strcmp(N->oldspeak, oldspeak) == 0);
        if (newspeak) {
            N->newspeak = strdup(newspeak);
            assert(strcmp(N->newspeak, newspeak) == 0);
        }
        N->left = N->right = NULL;
    }
    return N;
}

/*
 * Function: node_delete
 * Description: deletes a node
 * Parameters: 
 * 	n: pointer to the node that is to be deleted
 * Return: void
 */
void node_delete(Node **n) {
    if (*n) {
        if ((*n)->oldspeak) {
            free((*n)->oldspeak);
        }
        if ((*n)->newspeak) {
            free((*n)->newspeak);
        }
        *n = NULL;
    }
}

/*
 * Function: node_print
 * Description: prints out a node
 * Parameters: `
 * 	n: the node that is to be printed
 * Return: void
 */
void node_print(Node *n) {
    if (n) {
        if (n->oldspeak && n->newspeak) {
            printf("%s -> %s\n", n->oldspeak, n->newspeak);
        }
        if (n->oldspeak && !(n->newspeak)) {
            printf("%s\n", n->oldspeak);
        }
    }
}
