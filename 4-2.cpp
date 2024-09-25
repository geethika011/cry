#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Function to compute gcd
int gcd(int a, int b) {
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

// Function to factor n given a common factor with plaintext m
void factor_n(int n, int m) {
    int common_factor = gcd(n, m);
    
    if (common_factor > 1 && common_factor < n) {
        int p = common_factor; // Assume p is the common factor
        int q = n / p; // Calculate q
        
        printf("Common Factor Found: %d\n", p);
        printf("Corresponding Factor: %d\n", q);
        printf("n = p * q = %d * %d = %d\n", p, q, p * q);
    } else {
        printf("No valid common factor found.\n");
    }
}

int main() {
    // Example values for n and m
    int n = 3233; // Example: 61 * 53
    int m = 61;   // Assume one plaintext block has a common factor of 61 with n
    
    printf("Given n: %d\n", n);
    printf("Given plaintext block m: %d\n", m);
    
    // Attempt to factor n using the common factor m
    factor_n(n, m);

    return 0;
}