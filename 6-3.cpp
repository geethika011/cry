#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 2 // Size of the key matrix (2x2)

// Function to get the modulus of a number
int mod(int a, int b) {
    return (a % b + b) % b;
}

// Function to calculate the inverse of a matrix modulo 26
void matrix_inverse(int key[SIZE][SIZE], int inv[SIZE][SIZE]) {
    int det = (key[0][0] * key[1][1] - key[0][1] * key[1][0]) % 26;
    det = mod(det, 26);
    
    // Calculate modular inverse of determinant
    int det_inv = -1;
    for (int i = 1; i < 26; i++) {
        if ((det * i) % 26 == 1) {
            det_inv = i;
            break;
        }
    }
    
    // Calculate adjugate matrix
    inv[0][0] = key[1][1] * det_inv % 26;
    inv[0][1] = -key[0][1] * det_inv % 26;
    inv[1][0] = -key[1][0] * det_inv % 26;
    inv[1][1] = key[0][0] * det_inv % 26;
}

// Function to encrypt plaintext using the Hill cipher
void hill_encrypt(char *plaintext, int key[SIZE][SIZE], char *ciphertext) {
    int len = strlen(plaintext);
    for (int i = 0; i < len; i += SIZE) {
        int p[SIZE] = {0}; // Plaintext vector
        for (int j = 0; j < SIZE; j++) {
            if (i + j < len) {
                p[j] = plaintext[i + j] - 'a'; // Convert char to index
            }
        }
        
        // Encryption
        for (int j = 0; j < SIZE; j++) {
            ciphertext[i + j] = mod(key[j][0] * p[0] + key[j][1] * p[1], 26) + 'a';
        }
    }
    ciphertext[len] = '\0'; // Null-terminate the ciphertext
}

// Function to decrypt ciphertext using the Hill cipher
void hill_decrypt(char *ciphertext, int key[SIZE][SIZE], char *plaintext) {
    int inv[SIZE][SIZE];
    matrix_inverse(key, inv); // Get the inverse key matrix

    int len = strlen(ciphertext);
    for (int i = 0; i < len; i += SIZE) {
        int c[SIZE] = {0}; // Ciphertext vector
        for (int j = 0; j < SIZE; j++) {
            c[j] = ciphertext[i + j] - 'a'; // Convert char to index
        }
        
        // Decryption
        for (int j = 0; j < SIZE; j++) {
            plaintext[i + j] = mod(inv[j][0] * c[0] + inv[j][1] * c[1], 26) + 'a';
        }
    }
    plaintext[len] = '\0'; // Null-terminate the plaintext
}

// Main function to demonstrate the Hill cipher
int main() {
    int key[SIZE][SIZE] = {{9, 4}, {5, 7}}; // Example key matrix
    char plaintext[100] = "meetme";
    char ciphertext[100];
    char decrypted[100];

    // Encrypt the plaintext
    hill_encrypt(plaintext, key, ciphertext);
    printf("Ciphertext: %s\n", ciphertext);

    // Decrypt the ciphertext
    hill_decrypt(ciphertext, key, decrypted);
    printf("Decrypted: %s\n", decrypted);

    // Chosen plaintext attack example
    // Assume we have the pairs (plaintext, ciphertext) to recover the key
    // In a real scenario, this part would involve more sophisticated matrix calculations.
    // For demonstration, we just reprint the key matrix.
    printf("Key used for encryption:\n");
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            printf("%d ", key[i][j]);
        }
        printf("\n");
    }

    return 0;
}