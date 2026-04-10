/* step_3_2.c */
/* THIS PROGRAM displays message signing w/ RSA */

#include "general.h"


int main()
{

    char buffer[1024]; // will hold msg hex in this case
    char *msg = "I owe you $2000";
    // Declare 
    BN_CTX *ctx = BN_CTX_new();
    BIGNUM *n = BN_new(); // modulos
    BIGNUM *e = BN_new(); // pub key
    BIGNUM *s = BN_new(); // our signature
    BIGNUM *M = BN_new(); // message in BN 
    BIGNUM *d = BN_new(); // our priv key
    // Initialize 
    BN_hex2bn(&e, "010001");
    BN_hex2bn(&n, "DCBFFE3E51F62E09CE7032E2677A78946A849DC4CDDE3A4D0CB81629242FB1A5");
    BN_hex2bn(&d, "74D806F9F3A62BAE331FFE3F0A68AFE35B3D2E4794148AACBC26AA381CD7D30D");
    // convert msg to hex 
    convert_buff(msg, "utf_hex", buffer, sizeof(buffer));
    // convert hexmsg to BN
    BN_hex2bn(&M, buffer);
    
    // To sign a message, we just apply RSA with our priv key!
    // For this example, do not use hash directly

    // Sign message "I owe you $2000" directly 
    // C = M^d mod n
    BN_mod_exp(s, M, d, n, ctx);

    printLR("Msg string:", msg);
    printLR("Msg in hex:", buffer);
    printLR("Hex Signature of Msg:", BN_bn2hex(s));
    printf("\n");

    // Let's make a new msg and compare the signature
    BIGNUM *M2 = BN_new();
    char *msg2 = "I owe you $5000";
    convert_buff(msg2, "utf_hex", buffer, sizeof(buffer));
    
    BN_hex2bn(&M2, buffer);
    BN_mod_exp(s, M2, d, n, ctx);

    printLR("Msg2 string:", msg2);
    printLR("Msg2 in hex:", buffer);
    printLR("Hex Signature of Msg2:", BN_bn2hex(s));


    




    return 0;
}