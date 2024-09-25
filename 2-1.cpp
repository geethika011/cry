#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define ALPHABET_SIZE 26

// Function prototypes
void generate_key(char key[ALPHABET_SIZE]);
void encrypt(char plaintext[], char key[ALPHABET_SIZE], char ciphertext[]);
void decrypt(char ciphertext[], char key[ALPHABET_SIZE], char plaintext[]);

// Function to generate a substitution key
void generate_key(char key[ALPHABET_SIZE]) {
    // Example substitution key (this can be randomized or input by the user)
    strcpy(key, "QWERTYUIOPLKJHGFDSAZXCVBNM");
}

// Function to encrypt the plaintext using the substitution key
void encrypt(char plaintext[], char key[ALPHABET_SIZE], char ciphertext[]) {
    for (int i = 0; plaintext[i] != '\0'; i++) {
        char ch = toupper(plaintext[i]);

        if (isalpha(ch)) {
            int index = ch - 'A';  // Get the position of the letter in the alphabet
            ciphertext[i] = key[index];  // Substitute with the corresponding key letter
        } else {
            ciphertext[i] = plaintext[i];  // Keep non-alphabet characters unchanged
        }
    }
    ciphertext[strlen(plaintext)] = '\0';  // Null-terminate the ciphertext
}

// Function to decrypt the ciphertext using the substitution key
void decrypt(char ciphertext[], char key[ALPHABET_SIZE], char plaintext[]) {
    for (int i = 0; ciphertext[i] != '\0'; i++) {
        char ch = toupper(ciphertext[i]);

        if (isalpha(ch)) {
            // Find the index of the ciphertext letter in the key
            for (int j = 0; j < ALPHABET_SIZE; j++) {
                if (key[j] == ch) {
                    plaintext[i] = 'A' + j;  // Map it back to the corresponding plaintext letter
                    break;
                }
            }
        } else {
            plaintext[i] = ciphertext[i];  // Keep non-alphabet characters unchanged
        }
    }
    plaintext[strlen(ciphertext)] = '\0';  // Null-terminate the plaintext
}

int main() {
    char key[ALPHABET_SIZE];  // Substitution key
    char plaintext[100], ciphertext[100], decrypted_text[100];

    // Generate the substitution key (can be randomized or user-specified)
    generate_key(key);

    // Display the substitution key
    printf("Substitution key: ");
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        printf("%c ", key[i]);
    }
    printf("\n");

    // Input the plaintext
    printf("Enter the plaintext: ");
    fgets(plaintext, sizeof(plaintext), stdin);
    plaintext[strcspn(plaintext, "\n")] = '\0';  // Remove the newline character

    // Encrypt the plaintext
    encrypt(plaintext, key, ciphertext);
    printf("Encrypted text: %s\n", ciphertext);

    // Decrypt the ciphertext
    decrypt(ciphertext, key, decrypted_text);
    printf("Decrypted text: %s\n", decrypted_text);

    return 0;
}