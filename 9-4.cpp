#include <stdio.h>

// Function to compute the GCD using the Euclidean algorithm
int gcd(int a, int b) {
    while (b != 0) {
        int t = b;
        b = a % b;
        a = t;
    }
    return a;
}

// Function to find the multiplicative inverse of e modulo phi using Extended Euclidean Algorithm
int extended_gcd(int a, int b, int *x, int *y) {
    if (a == 0) {
        *x = 0;
        *y = 1;
        return b;
    }
    
    int x1, y1; // To store results of recursive call
    int gcd = extended_gcd(b % a, a, &x1, &y1);
    
    *x = y1 - (b / a) * x1;
    *y = x1;
    
    return gcd;
}

// Function to find the modular inverse
int mod_inverse(int e, int phi) {
    int x, y;
    int g = extended_gcd(e, phi, &x, &y);
    
    if (g != 1) {
        printf("Inverse doesn't exist\n");
        return -1; // Inverse doesn't exist
    } else {
        // m is added to handle negative x
        int res = (x % phi + phi) % phi;
        return res;
    }
}

// Function to find p and q by trial and error
void find_p_q(int n, int *p, int *q) {
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            *p = i;
            *q = n / i;
            return;
        }
    }
}

int main() {
    int n = 3599;   // Modulus
    int e = 31;    // Public exponent
    int p, q;

    // Find p and q
    find_p_q(n, &p, &q);
    printf("Found primes: p = %d, q = %d\n", p, q);

    // Calculate phi(n)
    int phi = (p - 1) * (q - 1);
    printf("phi(n) = %d\n", phi);

    // Calculate the private key (d)
    int d = mod_inverse(e, phi);
    printf("Private key (d) = %d\n", d);

    return 0;
}