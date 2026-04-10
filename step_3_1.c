/* step_3_1.c */
// This program computes private key
// given p, q, and the pub key
// It displays the use of the extended euclidean alg. 
// as well as the basic use of BIGNUM
#include "general.h"

int main()
{
    /*p = F7E75FDC469067FFDC4E847C51F452DF
    q = E85CED54AF57E53E092113E62F436F4F
    e = 0D88C3*/
    // RSA EXPLAINED 
    // each are prime... n = p * q
    // pub key is e,n
    // calc the private key d 

    //  n = pq (our modulo)
    // d * e = 1 mod eulertotient(n)
    // totient(n) = (p-1)(q-1)
    // find e*d = 1 mod (totient(n)) --> extended euclidean solves this
    // gcd(e,totient(n)) = s*e + t*totient(n) ---- 
    // open ssl can hekp us calc d = 1/e mod tot_n

    //      encrypt with C = M^e  mod n 
    //      decrypt with M = C^d   (d is the priv)
    BN_CTX *ctx = BN_CTX_new();
    BIGNUM *p = BN_new();
    BIGNUM *q = BN_new();
    BIGNUM *e = BN_new();
    BIGNUM *d = BN_new();
    BIGNUM *n = BN_new(); // modulo
    BIGNUM *tot_n = BN_new(); //totient of modulo

    BN_hex2bn(&p, "F7E75FDC469067FFDC4E847C51F452DF");
    BN_hex2bn(&q, "E85CED54AF57E53E092113E62F436F4F");
    BN_hex2bn(&e, "0D88C3");

    // mod calc
    BN_mul(n, p, q, ctx);

    // calcing totient )becomes tot_n
    BIGNUM *p_min = BN_new();
    BIGNUM *q_min = BN_new();
    
    BN_sub(p_min, p, BN_value_one()); // write BN val one as a func LOLOLOL 
    BN_sub(q_min, q, BN_value_one());

    BN_mul(tot_n, p, q, ctx);

    // we already chose e, so calc d 
    BN_mod_inverse(d, e, tot_n, ctx);
    printBN("d value (decimal): ", d);

    char *buff;
    buff = BN_bn2hex(d); // BN does it for us!
    printf(LR_FORMAT, KRED, "d value (hex)", KYEL, buff);

    // Let's write this hex to a file to use later
    FILE *f = fopen("RSA_priv.txt", "w");
    if (f == NULL)
    {  
        printf(LR_FORMAT, KRED, "COULD NOT CREATE/OPEN/WRITE: ", KYEL, "RSA_priv.txt");
        return 1;
    }
    else // not really needed since we have return, but for cleanliness
    {
        fputs(buff, f);
        fclose(f);
        printf("%s\tSUCCESSFULLY WRITTEN TO RSA_priv.txt%s\n", KRED,KNRM);
    }

    return 0; 
}
