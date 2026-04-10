/* step_2_1_basics.c */

#include "general.h"

int main()
{
    // Some library funcs require temp variables
    // Dynamic mem allocation for BIGNUMs is expensive with repeated subroutine calls
    // BN_CTX structure holds BIGNUM temp variables used by library functions
    // Pass to functions that require
    BN_CTX *ctx = BN_CTX_new();  // temp allocations easily freed

    //Initialize BIGNUM variable
    BIGNUM *a = BN_new();
    BIGNUM *b = BN_new();
    BIGNUM *c = BN_new();
    BIGNUM *d = BN_new();
    BIGNUM *res = BN_new();
    // #Assigning a BIGNUM variable# //
    
    // val from decimal number string
    BN_dec2bn(&a, "12345678901112231223");
    printBN("[dec2bn <a>]:", a);

    // Assign a value froma  hex number string
    BN_hex2bn(&b, "2A2B4C5FF77889AED3F");
    printBN("[hex2bn <b>]:", b);

    // Generate Random number of 128 bits
    BN_rand(c, 128, 0, 0);
    printBN("[rand <c>]:", c);
    // Generate rand prime num of 128 bits
    BN_generate_prime_ex(d, 128, 1, NULL, NULL, NULL);
    printBN("randprimeex <d>]", d);

    // #OPERATIONS# most equire the BN_CTX structure//

    BN_sub(res, a, b);
    printBN("bn sub a - b --> ", res);

    BN_add(res, a, b);
    printBN("bn a + b --> ", res);

    BN_mul(res, c, d, ctx);
    printBN("c * d --> ", res);

    // res = a * b mod n
    BIGNUM *eleven = BN_new();
    BN_dec2bn(&eleven, "11");
    BN_mod_mul(res, c, d, eleven, ctx);
    printBN("a * b mod 11", res);

    // res = a^c mod n
    BIGNUM *thirteen = BN_new();
    BN_mod_exp(res, a, thirteen, eleven, ctx);
    printBN("a^13 mod 11 -->", res);

    // compute mod inverse of a * b mod n = 1 (b inverse of a) 
    BN_mod_inverse(res, a, d, ctx);
    printBN("[inverse 1/a mod d] ", res);



    // END PROG RUN n FREE // 
    printf("%s%s", KNRM, "\t-----[END --> Now (FREEING)]-----\n");
    
    OPENSSL_free(a);
    OPENSSL_free(b);
    OPENSSL_free(c);
    OPENSSL_free(d);
    OPENSSL_free(res);
    BN_free(eleven);
    BN_free(thirteen);
    //BN_CTX_end(ctx);
    BN_CTX_free(ctx);

    return 0;
}