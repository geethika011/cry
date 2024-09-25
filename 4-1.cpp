#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define ALPHABET_SIZE 26
#define MAX_TEXT_LENGTH 1000

// Function to calculate the frequency of each letter in the ciphertext
void calculate_frequency(const char *ciphertext, double freq[ALPHABET_SIZE]) {
    int count[ALPHABET_SIZE] = {0};
    int total_letters = 0;
    
    for (int i = 0; ciphertext[i] != '\0'; i++) {
        if (ciphertext[i] >= 'a' && ciphertext[i] <= 'z') {
            count[ciphertext[i] - 'a']++;
            total_letters++;
        } else if (ciphertext[i] >= 'A' && ciphertext[i] <= 'Z') {
            count[ciphertext[i] - 'A']++;
            total_letters++;
        }
    }
    
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        freq[i] = (double)count[i] / total_letters;
    }
}

// Function to decrypt the ciphertext with a given shift
void decrypt(const char *ciphertext, int shift, char *plaintext) {
    for (int i = 0; ciphertext[i] != '\0'; i++) {
        if (ciphertext[i] >= 'a' && ciphertext[i] <= 'z') {
            plaintext[i] = (ciphertext[i] - 'a' - shift + ALPHABET_SIZE) % ALPHABET_SIZE + 'a';
        } else if (ciphertext[i] >= 'A' && ciphertext[i] <= 'Z') {
            plaintext[i] = (ciphertext[i] - 'A' - shift + ALPHABET_SIZE) % ALPHABET_SIZE + 'A';
        } else {
            plaintext[i] = ciphertext[i]; // Non-alphabetic characters remain unchanged
        }
    }
    plaintext[strlen(ciphertext)] = '\0'; // Null-terminate the plaintext
}

// Function to rank potential plaintexts based on the frequency of 'e'
int rank_plaintexts(const char *ciphertext) {
    double freq[ALPHABET_SIZE];
    calculate_frequency(ciphertext, freq);
    
    // Assume 'e' is the most common letter
    double max_freq = 0.0;
    int best_shift = 0;

    for (int shift = 0; shift < ALPHABET_SIZE; shift++) {
        double score = freq[(0 - shift + ALPHABET_SIZE) % ALPHABET_SIZE]; // Frequency of the letter corresponding to 'e'
        if (score > max_freq) {
            max_freq = score;
            best_shift = shift;
        }
    }
    return best_shift;
}

int main() {
    char ciphertext[MAX_TEXT_LENGTH];
    char plaintext[MAX_TEXT_LENGTH];

    // Example ciphertext (Add your ciphertext here)
    printf("Enter the ciphertext: ");
    fgets(ciphertext, sizeof(ciphertext), stdin);
    ciphertext[strcspn(ciphertext, "\n")] = 0; // Remove newline

    printf("Ciphertext: %s\n", ciphertext);
    
    // Generate potential plaintexts
    printf("Top 10 possible plaintexts:\n");
    for (int shift = 0; shift < ALPHABET_SIZE; shift++) {
        decrypt(ciphertext, shift, plaintext);
        printf("Shift %2d: %s\n", shift, plaintext);
    }

    // Optionally, find the most likely plaintext
    int best_shift = rank_plaintexts(ciphertext);
    printf("\nBest shift based on frequency analysis: %d\n", best_shift);
    printf("Decrypted text: ");
    decrypt(ciphertext, best_shift, plaintext);
    printf("%s\n", plaintext);

    return 0;
}