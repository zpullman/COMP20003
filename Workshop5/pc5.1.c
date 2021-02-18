#include <stdio.h>
#include <stdlib.h>

#define N 133
#define E 5
#define D 11

/* Returns an int representing the given
    value encrypted using RSA using the
    given parameters. */
unsigned int encrypt(unsigned int n, 
    unsigned int e, unsigned int value);

/* Returns an int representing the given
    value decrypted using RSA using the
    given parameters.
*/
unsigned int decrypt(unsigned int n,
    unsigned int d, unsigned int value);

unsigned int encrypt(unsigned int n, 
    unsigned int e, unsigned int value){
    /* Do (value^e) mod n */
    
    
    
    
}

unsigned int decrypt(unsigned int n,
    unsigned int d, unsigned int value){
    /* Do (value^d) mod n. */
    return encrypt(n, d, value);
}

int main(int argc, char *argv){
    /* The keys to encrypt */
    unsigned int toEncrypt[] = {72, 63, 14, 72, 72, 131, 95, 107, 92, 104, 51, 
        24, 54, 14, 92, 72, 10, 95, 131, 96, 21, 104, 47, 25, 131, 95, 24};
    unsigned int toDecrypt[] = {96, 51, 13, 51, 129, 96, 73, 7, 41, 7, 80, 6, 
        109, 80, 2, 8, 2, 6, 56, 7, 41, 41, 124, 8, 57, 7};

    int i;
    
    for(i = 0; i < sizeof(toEncrypt)/sizeof(toEncrypt[0]); i++){
        printf("%c",encrypt(N, E, toEncrypt[i]));
    }
    for(i = 0; i < sizeof(toDecrypt)/sizeof(toDecrypt[0]); i++){
        printf("%c",decrypt(N, D, toDecrypt[i]));
    }
    printf("\n");
    
    return 0;
}