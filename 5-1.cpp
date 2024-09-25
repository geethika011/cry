#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define ALPHABET_SIZE 26
#define MAX_TEXT_LENGTH 1000
#define TOP_PLAINTEXTS 10

// Function to calculate letter frequencies
void calculate_frequency(const char *text, double freq[ALPHABET_SIZE]) {
    int total_letters = 0;
    
    // Initialize frequency array
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        freq[i] = 0.0;
    }
    
    // Count frequency of each letter
    for (int i = 0; text[i] != '\0'; i++) {
        if (isalpha(text[i])) {
            char letter = toupper(text[i]);
            freq[letter - 'A']++;
            total_letters++;
        }
    }
    
    // Convert counts to frequency percentages
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        freq[i] = (freq[i] / total_letters) * 100; // Convert to percentage
    }
}

// Function to decrypt the ciphertext using a given shift
void decrypt(const char *ciphertext, int shift, char *plaintext) {
    for (int i = 0; ciphertext[i] != '\0'; i++) {
        if (isalpha(ciphertext[i])) {
            char letter = toupper(ciphertext[i]);
            plaintext[i] = ((letter - 'A' - shift + ALPHABET_SIZE) % ALPHABET_SIZE) + 'A';
        } else {
            plaintext[i] = ciphertext[i]; // Keep non-alphabetic characters unchanged
        }
    }
    plaintext[strlen(ciphertext)] = '\0'; // Null terminate
}

// Function to perform the frequency attack
void frequency_attack(const char *ciphertext) {
    double freq[ALPHABET_SIZE];
    calculate_frequency(ciphertext, freq);

    // Assume the most frequent letter in English is 'E'
    // Find the shift based on the most frequent letter in ciphertext
    int max_index = 0;
    for (int i = 1; i < ALPHABET_SIZE; i++) {
        if (freq[i] > freq[max_index]) {
            max_index = i;
        }
    }

    int shift = (max_index - ('E' - 'A') + ALPHABET_SIZE) % ALPHABET_SIZE; // Shift to 'E'
    
    // Store the top 10 possible plaintexts
    char plaintexts[TOP_PLAINTEXTS][MAX_TEXT_LENGTH];

    printf("\nPossible plaintexts:\n");
    for (int i = 0; i < TOP_PLAINTEXTS; i++) {
        decrypt(ciphertext, (shift + i) % ALPHABET_SIZE, plaintexts[i]);
        printf("%2d: %s\n", i + 1, plaintexts[i]);
    }
}

int main() {
    char ciphertext[MAX_TEXT_LENGTH];

    // Input ciphertext
    printf("Enter the ciphertext: ");
    fgets(ciphertext, sizeof(ciphertext), stdin);
    ciphertext[strcspn(ciphertext, "\n")] = 0; // Remove newline

    // Perform frequency attack
    frequency_attack(ciphertext);

    return 0;
}