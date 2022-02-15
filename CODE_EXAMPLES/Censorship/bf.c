//Radhika Sinha
//bloom filter
//November 29th, 2021

#include <stdlib.h>

#include "bf.h"
#include "salts.h"
#include "speck.h"

struct BloomFilter {
    uint64_t primary[2];
    uint64_t secondary[2];
    uint64_t tertiary[2];
    BitVector *filter;
};

/*
 * Function: bf_create
 * Description: constructor for a bloom filter
 * 		that uses three different salts
 * Parameters: size: the size of the bloom filter
 * Return: a pointer to the allocated bloom filter or NULL if not enough memory
 */
BloomFilter *bf_create(uint32_t size) {
    BloomFilter *bf = (BloomFilter *) calloc(size, sizeof(BloomFilter)); //check this
    if (bf) {
        bf->primary[0] = SALT_PRIMARY_LO;
        bf->primary[1] = SALT_PRIMARY_HI;
        bf->secondary[0] = SALT_SECONDARY_LO;
        bf->secondary[1] = SALT_SECONDARY_HI;
        bf->tertiary[0] = SALT_TERTIARY_LO;
        bf->tertiary[1] = SALT_TERTIARY_HI;
        bf->filter = bv_create(size);
        if (!bf->filter) {
            free(bf);
            bf = NULL;
        }
    }
    return bf;
}

/*
 * Function: bf_delete
 * Description: destructor for a bloom filter
 * Parameters: bf: pointer to the bloom filter that is to be deleted
 * Return: void
 */
void bf_delete(BloomFilter **bf) {
    if (*bf && (*bf)->filter) {
        free((*bf)->filter);
        free(*bf);
        *bf = NULL;
    }
    return;
}

/*
 * Function: bf_size
 * Description: returns the size of a bloom filter
 * Parameters: bf: the bloom filter
 * Return: the size of the bloom filter
 */
uint32_t bf_size(BloomFilter *bf) {
    return bv_length(bf->filter);
}

/*
 * Function: bf_insert
 * Description: inserts oldspeak into the bloom filter
 * Parameters:
 * 	bf: the bloom filter
 * 	oldspeak: the oldspeak to be inserted
 * Return: void
 */
void bf_insert(BloomFilter *bf, char *oldspeak) {
    uint32_t primary_index = hash(bf->primary, oldspeak); //check value
    uint32_t secondary_index = hash(bf->secondary, oldspeak);
    uint32_t tertiary_index = hash(bf->tertiary, oldspeak);
    primary_index = primary_index % bf_size(bf);
    secondary_index = secondary_index % bf_size(bf);
    tertiary_index = tertiary_index % bf_size(bf);
    bv_set_bit(bf->filter, primary_index);
    bv_set_bit(bf->filter, secondary_index);
    bv_set_bit(bf->filter, tertiary_index);
}

/*
 * Function: bf_probe
 * Description: probes the bloom filter for oldspeak
 * Parameters:
 * 	bf: the bloom filter
 * 	oldspeak: the oldspeak to probe for
 * Return:
 * 	true if oldspeak was most likely added to bloom filter
 * 	false if otherwise (definitely not in bloom filter)
 */
bool bf_probe(BloomFilter *bf, char *oldspeak) {
    uint32_t primary_index = hash(bf->primary, oldspeak); //check value
    uint32_t secondary_index = hash(bf->secondary, oldspeak);
    uint32_t tertiary_index = hash(bf->tertiary, oldspeak);
    primary_index = primary_index % bv_length(bf->filter);
    secondary_index = secondary_index % bv_length(bf->filter);
    tertiary_index = tertiary_index % bv_length(bf->filter);
    if (bv_get_bit(bf->filter, primary_index)) {
        if (bv_get_bit(bf->filter, secondary_index)) {
            if (bv_get_bit(bf->filter, tertiary_index)) {
                return true;
            }
        }
    }
    return false;
}

/*
 * Function: bf_count
 * Description: returns the number of set bits in the bloom filter
 * Parameters: bf: the bloom filter
 * Return: the number of set bits
 */
uint32_t bf_count(BloomFilter *bf) {
    uint32_t count = 0;
    for (uint32_t i = 0; i < bv_length(bf->filter); i++) {
        if (bv_get_bit(bf->filter, i)) {
            count++;
        }
    }
    return count;
}

/*
 * Function: bf_print
 * Description: debug function to print out the bits of a bloom filter
 * Parameters: bf: the bloom filter
 * Return: void
 */
void bf_print(BloomFilter *bf) {
    bv_print(bf->filter);
}
