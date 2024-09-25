#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BLOCK_SIZE 16 // Block size in bytes (for demonstration)

// Function to print bytes in hexadecimal
void print_hex(const unsigned char *data, size_t len) {
    for (size_t i = 0; i < len; i++) {
        printf("%02x", data[i]);
    }
    printf("\n");
}

// Simple encryption function (Caesar Cipher as a placeholder)
void simple_encrypt(const unsigned char *input, unsigned char *output, size_t len, int shift) {
    for (size_t i = 0; i < len; i++) {
        output[i] = (input[i] + shift) % 256; // Simple wrap around
    }
}

// Function for AES encryption in ECB mode
void ecb_encrypt(const unsigned char *input, size_t input_len, int shift, unsigned char *output) {
    for (size_t i = 0; i < input_len; i += BLOCK_SIZE) {
        simple_encrypt(input + i, output + i, BLOCK_SIZE, shift);
    }
}

// Function for AES encryption in CBC mode
void cbc_encrypt(const unsigned char *input, size_t input_len, int shift, const unsigned char *iv, unsigned char *output) {
    unsigned char previous_block[BLOCK_SIZE];
    memcpy(previous_block, iv, BLOCK_SIZE);

    for (size_t i = 0; i < input_len; i += BLOCK_SIZE) {
        unsigned char block[BLOCK_SIZE] = {0};
        memcpy(block, input + i, BLOCK_SIZE);
        
        // XOR with the previous ciphertext block (or IV for the first block)
        for (size_t j = 0; j < BLOCK_SIZE; j++) {
            block[j] ^= previous_block[j];
        }

        simple_encrypt(block, output + i, BLOCK_SIZE, shift);
        memcpy(previous_block, output + i, BLOCK_SIZE); // Save ciphertext for next iteration
    }
}

// Function for AES encryption in CFB mode
void cfb_encrypt(const unsigned char *input, size_t input_len, int shift, const unsigned char *iv, unsigned char *output) {
    unsigned char buffer[BLOCK_SIZE];
    unsigned char previous_block[BLOCK_SIZE];
    memcpy(previous_block, iv, BLOCK_SIZE);

    for (size_t i = 0; i < input_len; i += BLOCK_SIZE) {
        simple_encrypt(previous_block, buffer, BLOCK_SIZE, shift);
        
        size_t block_size = (i + BLOCK_SIZE > input_len) ? (input_len - i) : BLOCK_SIZE;
        
        for (size_t j = 0; j < block_size; j++) {
            output[i + j] = input[i + j] ^ buffer[j];
        }

        memcpy(previous_block, buffer, BLOCK_SIZE); // Update previous block
    }
}

int main() {
    // Example plaintext
    const unsigned char input[] = "This is a secret message to be encrypted!";
    size_t input_len = strlen((const char *)input);

    // Shift value for our simple encryption (replace with your own value)
    int shift = 3;
    
    // IV (initialization vector)
    unsigned char iv[BLOCK_SIZE] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
                                     0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f};
    
    // Output buffers
    unsigned char ecb_output[sizeof(input)];
    unsigned char cbc_output[sizeof(input)];
    unsigned char cfb_output[sizeof(input)];

    // Perform encryption
    ecb_encrypt(input, input_len, shift, ecb_output);
    cbc_encrypt(input, input_len, shift, iv, cbc_output);
    cfb_encrypt(input, input_len, shift, iv, cfb_output);

    // Print the ciphertexts
    printf("ECB Ciphertext: ");
    print_hex(ecb_output, input_len);

    printf("CBC Ciphertext: ");
    print_hex(cbc_output, input_len);

    printf("CFB Ciphertext: ");
    print_hex(cfb_output, input_len);
    
    return 0;
}