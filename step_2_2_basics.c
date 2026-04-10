/* step_2_2_basic.c */

#include "general.h"

int main()
{
    // create holder for temp allocations //easier to free
    BN_CTX *ctx = BN_CTX_new();
    // DECLARE // 
    BIGNUM *a = BN_new();
    BIGNUM *b = BN_new();
    BIGNUM *n = BN_new();
    BIGNUM *res = BN_new();

    // INITIALIZE // 
    // a rand prime, b defined dec, n rand
    BN_generate_prime_ex(a, NBITS, 1, NULL, NULL, NULL);
    BN_dec2bn(&b, "273489463796838501848592769467194369268");
    BN_rand(n, NBITS, 0, 0);

    // res = a * b 
    BN_mul(res, a, b, ctx);
    printBN("[a * b]", res);

    // mod prev result with 11
    BIGNUM *eleven = BN_new();
    BN_dec2bn(&eleven, "11");
    BN_mod(res, res, eleven, ctx);
    printBN("[res mod 11]", res);

    // res = a^b mod n
    BN_mod_exp(res, a, b, n, ctx);
    printBN("[a^c mod n]", res);

    return 0;
}