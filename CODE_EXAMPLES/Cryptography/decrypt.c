//Radhika Sinha
//Assignment 6 - Decrypt
//Nov 8th, 2021

#include <unistd.h>
#include <gmp.h>
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

#include "rsa.h"

#define OPTS "hvi:o:n:"

int main(int argc, char **argv) {
    FILE *infile = stdin;
    FILE *outfile = stdout;
    FILE *pvfile = fopen("rsa.priv", "r");
    uint32_t verbose = 0;
    int opt = 0;
    while ((opt = getopt(argc, argv, OPTS)) != -1) {
        switch (opt) {
        case 'h':
            printf("SYNOPSIS\n");
            printf("   Decrypts data using RSA decryption.\n");
            printf("   Encrypted data is encrypted by the encrypt program.\n");
            printf("\n");
            printf("USAGE\n");
            printf("   ./decrypt [-hv] [-i infile] [-o outfile] -n pubkey -d privkey\n");
            printf("\n");
            printf("OPTIONS\n");
            printf("   -h            Display program help and usage.\n");
            printf("   -v            Display verbose program output.\n");
            printf("   -i infile     Input file of data to decrypt (default: stdin).\n");
            printf("   -o outfile    Output file for decrypted data (default: stdout).\n");
            printf("   -n pvfile     Private key file (default: rsa.priv).\n");
            exit(0);
            break;
        case 'v': verbose = 1; break;
        case 'i': infile = fopen(optarg, "r"); break;
        case 'o': outfile = fopen(optarg, "w"); break;
        case 'n': pvfile = fopen(optarg, "r"); break;
        }
    }

    //file I/O error handling
    if (pvfile == NULL) {
        perror("Error while trying to access private key file");
        exit(1);
    }
    if (infile == NULL) {
        perror("Error");
        exit(1);
    }
    if (outfile == NULL) {
        perror("Error");
        exit(1);
    }

    //declare and initialize mpz
    mpz_t n, d;
    mpz_inits(n, d, NULL);

    //read in information from private key file
    rsa_read_priv(n, d, pvfile);

    //print information if verbose option enabled
    if (verbose) {
        uint32_t bits;
        bits = mpz_sizeinbase(n, 2) + 1;
        gmp_printf("n (%" PRIu32 " bits) = %Zd\n", bits, n);
        bits = mpz_sizeinbase(d, 2) + 1;
        gmp_printf("d (%" PRIu32 " bits) = %Zd\n", bits, d);
    }

    //decrypt file
    rsa_decrypt_file(infile, outfile, n, d);

    //close input, output, and private key file
    fclose(infile);
    fclose(outfile);
    fclose(pvfile);

    //clear mpz
    mpz_clears(n, d, NULL);
}
