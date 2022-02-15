#include <stdlib.h>
#include <math.h>

#include "rsa.h"
#include "randstate.h"
#include "numtheory.h"

//creates two large primes p and q, product n, and public exponent e
void rsa_make_pub(mpz_t p, mpz_t q, mpz_t n, mpz_t e, uint64_t nbits, uint64_t iters) {
    mpz_t tot, tot1, n1, g;
    mpz_init(tot);
    mpz_init(tot1);
    mpz_init(n1);
    mpz_init(g);
    uint64_t pbits, qbits;
    pbits = random() % (nbits / 2);
    pbits += nbits / 4;
    qbits = nbits - pbits;
    make_prime(p, pbits, iters);
    make_prime(q, qbits, iters);
    //(p-1)(q-1) = pq - p - q + 1
    mpz_mul(tot, p, q);
    mpz_sub(tot, tot, p);
    mpz_sub(tot, tot, q);
    mpz_add_ui(tot, tot, 1);
    mpz_set(tot1, tot);
    while (mpz_cmp_ui(g, 1) != 0) {
        mpz_urandomb(n, state, nbits);
        mpz_set(n1, n);
        gcd(g, n1, tot1);
        if (mpz_cmp_ui(g, 1) == 0) {
            mpz_set(e, n);
        }
        mpz_set(tot1, tot);
    }
    mpz_mul(n, p, q); //set n to product of p and q
    mpz_clear(tot);
    mpz_clear(tot1);
    mpz_clear(n1);
    mpz_clear(g);
}

//writes to public key file
void rsa_write_pub(mpz_t n, mpz_t e, mpz_t s, char username[], FILE *pbfile) {
    gmp_fprintf(pbfile, "%Zx\n", n);
    gmp_fprintf(pbfile, "%Zx\n", e);
    gmp_fprintf(pbfile, "%Zx\n", s);
    fprintf(pbfile, "%s\n", username); //got rid of gmp
}

//reads in from public key file
void rsa_read_pub(mpz_t n, mpz_t e, mpz_t s, char username[], FILE *pbfile) {
    gmp_fscanf(pbfile, "%Zx\n", n);
    gmp_fscanf(pbfile, "%Zx\n", e);
    gmp_fscanf(pbfile, "%Zx\n", s);
    fscanf(pbfile, "%s\n", username);
}

//creates a private key
void rsa_make_priv(mpz_t d, mpz_t e, mpz_t p, mpz_t q) {
    mpz_t tot;
    mpz_init(tot);
    mpz_mul(tot, p, q);
    mpz_sub(tot, tot, p);
    mpz_sub(tot, tot, q);
    mpz_add_ui(tot, tot, 1);
    mod_inverse(d, e, tot); //check if function changes values, most likely does not
    mpz_clear(tot);
}

//writes to private key file
void rsa_write_priv(mpz_t n, mpz_t d, FILE *pvfile) {
    gmp_fprintf(pvfile, "%Zx\n", n);
    gmp_fprintf(pvfile, "%Zx\n", d);
}

//reads in from private key file
void rsa_read_priv(mpz_t n, mpz_t d, FILE *pvfile) {
    gmp_fscanf(pvfile, "%Zx\n", n);
    gmp_fscanf(pvfile, "%Zx\n", d);
}

//encrypt function
void rsa_encrypt(mpz_t c, mpz_t m, mpz_t e, mpz_t n) {
    pow_mod(c, m, e, n);
}

//encrypts a file
void rsa_encrypt_file(FILE *infile, FILE *outfile, mpz_t n, mpz_t e) {
    mpz_t k1, l, m, c;
    mpz_init(k1);
    mpz_init(m);
    mpz_init(c);
    mpz_init_set_ui(l, 1);
    mpz_ui_sub(k1, mpz_sizeinbase(n, 2), l);
    mpz_fdiv_q_ui(k1, k1, 8);
    uint32_t k = mpz_get_ui(k1);
    uint8_t *block = (uint8_t *) calloc(k, sizeof(uint8_t));
    block[0] |= 0xFF;
    uint64_t j = fread(block + 1, sizeof(uint8_t), k - 1, infile);
    while (j > 0) {
        mpz_import(m, j + 1, 1, sizeof(uint8_t), 1, 0, block);
        rsa_encrypt(c, m, e, n);
        gmp_fprintf(outfile, "%Zx\n", c);
        j = fread(block + 1, sizeof(uint8_t), k - 1, infile);
    }
    mpz_clear(k1);
    mpz_clear(l);
    mpz_clear(m);
    mpz_clear(c);
    free(block);
}

//decrypt function
void rsa_decrypt(mpz_t m, mpz_t c, mpz_t d, mpz_t n) {
    pow_mod(m, c, d, n);
}

//decrypts a file
void rsa_decrypt_file(FILE *infile, FILE *outfile, mpz_t n, mpz_t d) {
    mpz_t k1, l, m, c;
    mpz_init(k1);
    mpz_init(m);
    mpz_init(c);
    mpz_init_set_ui(l, 1);
    mpz_ui_sub(k1, mpz_sizeinbase(n, 2), l);
    mpz_fdiv_q_ui(k1, k1, 8);
    uint32_t k = mpz_get_ui(k1);
    uint8_t *block = (uint8_t *) calloc(k, sizeof(uint8_t));
    uint64_t current_bytes = gmp_fscanf(infile, "%Zx\n", c);
    uint64_t j = 0;
    while (current_bytes == 1) {
        rsa_decrypt(m, c, d, n);
        mpz_export(block, &j, 1, sizeof(uint8_t), 1, 0, m);
        fwrite(block + 1, sizeof(uint8_t), j - 1, outfile);
        current_bytes = gmp_fscanf(infile, "%Zx\n", c);
    }
    mpz_clear(k1);
    mpz_clear(l);
    mpz_clear(m);
    mpz_clear(c);
    free(block);
}

//computes rsa signature
void rsa_sign(mpz_t s, mpz_t m, mpz_t d, mpz_t n) {
    pow_mod(s, m, d, n);
}

//verifies the signature
bool rsa_verify(mpz_t m, mpz_t s, mpz_t e, mpz_t n) {
    mpz_t t;
    mpz_init(t);
    pow_mod(t, s, e, n);
    if (mpz_cmp(t, m) == 0) {
        mpz_clear(t);
        return true;
    }
    mpz_clear(t);
    return false;
}
