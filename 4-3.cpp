#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define ALPHABET_SIZE 26
#define MAX_TEXT_LENGTH 1000

// Function to create the cipher alphabet from the keyword
void create_cipher_alphabet(const char *keyword, char *cipher_alphabet) {
    int used[ALPHABET_SIZE] = {0}; // To track used letters
    int index = 0;
    
    // Add keyword letters to cipher alphabet
    for (int i = 0; keyword[i] != '\0'; i++) {
        char c = toupper(keyword[i]);
        if (isalpha(c) && !used[c - 'A']) {
            cipher_alphabet[index++] = c; // Add the letter to cipher
            used[c - 'A'] = 1; // Mark as used
        }
    }
    
    // Add remaining letters of the alphabet
    for (char c = 'A'; c <= 'Z'; c++) {
        if (!used[c - 'A']) {
            cipher_alphabet[index++] = c; // Add unused letters
        }
    }
    cipher_alphabet[index] = '\0'; // Null terminate the cipher alphabet
}

// Function to encrypt the plaintext using the cipher alphabet
void encrypt(const char *plaintext, const char *cipher_alphabet, char *ciphertext) {
    for (int i = 0; plaintext[i] != '\0'; i++) {
        char c = toupper(plaintext[i]);
        if (isalpha(c)) {
            ciphertext[i] = cipher_alphabet[c - 'A']; // Replace with cipher letter
        } else {
            ciphertext[i] = plaintext[i]; // Non-alphabetic characters remain unchanged
        }
    }
    ciphertext[strlen(plaintext)] = '\0'; // Null terminate the ciphertext
}

int main() {
    char keyword[MAX_TEXT_LENGTH];
    char cipher_alphabet[ALPHABET_SIZE + 1]; // 26 letters + null terminator
    char plaintext[MAX_TEXT_LENGTH];
    char ciphertext[MAX_TEXT_LENGTH];

    // Input keyword
    printf("Enter the keyword: ");
    fgets(keyword, sizeof(keyword), stdin);
    keyword[strcspn(keyword, "\n")] = 0; // Remove newline

    // Input plaintext
    printf("Enter the plaintext: ");
    fgets(plaintext, sizeof(plaintext), stdin);
    plaintext[strcspn(plaintext, "\n")] = 0; // Remove newline

    // Create the cipher alphabet
    create_cipher_alphabet(keyword, cipher_alphabet);
    
    // Encrypt the plaintext
    encrypt(plaintext, cipher_alphabet, ciphertext);

    // Output results
    printf("\nKeyword: %s\n", keyword);
    printf("Cipher Alphabet: %s\n", cipher_alphabet);
    printf("Plaintext: %s\n", plaintext);
    printf("Ciphertext: %s\n", ciphertext);

    return 0;
}