//Radhika Sinha
//hash table functions
//Nov 29th, 2021

#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h> //remove later print number stuff

#include "ht.h"
#include "salts.h"
#include "speck.h"

uint64_t lookups = 0;

struct HashTable {
    uint64_t salt[2];
    uint32_t size;
    Node **trees;
};

/*
 * Function: ht_create
 * Description: constructor for a hash table
 * Parameters: size: number of indices that the hash table can index up to
 * Return: the hash table that is created
 */
HashTable *ht_create(uint32_t size) {
    HashTable *ht = (HashTable *) calloc(1, sizeof(HashTable));
    if (ht) {
        ht->salt[0] = SALT_HASHTABLE_LO;
        ht->salt[1] = SALT_HASHTABLE_HI;
        ht->size = size;
        ht->trees = (Node **) calloc(size, sizeof(Node *));
        if (!(ht->trees)) {
            free(ht);
            ht = NULL;
        }
    }
    return ht;
}

/*
 * Function: ht_delete
 * Description: destructor for a hash table, frees bsts
 * Parameters: ht: pointer to the hash table to delete
 * Return: void
 */
void ht_delete(HashTable **ht) {
    if (*ht) {
        if ((*ht)->trees) {
            for (uint32_t i = 0; i < (*ht)->size; i++) {
                bst_delete(&(*ht)->trees[i]);
            }
            free((*ht)->trees);
        }
        *ht = NULL;
    }
}

/*
 * Function: ht_size
 * Description: returns the hash table's size
 * Parameters: ht: the hash table
 * Return: size of hash table
 */
uint32_t ht_size(HashTable *ht) {
    return ht->size;
}

/*
 * Function: ht_lookup
 * Description: searches for an entry in the hash table
 * Parameters: 
 * 	ht: the hash table
 * 	oldspeak: the value to be hashed for index of bst
 * Return:
 * 	pointer to node if node is found
 * 	NULL if otherwise
 */
Node *ht_lookup(HashTable *ht, char *oldspeak) {
    lookups++;
    uint32_t index = hash(ht->salt, oldspeak) % ht->size; //range [0,size)
    return bst_find(ht->trees[index], oldspeak);
}

/*
 * Function: ht_ins ert
 * Description: inserts oldspeak and newspeak translation into hash table
 * Parameters: 
 * 	ht: the hash table
 * 	oldspeak: old speak to be inserted and hashed
 * 	newspeak: corresponding new translation to insert, can be NULL
 * Return: void
 */
void ht_insert(HashTable *ht, char *oldspeak, char *newspeak) {
    lookups++;
    uint32_t index = hash(ht->salt, oldspeak) % ht->size; //range [0,size)
    if (ht->trees[index]) {
        bst_insert(ht->trees[index], oldspeak, newspeak);
    } else {
        ht->trees[index] = bst_insert(ht->trees[index], oldspeak, newspeak);
    }
}

/*
 * Function: ht_count
 * Description: returns number of non-NULL bsts in hash table
 * Parameters: ht: the hash table
 * Return: number of non-NULL bsts
 */
uint32_t ht_count(HashTable *ht) {
    uint32_t count = 0;
    for (uint32_t i = 0; i < ht->size; i++) {
        if (ht->trees[i] != NULL) {
            count++;
        }
    }
    return count;
}

/*
 * Function: ht_avg_bst_size
 * Description: computes average binary search tree size
 * Parameters: ht: the hash table
 * Return: average binary search tree size in given hash table
 */
double ht_avg_bst_size(HashTable *ht) {
    double sum = 0.0; //variable to store sum of all sizes
    for (uint32_t i = 0; i < ht->size; i++) {
        sum += bst_size(ht->trees[i]);
    }
    return sum / ht_count(ht);
}

/*
 * Function: ht_avg_bst_height
 * Description: computes average bst height
 * Parameters: ht: the hash table
 * Return: average height of binary search tree in given hash table
 */
double ht_avg_bst_height(HashTable *ht) {
    double sum = 0.0; //variable to store sum of all heights
    for (uint32_t i = 0; i < ht->size; i++) {
        sum += bst_height(ht->trees[i]);
    }
    return sum / ht_count(ht);
}

/*
 * Function: ht_print
 * Description: debug function to print out the contents of a hash table
 * Parameters: ht: the hash table to print
 * Return: void
 */
void ht_print(HashTable *ht) {
    for (uint32_t i = 0; i < ht->size; i++) {
        bst_print(ht->trees[i]);
    }
}
