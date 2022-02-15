//Radhika Sinha
//Assignment 6 - Encrypt
//Nov 8th, 2021

#include <unistd.h>
#include <stdio.h>
#include <gmp.h>
#include <stdlib.h>
#include <inttypes.h>

#include "rsa.h"

#define OPTS "hvi:o:n:"
int main(int argc, char **argv) {
    FILE *infile = stdin; //default input file
    FILE *outfile = stdout; //default output file
    FILE *pbfile = fopen("rsa.pub", "r"); //default public key file
    uint32_t verbose = 0; //flag for verbose output
    int opt = 0;
    while ((opt = getopt(argc, argv, OPTS)) != -1) {
        switch (opt) {
        case 'h': //displays program synopsis and usage
            printf("SYNOPSIS\n");
            printf("   Encrypts data using RSA encryption.\n");
            printf("   Encrypted data is decrypted by the decrypt program..\n");
            printf("\n");
            printf("USAGE\n");
            printf("   ./encrypt [-hv] [-i infile] [-o outfile] -n pubkey -d privkey\n");
            printf("\n");
            printf("OPTIONS\n");
            printf("   -h            Display program help and usage.\n");
            printf("   -v            Display verbose program output.\n");
            printf("   -i infile     Input file of data to encrypt (default: stdin).\n");
            printf("   -o outfile    Output file for encrypted data (default: stdout).\n");
            printf("   -n pbfile     Public key file (default: rsa.pub).\n");
            exit(0);
            break;
        case 'v': //sets verbose flag to 1 (true)
            verbose = 1;
            break;
        case 'i': //specifies input file to encrypt
            infile = fopen(optarg, "r");
            break;
        case 'o': //specifies output file to encrypt
            outfile = fopen(optarg, "w");
            break;
        case 'n': //specifies file containing public key
            pbfile = fopen(optarg, "r");
            break;
        }
    }

    //error handling
    if (pbfile == NULL) {
        perror("Error while trying to access public key file");
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
    mpz_t m, n, e, s, d;
    mpz_inits(m, n, e, s, d, NULL);

    //read in username and info from public key file
    char username[33];
    rsa_read_pub(n, e, s, username, pbfile);

    //if verbose output specified, print information
    if (verbose) {
        printf("user = %s\n", username);
        uint32_t bits;
        bits = mpz_sizeinbase(s, 2) + 1;
        gmp_printf("s (%" PRIu32 " bits) = %Zd\n", bits, s);
        bits = mpz_sizeinbase(n, 2) + 1;
        gmp_printf("n (%" PRIu32 " bits) = %Zd\n", bits, n);
        bits = mpz_sizeinbase(e, 2) + 1;
        gmp_printf("e (%" PRIu32 " bits) = %Zd\n", bits, e);
    }

    //verify username matches signature
    mpz_set_str(m, username, 62);
    if (!rsa_verify(m, s, e, n)) {
        printf("Error: the username does not match the signature\n");
        exit(1);
    }

    //encrypt file
    rsa_encrypt_file(infile, outfile, n, e);

    //close input, output, private key file
    fclose(infile);
    fclose(outfile);
    fclose(pbfile);

    //clear mpz
    mpz_clears(m, n, e, s, d, NULL);
}
