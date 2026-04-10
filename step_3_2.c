/* step_3_2.c */
/* THIS PROGRAM displays encryption & decryption
   When we are provided with 
   n, e, M, d
   */

#include "general.h"

int main()
{

    char buffer[1024];
    char *M = "A top secret!";
    // DECLARATION // 
    BN_CTX *ctx = BN_CTX_new();
    BIGNUM *m = BN_new(); // msg as big num
    BIGNUM *e = BN_new();//pub key
    BIGNUM *d = BN_new(); //priv key
    BIGNUM *n = BN_new(); // our n val
    BIGNUM *c = BN_new(); //encrypted RSA M
    // INITIALIZATION // 
    BN_hex2bn(&e, "010001"); // pub key
   BN_hex2bn(&n, "DCBFFE3E51F62E09CE7032E2677A78946A849DC4CDDE3A4D0CB81629242FB1A5");
   BN_hex2bn(&e, "010001"); // pub key
   // M is converted later after we convert to hex
   BN_hex2bn(&d, "74D806F9F3A62BAE331FFE3F0A68AFE35B3D2E4794148AACBC26AA381CD7D30D");
    
    // converts with python lib (child process)
    // msg (arg1), function type (arg2), buffer we use, and size of our buffer
    convert_buff(M,"utf_hex", buffer, sizeof(buffer));
    printf(LR_FORMAT, KRED, "M string:", KYEL, M);
    printf(LR_FORMAT, KRED, "M in hex:", KYEL, buffer);
    // apply it to our BN 
    BN_hex2bn(&m, buffer);
    printBN("M as BN: ", m);

    //ENCRYPTION is C = M^e mod n (easy)
    BN_mod_exp(c, m, e, n, ctx);

    printBN("RSA Encrypted (C): ", c);
    // DECRYPTION IS M = C^d mod n (easy shmeezy)
    BIGNUM *decM = BN_new();

    BN_mod_exp(decM, c, d, n, ctx);
    char *dec_m_hex = BN_bn2hex(decM);
    convert_buff(dec_m_hex, "from_hex", buffer, sizeof(buffer));
    printLR("Decrypted C as str", buffer);
    



    return 0;
}