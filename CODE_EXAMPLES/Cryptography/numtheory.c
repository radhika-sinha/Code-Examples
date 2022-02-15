#include <time.h>
#include <math.h>

#include "numtheory.h"
#include "randstate.h"

//gcd function
void gcd(mpz_t g, mpz_t a, mpz_t b) {
    while (mpz_cmp_ui(b, 0) != 0) {
        mpz_set(g, b);
        mpz_mod(b, a, b);
        mpz_set(a, g);
    }
}

//calculates modular inverse
void mod_inverse(mpz_t o, mpz_t a, mpz_t n) {
    mpz_t r, r1, o1, q, temp, h;
    mpz_inits(r, r1, o1, q, temp, h, NULL);
    mpz_set(r, n);
    mpz_set(r1, a);
    mpz_set_ui(o, 0);
    mpz_set_ui(o1, 1);
    while (mpz_cmp_ui(r1, 0) != 0) {
        mpz_fdiv_q(q, r, r1);
        mpz_set(temp, r);
        mpz_set(r, r1);
        mpz_mul(h, q, r1); //h = q*r1
        mpz_sub(r1, temp, h);
        mpz_set(temp, o);
        mpz_set(o, o1);
        mpz_mul(h, q, o1);
        mpz_sub(o1, temp, h);
    }
    if (mpz_cmp_ui(r, 1) > 0) {
        mpz_set_ui(o, 0);
    }
    if (mpz_cmp_ui(o, 0) < 0) {
        mpz_add(o, o, n);
    }
    mpz_clears(r, r1, o1, q, temp, h, NULL);
}

//pow mod function
void pow_mod(mpz_t o, mpz_t a, mpz_t d, mpz_t n) {
    mpz_t p;
    mpz_t d1;
    mpz_init_set(p, a);
    mpz_init_set(d1, d);
    mpz_set_ui(o, 1);
    while (mpz_cmp_ui(d1, 0) > 0) {
        if (!(mpz_fdiv_ui(d1, 2) == 0)) {
            mpz_mul(o, o, p);
            mpz_mod(o, o, n);
        }
        mpz_mul(p, p, p);
        mpz_fdiv_r(p, p, n);
        mpz_fdiv_q_ui(d1, d1, 2);
    }
    mpz_clear(p);
    mpz_clear(d1);
}

//miller rabin primality test function
bool is_prime(mpz_t n, uint64_t iters) {
    if (mpz_cmp_ui(n, 2) < 0 || mpz_cmp_ui(n, 4) == 0) {
        return false;
    }
    if (mpz_cmp_ui(n, 4) < 0) {
        return true;
    }
    uint64_t j, s = 0;
    mpz_t a, r, y, d, t, g;
    mpz_inits(a, r, y, d, t, g, NULL);
    mpz_set_ui(d, 2);
    mpz_sub_ui(t, n, 1);
    mpz_sub_ui(r, n, 1);
    mpz_sub_ui(g, n, 3);
    while (mpz_fdiv_ui(r, 2) == 0) { //r%2==0
        s++;
        mpz_fdiv_q_ui(r, r, 2); // r = r/2
    }
    for (uint64_t i = 1; i <= iters; i++) {
        mpz_urandomm(a, state, g);
        mpz_add_ui(a, a, 2); //choose random 2 <= a <= n-2
        pow_mod(y, a, r, n);
        if (mpz_cmp_ui(y, 1) != 0 && mpz_cmp(y, t) != 0) {
            j = 1;
            while (j < s && mpz_cmp(y, t) != 0) {
                pow_mod(y, y, d, n);
                if (mpz_cmp_ui(y, 1) == 0) {
                    return false;
                }
                j = j + 1;
            }
            if (mpz_cmp(y, t) != 0) {
                return false;
            }
        }
    }
    mpz_clears(a, r, y, d, t, g, NULL);
    return true;
}

//function to create a prime number of at least bits number of bits
void make_prime(mpz_t p, uint64_t bits, uint64_t iters) {
    mpz_t base, power;
    mpz_inits(base, power, NULL);
    mpz_set_ui(base, 2);
    mpz_pow_ui(power, base, bits);
    mpz_urandomb(p, state, bits);
    mpz_add(p, p, power);
    while (!is_prime(p, iters)) {
        mpz_urandomb(p, state, bits);
        mpz_add(p, p, power);
    }
    mpz_clears(base, power, NULL);
}
