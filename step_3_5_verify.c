/* step_3_5_verify.c */
/* THIS PROGRAM displays message verification w/ RSA */
/* Reminder: actual signatures are hashed then encrypted */
/* Only the principle is displayed here... */

#include "general.h"

    // assume that
    // (1) We got a msg
    // (2) We have the sig
    // (3) We must verify sig by checking if it is the same as the msg sig
    // (4) We can do so with e, n, M, and S
// given a signature, let's verify (returns True = matches)
bool VerifySignature(char *msg, BIGNUM *sig, BIGNUM *pubk, BIGNUM *n)
{
    //
    char buffer[1024]; 
    BN_CTX *ctx = BN_CTX_new();
    BIGNUM *msg_bn = BN_new();
    BIGNUM *res = BN_new(); // BN of verified (decrypted msg)
    // Declare known value
    //TODO Create a BN for the msg (we will match this with decrypted SIG)
    convert_buff(msg, "utf_hex", buffer, sizeof(buffer)); 
    BN_hex2bn(&msg_bn, buffer);
    // Now lets decrypt (verify the given sig)
    // S^e mod n 
    BN_mod_exp(res, sig, pubk, n, ctx);

    printLR("Message: ", msg);
    printLR("Msg Hex:", buffer);
    printBN("Msg BN:", msg_bn);
    printBN("Checked Result:", res);
    printf("\n");
    
    if (BN_cmp(res, msg_bn) == 0)   // BN_cmp returns 0 for true
    {
        return true;
    }


    return false;
}

int main()
{

    char buffer[1024]; // will hold msg hex in this case
    char buffer2[1024];
    char *msg = "Launch a missile.";
    // Declare BN and ctx
    BN_CTX *ctx = BN_CTX_new();
    BIGNUM *M = BN_new(); // message in BN
    BIGNUM *S = BN_new(); // signature
    BIGNUM *e = BN_new(); // pub key
    BIGNUM *n = BN_new(); // modulo
    BIGNUM *res = BN_new(); // verifying result msg
    // Initialize BN stuff
    BN_hex2bn(&S, "643D6F34902D9C7EC90CB0B2BCA36C47FA37165C0005CAB026C0542CBDB6802F");
    BN_hex2bn(&e,"010001");
    BN_hex2bn(&n,"AE1CD4DC432798D933779FBD46C6E1247F0CF1233595113AA51B450F18116115");


    if(VerifySignature(msg, S, e, n))
    {
        printf(LR_FORMAT, KYEL, "RESULT", KGRN, "VERIFIED");
    }
    else
    {
        printf(LR_FORMAT, KYEL, "RESULT", KRED, "NOT VERIFIED");
    }

    return 0;
}
