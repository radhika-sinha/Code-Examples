//Radhika Sinha
//bit vector code
//November 29th, 2021

#include <stdlib.h>
#include <inttypes.h>
#include <stdio.h>

#include "bv.h"

struct BitVector {
    uint32_t length;
    uint8_t *vector;
};

/*
 * Function: bv_create
 * Description: constructor for a bit vector that holds length bits
 * Parameters: length: how long the bit vector should be
 * Return: a pointer to the allocated bit vector or NULL if not enough memory
 */
BitVector *bv_create(uint32_t length) {
    BitVector *bv = (BitVector *) calloc(1, sizeof(BitVector));
    if (bv) {
        bv->length = length;
        bv->vector = (uint8_t *) calloc(length, sizeof(uint8_t));
        if (!bv->vector) {
            free(bv);
            bv = NULL;
        }
    }
    return bv;
}

/*
 * Function: bv_delete
 * Description: destructor for a bit vector, frees bv and sets pointer to NULL
 * Parameters: bv: pointer to the bit vector that is to be deleted
 * Return: void
 */
void bv_delete(BitVector **bv) {
    if (*bv && (*bv)->vector) {
        free((*bv)->vector);
        free(*bv);
        *bv = NULL;
    }
    return;
}

/*
 * Function: bv_length
 * Description: returns the length of a bit vector
 * Parameters: bv: the bit vector 
 * Return: the length of the bit vector
 */
uint32_t bv_length(BitVector *bv) {
    return bv->length;
}

/*
 * Function: bv_set_bit
 * Description: sets the i^th bit in a bit vector
 * 		returns false if i is out of range
 * 		true if successful
 * Parameters: 
 * 	bv: the bit vector
 * 	i: the bit to set
 * Return:
 * 	returns false if i is out of range
 * 	true if successful
 */
bool bv_set_bit(BitVector *bv, uint32_t i) {
    if (i < bv->length) {
        bv->vector[i / 8] |= (0x1 << i % 8);
        return true;
    } else {
        return false;
    }
}

/*
 * Function: bv_clr_bit
 * Description: clears the i^th bit in the bit vector
 * Parameters:
 * 	bv: the bit vector
 * 	i: the bit to set
 * Return: 
 * 	false if i is out of range
 * 	true to indicate success
 */
bool bv_clr_bit(BitVector *bv, uint32_t i) {
    if (i < bv->length) {
        bv->vector[i / 8] &= ~(0x1 << i % 8);
        return true;
    } else {
        return false;
    }
}

/*
 * Function: bv_get_bit
 * Description: returns the i^th bit in the bit vector
 * Parameters:
 * 	bv: the bit vector
 * 	i: the bit to return
 * Return:
 * 	false if out of range
 * 	false if value of bit is 0
 * 	true if value of bit is 1
 */
bool bv_get_bit(BitVector *bv, uint32_t i) {
    if (i < bv->length) {
        return (bv->vector[i / 8] >> i % 8) & 0x1;
    }
    return 0; //check later
}

/*
 * Function: bv_print
 * Description: debug function to print the bits of a bit vector
 * 		prints out either 0 or 1 depending on whether bit is set
 * Parameters: bv: the bit vector to print
 * Return: void
 */
void bv_print(BitVector *bv) {
    for (uint32_t i = 0; i < bv->length; i++) {
        printf("%" PRIu32 ": %d", i, bv_get_bit(bv, i));
    }
}
