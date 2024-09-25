#include <stdio.h>

// Function to compute GCD of two numbers
int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// Function to encrypt plaintext using Affine Caesar Cipher
void affine_encrypt(char plaintext[], int a, int b) {
    if (gcd(a, 26) != 1) {
        printf("Invalid value of 'a'. It must be coprime with 26.\n");
        return;
    }
    
    printf("Encrypted text: ");
    for (int i = 0; plaintext[i] != '\0'; i++) {
        char ch = plaintext[i];
        
        if (ch >= 'A' && ch <= 'Z') {
            // Apply the affine encryption formula for uppercase letters
            ch = ((a * (ch - 'A') + b) % 26) + 'A';
        } else if (ch >= 'a' && ch <= 'z') {
            // Apply the affine encryption formula for lowercase letters
            ch = ((a * (ch - 'a') + b) % 26) + 'a';
        }

        // Output the encrypted character
        printf("%c", ch);
    }
    printf("\n");
}

// Function to find the modular inverse of 'a' under modulo 26
int mod_inverse(int a, int m) {
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1)
            return x;
    }
    return -1;
}

// Function to decrypt ciphertext using Affine Caesar Cipher
void affine_decrypt(char ciphertext[], int a, int b) {
    if (gcd(a, 26) != 1) {
        printf("Invalid value of 'a'. It must be coprime with 26.\n");
        return;
    }

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
            ch = (a_inv * ((ch - 'A' - b + 26) % 26)) % 26 + 'A';
        } else if (ch >= 'a' && ch <= 'z') {
            // Apply the affine decryption formula for lowercase letters
            ch = (a_inv * ((ch - 'a' - b + 26) % 26)) % 26 + 'a';
        }

        // Output the decrypted character
        printf("%c", ch);
    }
    printf("\n");
}

int main() {
    char text[100];
    int a, b;
    int choice;

    // Input choice for encryption or decryption
    printf("Affine Caesar Cipher\n");
    printf("1. Encrypt\n2. Decrypt\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    // Input key values 'a' and 'b'
    printf("Enter value for 'a' (should be coprime with 26): ");
    scanf("%d", &a);
    printf("Enter value for 'b': ");
    scanf("%d", &b);

    // Input the text (plaintext or ciphertext)
    printf("Enter the text: ");
    scanf(" %[^\n]%*c", text);  // Reads input with spaces

    // Perform encryption or decryption based on the choice
    if (choice == 1) {
        affine_encrypt(text, a, b);
    } else if (choice == 2) {
        affine_decrypt(text, a, b);
    } else {
        printf("Invalid choice.\n");
    }

    return 0;
}