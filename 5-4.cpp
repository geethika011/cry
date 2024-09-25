#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MATRIX_SIZE 2 // 2x2 matrix for Hill Cipher
#define ALPHABET_SIZE 26
#define MAX_TEXT_LENGTH 1000

// Function to get the modulus of a number
int mod(int a, int b) {
    return (a % b + b) % b; // Ensures the result is non-negative
}

// Function to calculate the determinant of a matrix
int determinant(int matrix[MATRIX_SIZE][MATRIX_SIZE]) {
    return (matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0]) % ALPHABET_SIZE;
}

// Function to calculate the modular inverse of a number
int mod_inverse(int a, int m) {
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1) {
            return x;
        }
    }
    return -1; // No modular inverse exists
}

// Function to calculate the inverse of the key matrix
void inverse_matrix(int key[MATRIX_SIZE][MATRIX_SIZE], int inverse[MATRIX_SIZE][MATRIX_SIZE]) {
    int det = determinant(key);
    int det_inv = mod_inverse(det, ALPHABET_SIZE);

    if (det_inv == -1) {
        printf("Matrix is not invertible\n");
        exit(1);
    }

    inverse[0][0] = (key[1][1] * det_inv) % ALPHABET_SIZE;
    inverse[0][1] = (-key[0][1] * det_inv) % ALPHABET_SIZE;
    inverse[1][0] = (-key[1][0] * det_inv) % ALPHABET_SIZE;
    inverse[1][1] = (key[0][0] * det_inv) % ALPHABET_SIZE;
}

// Function to encrypt plaintext using the Hill cipher
void encrypt(char *plaintext, int key[MATRIX_SIZE][MATRIX_SIZE], char *ciphertext) {
    int len = strlen(plaintext);
    for (int i = 0; i < len; i += MATRIX_SIZE) {
        int block[MATRIX_SIZE] = {0};
        for (int j = 0; j < MATRIX_SIZE; j++) {
            if (i + j < len) {
                block[j] = plaintext[i + j] - 'A'; // Convert char to index
            }
        }

        int encrypted[MATRIX_SIZE] = {0};
        for (int j = 0; j < MATRIX_SIZE; j++) {
            for (int k = 0; k < MATRIX_SIZE; k++) {
                encrypted[j] += key[j][k] * block[k];
            }
            encrypted[j] = mod(encrypted[j], ALPHABET_SIZE); // Modulo 26
            ciphertext[i + j] = encrypted[j] + 'A'; // Convert index back to char
        }
    }
    ciphertext[len] = '\0'; // Null-terminate the string
}

// Function to decrypt ciphertext using the Hill cipher
void decrypt(char *ciphertext, int key[MATRIX_SIZE][MATRIX_SIZE], char *plaintext) {
    int inverse[MATRIX_SIZE][MATRIX_SIZE];
    inverse_matrix(key, inverse);

    int len = strlen(ciphertext);
    for (int i = 0; i < len; i += MATRIX_SIZE) {
        int block[MATRIX_SIZE] = {0};
        for (int j = 0; j < MATRIX_SIZE; j++) {
            if (i + j < len) {
                block[j] = ciphertext[i + j] - 'A'; // Convert char to index
            }
        }

        int decrypted[MATRIX_SIZE] = {0};
        for (int j = 0; j < MATRIX_SIZE; j++) {
            for (int k = 0; k < MATRIX_SIZE; k++) {
                decrypted[j] += inverse[j][k] * block[k];
            }
            decrypted[j] = mod(decrypted[j], ALPHABET_SIZE); // Modulo 26
            plaintext[i + j] = decrypted[j] + 'A'; // Convert index back to char
        }
    }
    plaintext[len] = '\0'; // Null-terminate the string
}

int main() {
    int key[MATRIX_SIZE][MATRIX_SIZE] = {
        {9, 4},
        {5, 7}
    };

    // The message to be encrypted
    char plaintext[] = "MEETMEATTHEUSUALPLACEATTENRATHERTHANEIGHTOCLOCK";
    char ciphertext[MAX_TEXT_LENGTH];

    // Encrypt the plaintext
    encrypt(plaintext, key, ciphertext);
    printf("Ciphertext: %s\n", ciphertext);

    // Decrypt the ciphertext
    char decrypted_text[MAX_TEXT_LENGTH];
    decrypt(ciphertext, key, decrypted_text);
    printf("Decrypted Text: %s\n", decrypted_text);

    return 0;
}