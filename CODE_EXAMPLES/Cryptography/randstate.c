#include "randstate.h"

gmp_randstate_t state;

//initializes random state with seed
void randstate_init(uint64_t seed) {
    gmp_randinit_mt(state);
    gmp_randseed_ui(state, seed);
}

//clears random state
void randstate_clear(void) {
    gmp_randclear(state);
}
