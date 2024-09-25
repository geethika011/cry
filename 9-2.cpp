#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MATRIX_SIZE 2 // 2x2 Hill cipher for simplicity

// Function to perform matrix multiplication modulo 26
void matrix_mult(int result[MATRIX_SIZE][MATRIX_SIZE], int a[MATRIX_SIZE][MATRIX_SIZE], int b[MATRIX_SIZE], int mod) {
    for (int i = 0; i < MATRIX_SIZE; i++) {
        result[i][0] = 0;
        for (int j = 0; j < MATRIX_SIZE; j++) {
            result[i][0] += a[i][j] * b[j];
        }
        result[i][0] %= mod;
    }
}

// Function to encrypt plaintext using the Hill cipher
void hill_encrypt(int key[MATRIX_SIZE][MATRIX_SIZE], char *plaintext, char *ciphertext) {
    int length = strlen(plaintext);
    int mod = 26; // For English alphabet
    int pt_vector[MATRIX_SIZE];

    for (int i = 0; i < length; i += MATRIX_SIZE) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            if (i + j < length) {
                pt_vector[j] = plaintext[i + j] - 'A'; // Convert char to int
            } else {
                pt_vector[j] = 0; // Padding if needed
            }
        }
        
        int result[MATRIX_SIZE][MATRIX_SIZE];
        matrix_mult(result, key, pt_vector, mod);

        for (int j = 0; j < MATRIX_SIZE; j++) {
            ciphertext[i + j] = (result[j][0] + 'A'); // Convert int back to char
        }
    }
    ciphertext[length] = '\0'; // Null terminate
}

// Function to calculate the determinant of a 2x2 matrix
int determinant(int key[MATRIX_SIZE][MATRIX_SIZE]) {
    return (key[0][0] * key[1][1] - key[0][1] * key[1][0]) % 26;
}

// Function to calculate the modular inverse of a number modulo m
int mod_inverse(int a, int m) {
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1) {
            return x;
        }
    }
    return -1; // No modular inverse
}

// Function to calculate the inverse of the key matrix
void matrix_inverse(int key[MATRIX_SIZE][MATRIX_SIZE], int inv[MATRIX_SIZE][MATRIX_SIZE]) {
    int det = determinant(key);
    int det_inv = mod_inverse(det, 26);

    if (det_inv == -1) {
        printf("No inverse exists for the key matrix\n");
        exit(1);
    }

    // Inverse for 2x2 matrix
    inv[0][0] = (key[1][1] * det_inv) % 26;
    inv[0][1] = (-key[0][1] * det_inv) % 26;
    inv[1][0] = (-key[1][0] * det_inv) % 26;
    inv[1][1] = (key[0][0] * det_inv) % 26;

    // Adjust negative values to positive modulo 26
    for (int i = 0; i < MATRIX_SIZE; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            if (inv[i][j] < 0) {
                inv[i][j] += 26;
            }
        }
    }
}

// Function to decrypt ciphertext using the Hill cipher
void hill_decrypt(int key[MATRIX_SIZE][MATRIX_SIZE], char *ciphertext, char *plaintext) {
    int inv_key[MATRIX_SIZE][MATRIX_SIZE];
    matrix_inverse(key, inv_key);

    int length = strlen(ciphertext);
    int mod = 26; // For English alphabet
    int ct_vector[MATRIX_SIZE];

    for (int i = 0; i < length; i += MATRIX_SIZE) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            if (i + j < length) {
                ct_vector[j] = ciphertext[i + j] - 'A'; // Convert char to int
            } else {
                ct_vector[j] = 0; // Padding if needed
            }
        }
        
        int result[MATRIX_SIZE][MATRIX_SIZE];
        matrix_mult(result, inv_key, ct_vector, mod);

        for (int j = 0; j < MATRIX_SIZE; j++) {
            plaintext[i + j] = (result[j][0] + 'A'); // Convert int back to char
        }
    }
    plaintext[length] = '\0'; // Null terminate
}

int main() {
    // Example key matrix for the Hill cipher
    int key[MATRIX_SIZE][MATRIX_SIZE] = {
        {6, 24},
        {1, 13}
    };

    // Input plaintext
    char plaintext[] = "HELLOHILL";
    char ciphertext[256];
    char decryptedtext[256];

    // Encrypting the plaintext
    hill_encrypt(key, plaintext, ciphertext);
    printf("Ciphertext: %s\n", ciphertext);

    // Decrypting the ciphertext
    hill_decrypt(key, ciphertext, decryptedtext);
    printf("Decrypted Text: %s\n", decryptedtext);

    // Example of a known plaintext attack
    // Assume we have plaintext "HELLO" and ciphertext "KDMVQ" pairs
    char known_plaintext[] = "HELLO";
    char known_ciphertext[] = "KDMVQ";
    
    // This section would simulate using known plaintext-ciphertext pairs to recover the key.
    // For a more comprehensive attack, one could implement a more complex analysis.
    // Here, we just display that the pairs exist.

    printf("Known Plaintext: %s\n", known_plaintext);
    printf("Known Ciphertext: %s\n", known_ciphertext);
    
    return 0;
}