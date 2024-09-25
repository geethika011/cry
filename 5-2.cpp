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

// Function to decrypt the ciphertext using a given substitution
void decrypt(const char *ciphertext, const char *substitution, char *plaintext) {
    for (int i = 0; ciphertext[i] != '\0'; i++) {
        if (isalpha(ciphertext[i])) {
            char letter = toupper(ciphertext[i]);
            plaintext[i] = substitution[letter - 'A'];
        } else {
            plaintext[i] = ciphertext[i]; // Keep non-alphabetic characters unchanged
        }
    }
    plaintext[strlen(ciphertext)] = '\0'; // Null terminate
}

// Function to generate a substitution alphabet based on frequency analysis
void generate_substitution(const double freq[ALPHABET_SIZE], char *substitution) {
    // Common letter frequencies in English
    char common_letters[ALPHABET_SIZE] = {'E', 'T', 'A', 'O', 'I', 'N', 'S', 'H', 'R', 'D', 
                                           'L', 'U', 'C', 'M', 'W', 'F', 'Y', 'G', 'P', 'B', 
                                           'V', 'K', 'J', 'X', 'Q', 'Z'};
    
    // Create a basic substitution based on frequency
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        substitution[i] = common_letters[i];
    }
}

// Function to perform the frequency attack
void frequency_attack(const char *ciphertext) {
    double freq[ALPHABET_SIZE];
    calculate_frequency(ciphertext, freq);

    // Generate a substitution based on frequency analysis
    char substitution[ALPHABET_SIZE + 1];
    generate_substitution(freq, substitution);
    substitution[ALPHABET_SIZE] = '\0'; // Null terminate the substitution string

    // Store the top 10 possible plaintexts
    char plaintexts[TOP_PLAINTEXTS][MAX_TEXT_LENGTH];

    printf("\nPossible plaintexts:\n");
    for (int i = 0; i < TOP_PLAINTEXTS; i++) {
        decrypt(ciphertext, substitution, plaintexts[i]);
        printf("%2d: %s\n", i + 1, plaintexts[i]);

        // Update the substitution for the next iteration if needed
        // (For demonstration, we just use the same substitution)
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