//Radhika Sinha
//Assignment 7 - The Great Firewall of Santa Cruz
//Nov 24th, 2021

#include <stdio.h>
#include <regex.h>
#include <stdlib.h>
#include <inttypes.h>
#include <unistd.h>

#include "bst.h"
#include "ht.h"
#include "bf.h"
#include "parser.h"
#include "messages.h"

#define MAX_BAD_SPEAK   14295
#define MAX_RIGHT_SPEAK 280

#define WORD "[a-z,A-Z,0-9,_]+['-?a-z,A-Z,0-9,_]*[a-z,A-Z,0-9,_]?"
#define OPTS "hst:f:"
int main(int argc, char **argv) {
    FILE *oldfile = fopen("badspeak.txt", "r");
    if (oldfile == NULL) {
        printf("Unable to open \"badspeak.txt\"\n");
        //helpful print message here
        //return
    }
    FILE *newfile = fopen("newspeak.txt", "r");
    if (newfile == NULL) {
        printf("Unable to open newspeak.txt file\n");
    }
    uint32_t statistics = 0;
    uint32_t table_size = 1 << 16;
    uint32_t filter_size = 1 << 20;
    int opt = 0;
    while ((opt = getopt(argc, argv, OPTS)) != -1) {
        switch (opt) {
        case 'h': //displays program synopsis and usage
            printf("SYNOPSIS\n");
            printf("   A word filtering program for the GPRSC.\n");
            printf("   Filters out and reports bad words parsed from stdin.\n");
            printf("\n");
            printf("USAGE\n");
            printf("   ./banhammer [-hs] [-t size] [-f size]\n");
            printf("\n");
            printf("OPTIONS\n");
            printf("   -h            Display program help and usage.\n");
            printf("   -s            Print program statistics.\n");
            printf("   -t size     Specify hash table size (default: 2^16).\n");
            printf("   -f size    Specify Bloom filter size (default: 2^20).\n");
            exit(0);
            break;
        case 's': //print program statistics flag = 1
            statistics = 1; //sets stats flag
            //average binary search tree size
            //average binary search tree height
            //average branches traversed
            //hash table load
            //bloom filter load
            break;
        case 't': //specifies hash table size (default: 2^16)
            table_size = atoi(optarg);
            break;
        case 'f': //specifies bloom filter size (default: 2^20)
            filter_size = atoi(optarg);
            break;
        }
    }

    HashTable *ht = ht_create(table_size);
    BloomFilter *bf = bf_create(filter_size);

    char old[1024]; //old speak buffer
    char new[1024]; //new speak buffer

    while (fscanf(oldfile, "%1023s\n", old) != EOF) {
        bf_insert(bf, old);
        ht_insert(ht, old, NULL);
    }

    while (fscanf(newfile, "%1023s %1023s\n", old, new) != EOF) {
        bf_insert(bf, old);
        ht_insert(ht, old, new);
    }

    regex_t re;

    Node **thoughtcrime = malloc(MAX_BAD_SPEAK * sizeof(Node));
    Node **rightspeak = malloc(MAX_RIGHT_SPEAK * sizeof(Node));

    //remember to free
    if (thoughtcrime == NULL) {
        printf("Error: thoughtcrime array not allocated.\n");
        exit(1);
    }
    if (rightspeak == NULL) {
        printf("Error: rightspeak array not allocated.\n");
        exit(1);
    }

    if (regcomp(&re, WORD, REG_EXTENDED)) {
        fprintf(stderr, "Failed to compile regex.\n");
        return 1;
    }

    char *word = NULL;

    //index for thoughtcrime and rightspeak arrays
    uint32_t thought_index = 0;
    uint32_t right_index = 0;
    Node *current_node;

    while ((word = next_word(stdin, &re)) != NULL) {
        if (bf_probe(bf, word)) {
            current_node = ht_lookup(ht, word);
            if (current_node->newspeak) {
                rightspeak[right_index] = ht_lookup(ht, word);
                right_index++;
            } else {
                thoughtcrime[thought_index] = ht_lookup(ht, word);
                thought_index++;
            }
        }
    }

    if (statistics) {
        double bf_load = (bf_count(bf) * 100.0) / bf_size(bf);
        double ht_load = (ht_count(ht) * 100.0) / ht_size(ht);
        double avg_branches = branches / (lookups * 1.0) - 1.0;
        printf("Average BST size: %f\n", ht_avg_bst_size(ht));
        printf("Average BST  height: %f\n", ht_avg_bst_height(ht));
        printf("Average branches traversed: %f\n", avg_branches);
        printf("Hash table load: %f%%\n", ht_load);
        printf("Bloom filter load: %f%%\n", bf_load);
        exit(0);
    }

    //should be careful with message printing since not null-terminated strings
    if (thought_index > 0 && right_index > 0) {
        printf("%s", mixspeak_message);
    } else if (thought_index > 0) {
        printf("%s", badspeak_message);
    } else if (right_index > 0) {
        printf("%s", goodspeak_message);
    }

    for (uint32_t i = 0; i < thought_index; i++) {
        node_print(thoughtcrime[i]);
    }
    for (uint32_t i = 0; i < right_index; i++) {
        node_print(rightspeak[i]);
    }

    clear_words();
    regfree(&re);

    bf_delete(&bf);
    ht_delete(&ht);

    fclose(newfile);
    fclose(oldfile);
    return 0;
}
