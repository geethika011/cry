#include <stdio.h>
#include <string.h>

#define BLOCK_SIZE 8  // Size of each block (in bytes)
#define NUM_BLOCKS 4  // Number of blocks to encrypt

// Dummy encryption function (for demonstration purposes)
void encrypt_block(const unsigned char *plaintext, unsigned char *ciphertext) {
    // A simple XOR with a key (not secure, for demonstration only)
    for (int i = 0; i < BLOCK_SIZE; i++) {
        ciphertext[i] = plaintext[i] ^ 0xAA;  // Simple XOR with a key (0xAA)
    }
}

// Dummy decryption function (for demonstration purposes)
void decrypt_block(const unsigned char *ciphertext, unsigned char *plaintext) {
    // XOR with the same key to decrypt
    for (int i = 0; i < BLOCK_SIZE; i++) {
        plaintext[i] = ciphertext[i] ^ 0xAA;  // Simple XOR with a key (0xAA)
    }
}

// ECB Mode Encryption
void ecb_encrypt(const unsigned char plaintext[][BLOCK_SIZE], unsigned char ciphertext[][BLOCK_SIZE]) {
    for (int i = 0; i < NUM_BLOCKS; i++) {
        encrypt_block(plaintext[i], ciphertext[i]);
    }
}

// CBC Mode Encryption
void cbc_encrypt(const unsigned char plaintext[][BLOCK_SIZE], unsigned char ciphertext[][BLOCK_SIZE], unsigned char *iv) {
    unsigned char previous_block[BLOCK_SIZE];
    memcpy(previous_block, iv, BLOCK_SIZE); // Initialize with IV

    for (int i = 0; i < NUM_BLOCKS; i++) {
        unsigned char block[BLOCK_SIZE];
        // XOR the current plaintext block with the previous ciphertext block
        for (int j = 0; j < BLOCK_SIZE; j++) {
            block[j] = plaintext[i][j] ^ previous_block[j];
        }
        encrypt_block(block, ciphertext[i]);  // Encrypt the XORed block
        memcpy(previous_block, ciphertext[i], BLOCK_SIZE);  // Update previous block
    }
}

// Print blocks in hex
void print_blocks(const unsigned char blocks[][BLOCK_SIZE], int num_blocks) {
    for (int i = 0; i < num_blocks; i++) {
        for (int j = 0; j < BLOCK_SIZE; j++) {
            printf("%02X ", blocks[i][j]);
        }
        printf("\n");
    }
}

int main() {
    unsigned char plaintext[NUM_BLOCKS][BLOCK_SIZE] = {
        "Block1", "Block2", "Block3", "Block4"
    };

    unsigned char ciphertext_ecb[NUM_BLOCKS][BLOCK_SIZE];
    unsigned char ciphertext_cbc[NUM_BLOCKS][BLOCK_SIZE];

    unsigned char iv[BLOCK_SIZE] = "InitVect"; // Initialization Vector for CBC

    printf("Plaintext Blocks:\n");
    print_blocks(plaintext, NUM_BLOCKS);

    // ECB Encryption
    ecb_encrypt(plaintext, ciphertext_ecb);
    printf("\nCiphertext (ECB):\n");
    print_blocks(ciphertext_ecb, NUM_BLOCKS);

    // CBC Encryption
    cbc_encrypt(plaintext, ciphertext_cbc, iv);
    printf("\nCiphertext (CBC):\n");
    print_blocks(ciphertext_cbc, NUM_BLOCKS);

    // Simulate an error in the first ciphertext block in CBC
    ciphertext_cbc[0][0] ^= 0x01;  // Introduce an error in C1
    printf("\nCiphertext after error in CBC (C1):\n");
    print_blocks(ciphertext_cbc, NUM_BLOCKS);

    // Decrypt CBC with error to see the effect
    unsigned char decrypted_cbc[NUM_BLOCKS][BLOCK_SIZE];
    for (int i = 0; i < NUM_BLOCKS; i++) {
        decrypt_block(ciphertext_cbc[i], decrypted_cbc[i]);
    }

    printf("\nDecrypted Plaintext with error in CBC:\n");
    print_blocks(decrypted_cbc, NUM_BLOCKS);

    return 0;
}