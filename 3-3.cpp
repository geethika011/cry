#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MATRIX_SIZE 2
#define MOD 26

// Function to print the matrix
void print_matrix(int matrix[MATRIX_SIZE][MATRIX_SIZE]) {
    for (int i = 0; i < MATRIX_SIZE; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

// Function to calculate the modular inverse of a number
int mod_inverse(int a, int m) {
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1)
            return x;
    }
    return -1; // No modular inverse
}

// Function to calculate the determinant of a 2x2 matrix
int determinant(int matrix[MATRIX_SIZE][MATRIX_SIZE]) {
    return (matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0]) % MOD;
}

// Function to find the inverse of the 2x2 matrix
void inverse_matrix(int matrix[MATRIX_SIZE][MATRIX_SIZE], int inverse[MATRIX_SIZE][MATRIX_SIZE]) {
    int det = determinant(matrix);
    int inv_det = mod_inverse(det, MOD);

    // Calculate the inverse matrix
    inverse[0][0] = (matrix[1][1] * inv_det) % MOD;
    inverse[0][1] = (-matrix[0][1] * inv_det + MOD) % MOD;
    inverse[1][0] = (-matrix[1][0] * inv_det + MOD) % MOD;
    inverse[1][1] = (matrix[0][0] * inv_det) % MOD;
}

// Function to encrypt a plaintext message
void encrypt(const char *plaintext, int key[MATRIX_SIZE][MATRIX_SIZE], char *ciphertext) {
    int length = strlen(plaintext);
    int block[MATRIX_SIZE];
    int index = 0;

    // Convert plaintext to ciphertext
    for (int i = 0; i < length; i += MATRIX_SIZE) {
        // Prepare the block
        for (int j = 0; j < MATRIX_SIZE; j++) {
            if (i + j < length && plaintext[i + j] != ' ') {
                block[j] = plaintext[i + j] - 'a'; // Convert char to number (a=0, b=1, ..., z=25)
            } else {
                block[j] = 0; // Padding with 0 for spaces or if the end of the string is reached
            }
        }

        // Encrypt the block
        for (int j = 0; j < MATRIX_SIZE; j++) {
            int sum = 0;
            for (int k = 0; k < MATRIX_SIZE; k++) {
                sum += key[j][k] * block[k];
            }
            ciphertext[index++] = (sum % MOD) + 'a'; // Convert number back to char
        }
    }
    ciphertext[index] = '\0'; // Null terminate the string
}

// Function to decrypt the ciphertext message
void decrypt(const char *ciphertext, int key[MATRIX_SIZE][MATRIX_SIZE], char *plaintext) {
    int inverse[MATRIX_SIZE][MATRIX_SIZE];
    inverse_matrix(key, inverse);
    int length = strlen(ciphertext);
    int block[MATRIX_SIZE];
    int index = 0;

    // Convert ciphertext to plaintext
    for (int i = 0; i < length; i += MATRIX_SIZE) {
        // Prepare the block
        for (int j = 0; j < MATRIX_SIZE; j++) {
            if (i + j < length) {
                block[j] = ciphertext[i + j] - 'a'; // Convert char to number
            }
        }

        // Decrypt the block
        for (int j = 0; j < MATRIX_SIZE; j++) {
            int sum = 0;
            for (int k = 0; k < MATRIX_SIZE; k++) {
                sum += inverse[j][k] * block[k];
            }
            plaintext[index++] = (sum % MOD + MOD) % MOD + 'a'; // Convert number back to char
        }
    }
    plaintext[index] = '\0'; // Null terminate the string
}

int main() {
    const char *plaintext = "meetmeattheusualplaceattenratherthaneightoclock";
    int key[MATRIX_SIZE][MATRIX_SIZE] = {{9, 4}, {5, 7}};
    char ciphertext[100];
    char decrypted[100];

    printf("Plaintext: %s\n", plaintext);

    // Encrypt the plaintext
    encrypt(plaintext, key, ciphertext);
    printf("Ciphertext: %s\n", ciphertext);

    // Decrypt the ciphertext
    decrypt(ciphertext, key, decrypted);
    printf("Decrypted Plaintext: %s\n", decrypted);

    return 0;
}