#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_TEXT_LENGTH 1000

// Function to generate the key for the encryption process
void generate_key(const char *plaintext, const char *keyword, char *key) {
    int j = 0; // Index for keyword
    for (int i = 0; i < strlen(plaintext); i++) {
        if (isalpha(plaintext[i])) {
            key[i] = toupper(keyword[j % strlen(keyword)]); // Cycle through keyword
            j++; // Increment keyword index only for alphabetic characters
        } else {
            key[i] = plaintext[i]; // Non-alphabetic characters remain unchanged
        }
    }
    key[strlen(plaintext)] = '\0'; // Null-terminate the key
}

// Function to encrypt the plaintext using the Vigenère cipher
void encrypt(const char *plaintext, const char *key, char *ciphertext) {
    for (int i = 0; i < strlen(plaintext); i++) {
        if (isalpha(plaintext[i])) {
            char p = toupper(plaintext[i]);
            char k = key[i];
            // Encrypt using the formula: C = (P + K) mod 26
            ciphertext[i] = (p + k - 2 * 'A') % 26 + 'A';
        } else {
            ciphertext[i] = plaintext[i]; // Non-alphabetic characters remain unchanged
        }
    }
    ciphertext[strlen(plaintext)] = '\0'; // Null-terminate the ciphertext
}

int main() {
    char keyword[MAX_TEXT_LENGTH];
    char plaintext[MAX_TEXT_LENGTH];
    char key[MAX_TEXT_LENGTH];
    char ciphertext[MAX_TEXT_LENGTH];

    // Input keyword
    printf("Enter the keyword: ");
    fgets(keyword, sizeof(keyword), stdin);
    keyword[strcspn(keyword, "\n")] = 0; // Remove newline

    // Input plaintext
    printf("Enter the plaintext: ");
    fgets(plaintext, sizeof(plaintext), stdin);
    plaintext[strcspn(plaintext, "\n")] = 0; // Remove newline

    // Generate the key
    generate_key(plaintext, keyword, key);
    
    // Encrypt the plaintext
    encrypt(plaintext, key, ciphertext);

    // Output results
    printf("\nKeyword: %s\n", keyword);
    printf("Plaintext: %s\n", plaintext);
    printf("Key: %s\n", key);
    printf("Ciphertext: %s\n", ciphertext);

    return 0;
}