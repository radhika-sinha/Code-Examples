//Radhika Sinha
//Assignment 6 - Key Generator
//Nov 8th, 2021

#include <unistd.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <inttypes.h>
#include <sys/stat.h>
#include <stdlib.h>

#include "numtheory.h"
#include "randstate.h"
#include "rsa.h"

#define OPTS "hvb:i:n:d:s:"

int main(int argc, char **argv) {
    int opt = 0;
    FILE *pbfile = fopen("rsa.pub", "w");
    FILE *pvfile = fopen("rsa.priv", "w");
    time_t time_null = time(NULL);
    uint64_t nbits = 256;
    uint64_t iters = 50;
    uint32_t verbose = 0; //flag for verbose output
    uint64_t seed = (uint64_t) time_null;
    while ((opt = getopt(argc, argv, OPTS)) != -1) {
        switch (opt) {
        case 'h': //displays program synopsis and usage
            printf("SYNOPSIS\n");
            printf("   Generates an RSA public/private key pair.\n");
            printf("\n");
            printf("USAGE\n");
            printf("   ./keygen [-hv] [-b bits] -n pbfile -d pvfile\n");
            printf("\n");
            printf("OPTIONS\n");
            printf("   -h            Display program help and usage.\n");
            printf("   -v            Display verbose program output.\n");
            printf("   -b bits       Minimum bits needed for public key n.\n");
            printf("   -i confidence Miller-Rabin iterations for testing primes (default: 50).\n");
            printf("   -n pbfile     Public key file (default: rsa.pub).\n");
            printf("   -d pvfile     Private key file (default: rsa.priv).\n");
            printf("   -s seed       Random seed for testing.\n");
            exit(0);
            break;
        case 'v': //enables verbose output
            verbose = 1;
            break;
        case 'b': //specifies minimum number of bits for public modulus n
            nbits = atoi(optarg);
            break;
        case 'i': //specifies number of miller-rabin iterations for testing primes (default 50)
            iters = atoi(optarg);
            break;
        case 'n': //specifies public key file
            pbfile = fopen(optarg, "w"); //error handle
            break;
        case 'd': //specifies private key file
            pvfile = fopen(optarg, "w");
            break;
        case 's': //specifies random seed for random state initialization
            seed = atoi(optarg);
            break;
        }
    }

    //error handling for accessing files to write to
    if (pbfile == NULL) {
        perror("Error while trying to access public key file");
        exit(1);
    }
    if (pvfile == NULL) {
        perror("Error while trying to access private key file");
        exit(1);
    }

    //changes private key file permissions
    //only owner can read + write
    //no one else has permissions
    fchmod(fileno(pvfile), 0600);

    //initialize randsom state using set seed
    srandom(seed);
    randstate_init(seed);

    //declare and initialize mpz
    mpz_t p, q, n, e, d, s, m;
    mpz_inits(p, q, n, e, d, s, m, NULL);

    //make public and private keys
    rsa_make_pub(p, q, n, e, nbits, iters);
    rsa_make_priv(d, e, p, q);

    //store username as string
    char username[33];
    char *user = getenv("USER");
    strcpy(username, user);

    //convert username to mpz and sign
    mpz_set_str(m, username, 62);
    rsa_sign(s, m, d, n);

    //write public and private keys to files
    rsa_write_pub(n, e, s, username, pbfile); //what is s supposed to be
    rsa_write_priv(n, d, pvfile);

    //print out verbose output if verbose option was chosen
    if (verbose) {
        printf("user = %s\n", username);
        uint32_t bits;
        bits = mpz_sizeinbase(s, 2) + 1;
        gmp_printf("s (%" PRIu32 " bits) = %Zd\n", bits, s);
        bits = mpz_sizeinbase(p, 2) + 1;
        gmp_printf("p (%" PRIu32 " bits) = %Zd\n", bits, p);
        bits = mpz_sizeinbase(q, 2) + 1;
        gmp_printf("q (%" PRIu32 " bits) = %Zd\n", bits, q);
        bits = mpz_sizeinbase(n, 2) + 1;
        gmp_printf("n (%" PRIu32 " bits) = %Zd\n", bits, n);
        bits = mpz_sizeinbase(e, 2) + 1;
        gmp_printf("e (%" PRIu32 " bits) = %Zd\n", bits, e);
        bits = mpz_sizeinbase(d, 2) + 1;
        gmp_printf("d (%" PRIu32 " bits) = %Zd\n", bits, d);
    }

    //clear mpz variables
    mpz_clears(p, q, n, e, d, s, NULL);

    //clear random state
    randstate_clear();

    //close public and private key files
    fclose(pbfile);
    fclose(pvfile);
}
