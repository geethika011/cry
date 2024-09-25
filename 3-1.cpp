#include <stdio.h>
#include <string.h>

// Define the permutation tables

// Permuted Choice 1 (PC-1): Selects 56 bits from the original 64-bit key.
int PC1[] = {
    57, 49, 41, 33, 25, 17,  9,
     1, 58, 50, 42, 34, 26, 18,
    10,  2, 59, 51, 43, 35, 27,
    19, 11,  3, 60, 52, 44, 36,
    63, 55, 47, 39, 31, 23, 15,
     7, 62, 54, 46, 38, 30, 22,
    14,  6, 61, 53, 45, 37, 29,
    21, 13,  5, 28, 20, 12,  4
};

// Permuted Choice 2 (PC-2): Selects 48 bits from the shifted 56-bit key (28 bits from C and 28 bits from D).
int PC2[] = {
    14, 17, 11, 24,  1,  5,
     3, 28, 15,  6, 21, 10,
    23, 19, 12,  4, 26,  8,
    16,  7, 27, 20, 13,  2,
    41, 52, 31, 37, 47, 55,
    30, 40, 51, 45, 33, 48,
    44, 49, 39, 56, 34, 53,
    46, 42, 50, 36, 29, 32
};

// Number of left shifts for each round
int left_shifts[] = {
    1, 1, 2, 2, 2, 2, 2, 2,
    1, 2, 2, 2, 2, 2, 2, 1
};

// Function to perform a left circular shift on a 28-bit block
unsigned int left_circular_shift(unsigned int half, int shifts) {
    return ((half << shifts) | (half >> (28 - shifts))) & 0x0FFFFFFF; // Mask with 28 bits
}

// Function to generate the 16 DES subkeys from a 64-bit key
void generate_subkeys(unsigned char *key, unsigned char subkeys[16][6]) {
    unsigned int C = 0, D = 0;  // C and D are the 28-bit halves of the 56-bit key
    unsigned char permuted_key[7];  // After PC-1, we get a 56-bit key

    // Apply PC-1 to the key to get the initial 56-bit key
    for (int i = 0; i < 56; i++) {
        int bit_position = PC1[i] - 1;
        int byte_index = bit_position / 8;
        int bit_index = bit_position % 8;
        if (key[byte_index] & (1 << (7 - bit_index))) {
            permuted_key[i / 8] |= (1 << (7 - (i % 8)));
        } else {
            permuted_key[i / 8] &= ~(1 << (7 - (i % 8)));
        }
    }

    // Split the permuted key into C (left) and D (right)
    for (int i = 0; i < 28; i++) {
        C = (C << 1) | ((permuted_key[i / 8] >> (7 - (i % 8))) & 0x01);
        D = (D << 1) | ((permuted_key[(i + 28) / 8] >> (7 - ((i + 28) % 8))) & 0x01);
    }

    // Generate the 16 subkeys
    for (int round = 0; round < 16; round++) {
        // Perform the left circular shifts
        C = left_circular_shift(C, left_shifts[round]);
        D = left_circular_shift(D, left_shifts[round]);

        // Combine C and D into a 56-bit block
        unsigned long long combined = ((unsigned long long)C << 28) | D;

        // Apply PC-2 to get the 48-bit subkey
        memset(subkeys[round], 0, 6);  // Initialize the subkey to 0
        for (int i = 0; i < 48; i++) {
            int bit_position = PC2[i] - 1;
            int byte_index = bit_position / 8;
            int bit_index = bit_position % 8;
            if (combined & ((unsigned long long)1 << (55 - bit_position))) {
                subkeys[round][i / 8] |= (1 << (7 - (i % 8)));
            }
        }
    }
}

// Function to print a subkey in hexadecimal format
void print_subkey(unsigned char subkey[6]) {
    for (int i = 0; i < 6; i++) {
        printf("%02X ", subkey[i]);
    }
    printf("\n");
}

int main() {
    // 64-bit key (including parity bits)
    unsigned char key[8] = {0x13, 0x34, 0x57, 0x79, 0x9B, 0xBC, 0xDF, 0xF1};
    unsigned char subkeys[16][6];  // Store the 16 subkeys (48-bit each)

    // Generate the subkeys
    generate_subkeys(key, subkeys);

    // Print the subkeys
    for (int round = 0; round < 16; round++) {
        printf("Subkey %d: ", round + 1);
        print_subkey(subkeys[round]);
    }

    return 0;
}