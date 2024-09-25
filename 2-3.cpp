#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define BLOCK_SIZE 8 // DES block size is 8 bytes

// Function to print bytes in hexadecimal
void print_hex(const unsigned char *data, size_t len) {
    for (size_t i = 0; i < len; i++) {
        printf("%02x", data[i]);
    }
    printf("\n");
}

// Placeholder for a simple DES-like encryption function (for demonstration purposes)
void des_encrypt(const unsigned char *input, unsigned char *output, const unsigned char *key) {
    // Simple XOR with key (not a real DES operation)
    for (size_t i = 0; i < BLOCK_SIZE; i++) {
        output[i] = input[i] ^ key[i % 8]; // Simple encryption logic
    }
}

// Function to perform 3DES encryption in CBC mode
void triple_des_cbc_encrypt(const unsigned char *input, size_t input_len,
                             const unsigned char *key, const unsigned char *iv,
                             unsigned char *output) {
    unsigned char temp[BLOCK_SIZE];
    unsigned char block[BLOCK_SIZE];

    // Initialization vector for CBC
    memcpy(temp, iv, BLOCK_SIZE);

    // Encrypt input in blocks
    for (size_t i = 0; i < input_len; i += BLOCK_SIZE) {
        size_t block_size = BLOCK_SIZE;

        // Handle last block padding
        if (i + BLOCK_SIZE > input_len) {
            block_size = input_len - i;
            memset(block + block_size, 0, BLOCK_SIZE - block_size); // Padding
        } else {
            memcpy(block, input + i, BLOCK_SIZE);
        }

        // XOR with the previous ciphertext block (or IV for the first block)
        for (size_t j = 0; j < BLOCK_SIZE; j++) {
            block[j] ^= temp[j];
        }

        // Encrypt using 3DES (simulated as three rounds of DES)
        unsigned char intermediate[BLOCK_SIZE];
        des_encrypt(block, intermediate, key);           // First key
        des_encrypt(intermediate, output + (i / BLOCK_SIZE) * BLOCK_SIZE, key + 8); // Second key
        des_encrypt(output + (i / BLOCK_SIZE) * BLOCK_SIZE, output + (i / BLOCK_SIZE) * BLOCK_SIZE, key + 16); // Third key

        // Save the encrypted block for the next iteration
        memcpy(temp, output + (i / BLOCK_SIZE) * BLOCK_SIZE, BLOCK_SIZE);
    }
}

int main() {
    // Example input
    const unsigned char input[] = "This is a secret message that needs to be encrypted!";
    size_t input_len = strlen((const char *)input);
    
    // Key (24 bytes for 3DES)
    unsigned char key[24] = {
        0x01, 0x02, 0x03, 0x04, 0x05, 0x06, // Key1
        0x11, 0x12, 0x13, 0x14, 0x15, 0x16, // Key2
        0x21, 0x22, 0x23, 0x24, 0x25, 0x26  // Key3
    };

    // IV (8 bytes)
    unsigned char iv[BLOCK_SIZE] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07};
    
    // Output buffer
    unsigned char output[BLOCK_SIZE * ((input_len + BLOCK_SIZE - 1) / BLOCK_SIZE)];
    
    // Perform encryption
    triple_des_cbc_encrypt(input, input_len, key, iv, output);
    
    // Print the ciphertext in hex
    printf("Ciphertext: ");
    print_hex(output, sizeof(output));

    return 0;
}