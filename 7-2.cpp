#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BLOCK_SIZE 8 // Size of the S-DES block in bits
#define KEY_SIZE 10  // Size of the S-DES key in bits

// S-DES key
int key[KEY_SIZE] = {0, 1, 1, 1, 1, 1, 1, 1, 0, 1}; // 0111111101

// S-DES Function Prototypes
void sdes_encrypt(int *plaintext, int *key, int *ciphertext);
void sdes_decrypt(int *ciphertext, int *key, int *plaintext);
void int_to_bin(int value, int *binary);
void bin_to_int(int *binary, int *value);
void print_binary(int *binary, int size);

int main() {
    // Define plaintext and ciphertext
    int plaintext[BLOCK_SIZE * 3] = {0, 0, 0, 0, 0, 0, 0, 1,   // 0000 0001
                                      0, 0, 0, 0, 0, 0, 1, 0,   // 0000 0010
                                      0, 0, 0, 0, 0, 1, 0, 0};  // 0000 0100
    int ciphertext[BLOCK_SIZE * 3];
    int decrypted[BLOCK_SIZE * 3];

    // Define initial counter
    int counter[BLOCK_SIZE] = {0, 0, 0, 0, 0, 0, 0, 0}; // 0000 0000

    // Encrypt
    printf("Plaintext: ");
    print_binary(plaintext, BLOCK_SIZE * 3);
    for (int i = 0; i < 3; i++) {
        int current_counter[BLOCK_SIZE];
        memcpy(current_counter, counter, BLOCK_SIZE * sizeof(int));

        // Encrypt the counter
        int counter_cipher[BLOCK_SIZE];
        sdes_encrypt(current_counter, key, counter_cipher);
        
        // XOR with the plaintext block
        for (int j = 0; j < BLOCK_SIZE; j++) {
            ciphertext[i * BLOCK_SIZE + j] = plaintext[i * BLOCK_SIZE + j] ^ counter_cipher[j];
        }

        // Increment the counter
        for (int j = BLOCK_SIZE - 1; j >= 0; j--) {
            if (counter[j] == 1) {
                counter[j] = 0;
            } else {
                counter[j] = 1;
                break;
            }
        }
    }

    printf("Ciphertext: ");
    print_binary(ciphertext, BLOCK_SIZE * 3);

    // Decrypt
    for (int i = 0; i < 3; i++) {
        int current_counter[BLOCK_SIZE];
        memcpy(current_counter, counter, BLOCK_SIZE * sizeof(int));

        // Encrypt the counter
        int counter_cipher[BLOCK_SIZE];
        sdes_encrypt(current_counter, key, counter_cipher);

        // XOR with the ciphertext block
        for (int j = 0; j < BLOCK_SIZE; j++) {
            decrypted[i * BLOCK_SIZE + j] = ciphertext[i * BLOCK_SIZE + j] ^ counter_cipher[j];
        }

        // Increment the counter
        for (int j = BLOCK_SIZE - 1; j >= 0; j--) {
            if (counter[j] == 1) {
                counter[j] = 0;
            } else {
                counter[j] = 1;
                break;
            }
        }
    }

    printf("Decrypted: ");
    print_binary(decrypted, BLOCK_SIZE * 3);

    return 0;
}

// Function to convert an integer to binary
void int_to_bin(int value, int *binary) {
    for (int i = BLOCK_SIZE - 1; i >= 0; i--) {
        binary[i] = value % 2;
        value /= 2;
    }
}

// Function to convert binary to integer
void bin_to_int(int *binary, int *value) {
    *value = 0;
    for (int i = 0; i < BLOCK_SIZE; i++) {
        *value = (*value << 1) | binary[i];
    }
}

// Function to print binary array
void print_binary(int *binary, int size) {
    for (int i = 0; i < size; i++) {
        printf("%d", binary[i]);
        if ((i + 1) % BLOCK_SIZE == 0) {
            printf(" "); // Add space for readability
        }
    }
    printf("\n");
}

// S-DES Encryption function (simplified)
void sdes_encrypt(int *plaintext, int *key, int *ciphertext) {
    // Simple implementation of S-DES, this should contain all S-DES logic for proper encryption.
    // For simplicity, assume we implement a very basic S-DES operation.

    // This part should include the S-DES rounds and permutations
    // Here is a dummy operation to illustrate encryption
    for (int i = 0; i < BLOCK_SIZE; i++) {
        ciphertext[i] = plaintext[i] ^ key[i % KEY_SIZE]; // Dummy operation
    }
}

// S-DES Decryption function (simplified)
void sdes_decrypt(int *ciphertext, int *key, int *plaintext) {
    // Implement S-DES decryption logic here.
    // Here is a dummy operation to illustrate decryption
    for (int i = 0; i < BLOCK_SIZE; i++) {
        plaintext[i] = ciphertext[i] ^ key[i % KEY_SIZE]; // Dummy operation
    }
}