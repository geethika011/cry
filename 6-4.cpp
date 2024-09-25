#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define BLOCK_SIZE 8 // Size of the block in bytes

void print_block(unsigned char* block) {
    for (int i = 0; i < BLOCK_SIZE; i++) {
        printf("%02x ", block[i]);
    }
    printf("\n");
}

// Padding function
void pad(unsigned char* input, int* length) {
    // Calculate padding size
    int pad_size = BLOCK_SIZE - (*length % BLOCK_SIZE);
    for (int i = 0; i < pad_size; i++) {
        input[*length + i] = (i == 0) ? 0x80 : 0x00; // Pad with 0x80 followed by 0x00
    }
    *length += pad_size;
}

// Simple XOR encryption for demonstration
void xor_encrypt(unsigned char* block, unsigned char* key) {
    for (int i = 0; i < BLOCK_SIZE; i++) {
        block[i] ^= key[i];
    }
}

// ECB mode
void ecb_encrypt(unsigned char* plaintext, unsigned char* ciphertext, unsigned char* key, int length) {
    for (int i = 0; i < length; i += BLOCK_SIZE) {
        memcpy(ciphertext + i, plaintext + i, BLOCK_SIZE);
        xor_encrypt(ciphertext + i, key);
    }
}

// CBC mode
void cbc_encrypt(unsigned char* plaintext, unsigned char* ciphertext, unsigned char* key, int length) {
    unsigned char iv[BLOCK_SIZE] = {0}; // Initialization vector (IV)
    
    for (int i = 0; i < length; i += BLOCK_SIZE) {
        for (int j = 0; j < BLOCK_SIZE; j++) {
            plaintext[i + j] ^= iv[j]; // XOR with IV or previous ciphertext
        }
        memcpy(ciphertext + i, plaintext + i, BLOCK_SIZE);
        xor_encrypt(ciphertext + i, key);
        memcpy(iv, ciphertext + i, BLOCK_SIZE); // Update IV for next block
    }
}

// CFB mode
void cfb_encrypt(unsigned char* plaintext, unsigned char* ciphertext, unsigned char* key, int length) {
    unsigned char iv[BLOCK_SIZE] = {0}; // Initialization vector (IV)
    
    for (int i = 0; i < length; i += BLOCK_SIZE) {
        xor_encrypt(iv, key); // Encrypt the IV
        
        for (int j = 0; j < BLOCK_SIZE; j++) {
            ciphertext[i + j] = plaintext[i + j] ^ iv[j]; // XOR with the output of the encryption
        }
        
        memcpy(iv, ciphertext + i, BLOCK_SIZE); // Update IV for next block
    }
}

int main() {
    unsigned char key[BLOCK_SIZE] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08}; // Example key
    unsigned char plaintext[64] = "This is an example plaintext message."; // Example plaintext
    unsigned char ciphertext[64];
    
    // Adjust plaintext length
    int length = strlen((char*)plaintext);
    pad(plaintext, &length); // Pad the plaintext

    printf("Original Plaintext:\n");
    print_block(plaintext);

    // Encrypt using ECB mode
    printf("\nEncryption using ECB:\n");
    ecb_encrypt(plaintext, ciphertext, key, length);
    print_block(ciphertext);

    // Reset and prepare for CBC
    memcpy(plaintext, ciphertext, length); // Use ciphertext as new plaintext
    printf("\nEncryption using CBC:\n");
    cbc_encrypt(plaintext, ciphertext, key, length);
    print_block(ciphertext);

    // Reset and prepare for CFB
    memcpy(plaintext, ciphertext, length); // Use ciphertext as new plaintext
    printf("\nEncryption using CFB:\n");
    cfb_encrypt(plaintext, ciphertext, key, length);
    print_block(ciphertext);

    return 0;
}