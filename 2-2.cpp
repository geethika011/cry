#include <stdio.h>

// Function to compute GCD (greatest common divisor)
int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// Function to find the modular inverse of a under modulo m
int mod_inverse(int a, int m) {
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1)
            return x;
    }
    return -1; // No modular inverse found
}

// Function to decrypt ciphertext using the affine cipher
void affine_decrypt(char ciphertext[], int a, int b) {
    int a_inv = mod_inverse(a, 26); // Find modular inverse of 'a'

    if (a_inv == -1) {
        printf("No modular inverse for a = %d under modulo 26.\n", a);
        return;
    }

    printf("Decrypted text: ");
    for (int i = 0; ciphertext[i] != '\0'; i++) {
        char ch = ciphertext[i];

        if (ch >= 'A' && ch <= 'Z') {
            // Apply the affine decryption formula for uppercase letters
            int C = ch - 'A';
            int p = (a_inv * (C - b + 26)) % 26;
            printf("%c", 'A' + p);
        } else if (ch >= 'a' && ch <= 'z') {
            // Apply the affine decryption formula for lowercase letters
            int C = ch - 'a';
            int p = (a_inv * (C - b + 26)) % 26;
            printf("%c", 'a' + p);
        } else {
            // Non-alphabet characters are unchanged
            printf("%c", ch);
        }
    }
    printf("\n");
}

int main() {
    char ciphertext[100];
    int a, b;

   
    a = 7;
    b = 23;

    // Input the ciphertext
    printf("Enter the ciphertext: ");
    fgets(ciphertext, sizeof(ciphertext), stdin);

    // Decrypt the ciphertext
    affine_decrypt(ciphertext, a, b);

    return 0;
}