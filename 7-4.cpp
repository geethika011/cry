
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
unsigned int hash_function(const char *message) {
    unsigned int hash = 0;
    while (*message) {
        hash = (hash << 5) + *message++;
    }
    return hash;
}
void dsa_sign(const char *message, unsigned int *r, unsigned int *s) {
    unsigned int k = rand() % 1000 + 1; 
    unsigned int hash = hash_function(message);
    unsigned int private_key = 12345; 
    unsigned int p = 104729; 
    unsigned int q = 104723; 
    unsigned int g = 2;
    *r = (g * k) % p % q;
    *s = ((hash + private_key * (*r)) * k) % q;
}
int main() {
    srand(time(NULL)); 
    const char *message = "Hello, this is a test message for DSA.";
    unsigned int r1, s1, r2, s2;
    dsa_sign(message, &r1, &s1);
    printf("First signature: r = %u, s = %u\n", r1, s1);
    dsa_sign(message, &r2, &s2);
    printf("Second signature: r = %u, s = %u\n", r2, s2);
    if (r1 != r2 || s1 != s2) {
        printf("The signatures are different, as expected.\n");
    } else {
        printf("The signatures are the same, which should not happen in DSA.\n");
    }
    return 0;
}

