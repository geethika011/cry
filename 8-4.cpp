#include <stdio.h>
#include <string.h>
#include <stdint.h>

#define BLOCK_SIZE 8 // Size of the block in bytes

// Simplified block cipher function (just for demonstration)
void simple_block_cipher(uint8_t *input, uint8_t *key, uint8_t *output) {
    for (int i = 0; i < BLOCK_SIZE; i++) {
        output[i] = input[i] ^ key[i]; // XOR with the key (not secure, just illustrative)
    }
}

// CBC-MAC calculation
void cbc_mac(uint8_t *key, uint8_t *message, uint8_t *mac) {
    uint8_t iv[BLOCK_SIZE] = {0}; // Initialization Vector (IV)
    uint8_t block[BLOCK_SIZE] = {0};

    // Process the message in blocks
    for (int i = 0; i < BLOCK_SIZE; i++) {
        block[i] = message[i]; // Load the block
    }

    // XOR with IV
    for (int i = 0; i < BLOCK_SIZE; i++) {
        block[i] ^= iv[i];
    }

    // Encrypt the block
    simple_block_cipher(block, key, mac);
}

// Main function to demonstrate CBC-MAC
int main() {
    uint8_t key[BLOCK_SIZE] = {0x1F, 0x2E, 0x3D, 0x4C, 0x5B, 0x6A, 0x7B, 0x8C}; // Example key
    uint8_t message[BLOCK_SIZE] = {0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48}; // Example message 'ABCDEFGH'
    uint8_t mac[BLOCK_SIZE] = {0};

    // Calculate the MAC for the single-block message
    cbc_mac(key, message, mac);

    printf("CBC-MAC of the one-block message:\n");
    for (int i = 0; i < BLOCK_SIZE; i++) {
        printf("%02X ", mac[i]);
    }
    printf("\n");

    // Adversary knows the MAC for the two-block message X || (X, T)
    uint8_t adversary_message[2 * BLOCK_SIZE];
    memcpy(adversary_message, message, BLOCK_SIZE); // X
    memcpy(adversary_message + BLOCK_SIZE, message, BLOCK_SIZE); // X
    memcpy(adversary_message + 2 * BLOCK_SIZE, mac, BLOCK_SIZE); // T

    // The adversary can calculate the MAC for the two-block message
    uint8_t adversary_mac[BLOCK_SIZE] = {0};
    cbc_mac(key, adversary_message, adversary_mac);

    printf("Adversary MAC for the two-block message (X || (X, T)):\n");
    for (int i = 0; i < BLOCK_SIZE; i++) {
        printf("%02X ", adversary_mac[i]);
    }
    printf("\n");

    return 0;
}