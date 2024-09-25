#include <stdio.h>
#include <string.h>

#define BLOCK_SIZE 8 // Size of the block in bits
#define KEY_SIZE 10  // Size of the key in bits

void print_binary(unsigned char* data, int length) {
    for (int i = 0; i < length; i++) {
        for (int j = 7; j >= 0; j--) {
            printf("%d", (data[i] >> j) & 1);
        }
        printf(" ");
    }
    printf("\n");
}

// Simple DES function for demonstration
void simple_des(unsigned char* input, unsigned char* output, unsigned char* key) {
    // A basic XOR operation to simulate a simple DES-like operation
    for (int i = 0; i < BLOCK_SIZE / 8; i++) { // Use BLOCK_SIZE / 8 for byte size
        output[i] = input[i] ^ key[i % (KEY_SIZE / 8)];
    }
}

// CBC Encryption
void cbc_encrypt(unsigned char* plaintext, unsigned char* ciphertext, unsigned char* key, unsigned char* iv, int length) {
    unsigned char previous_block[BLOCK_SIZE / 8];
    memcpy(previous_block, iv, BLOCK_SIZE / 8); // Initialization vector

    for (int i = 0; i < length; i += BLOCK_SIZE / 8) {
        // XOR with the previous block (or IV for the first block)
        for (int j = 0; j < BLOCK_SIZE / 8; j++) {
            plaintext[i + j] ^= previous_block[j];
        }

        // Encrypt the block
        simple_des(plaintext + i, ciphertext + i, key);
        memcpy(previous_block, ciphertext + i, BLOCK_SIZE / 8); // Update previous block
    }
}

// CBC Decryption
void cbc_decrypt(unsigned char* ciphertext, unsigned char* plaintext, unsigned char* key, unsigned char* iv, int length) {
    unsigned char previous_block[BLOCK_SIZE / 8];
    memcpy(previous_block, iv, BLOCK_SIZE / 8); // Initialization vector

    for (int i = 0; i < length; i += BLOCK_SIZE / 8) {
        // Decrypt the block
        unsigned char decrypted_block[BLOCK_SIZE / 8];
        simple_des(ciphertext + i, decrypted_block, key);

        // XOR with the previous block (or IV for the first block)
        for (int j = 0; j < BLOCK_SIZE / 8; j++) {
            plaintext[i + j] = decrypted_block[j] ^ previous_block[j];
        }

        memcpy(previous_block, ciphertext + i, BLOCK_SIZE / 8); // Update previous block
    }
}

int main() {
    unsigned char key[KEY_SIZE / 8] = {0b01111111}; // Key: 01111111 (1 byte)
    unsigned char iv[BLOCK_SIZE / 8] = {0b10101010};   // IV: 10101010 (1 byte)
    
    // Plaintext needs to be a multiple of BLOCK_SIZE/8 bytes
    unsigned char plaintext[BLOCK_SIZE / 8 * 3] = {0b00000001, 0b00000010, 0b00000011}; // Three bytes of plaintext
    unsigned char ciphertext[BLOCK_SIZE / 8 * 3]; // Buffer for ciphertext
    unsigned char decrypted[BLOCK_SIZE / 8 * 3]; // Buffer for decrypted text

    printf("Original Plaintext:\n");
    print_binary(plaintext, sizeof(plaintext));

    // Encrypt
    cbc_encrypt(plaintext, ciphertext, key, iv, sizeof(plaintext));
    printf("Ciphertext:\n");
    print_binary(ciphertext, sizeof(plaintext)); // Print only the size of the plaintext

    // Decrypt
    cbc_decrypt(ciphertext, decrypted, key, iv, sizeof(plaintext)); // Decrypt only the size of the plaintext
    printf("Decrypted Plaintext:\n");
    print_binary(decrypted, sizeof(plaintext)); // Print only the size of the plaintext

    return 0;
}