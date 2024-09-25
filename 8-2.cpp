#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_TEXT_SIZE 100

// Function to encrypt the plaintext using the one-time pad
void encrypt(char *plaintext, int *key, int key_length, char *ciphertext) {
    for (int i = 0; plaintext[i] != '\0'; i++) {
        char c = plaintext[i];

        // Encrypt only alphabetic characters
        if (c >= 'A' && c <= 'Z') {
            ciphertext[i] = (c - 'A' + key[i % key_length]) % 26 + 'A';
        } else if (c >= 'a' && c <= 'z') {
            ciphertext[i] = (c - 'a' + key[i % key_length]) % 26 + 'a';
        } else {
            ciphertext[i] = c; // Non-alphabetic characters remain unchanged
        }
    }
    ciphertext[strlen(plaintext)] = '\0'; // Null-terminate the ciphertext
}

// Function to generate a random key of specified length
void generate_random_key(int *key, int key_length) {
    for (int i = 0; i < key_length; i++) {
        key[i] = rand() % 26; // Random number between 0 and 25
    }
}

// Function to display the key
void display_key(int *key, int key_length) {
    printf("Key: ");
    for (int i = 0; i < key_length; i++) {
        printf("%d ", key[i]);
    }
    printf("\n");
}

int main() {
    char plaintext[MAX_TEXT_SIZE];
    int key_length;

    // Seed random number generator
    srand(time(NULL));

    // Input plaintext
    printf("Enter the plaintext (letters only): ");
    fgets(plaintext, sizeof(plaintext), stdin);
    
    // Remove newline character from input
    plaintext[strcspn(plaintext, "\n")] = 0;

    // Input key length
    printf("Enter the length of the key: ");
    scanf("%d", &key_length);

    if (key_length <= 0 || key_length > MAX_TEXT_SIZE) {
        printf("Invalid key length. It must be greater than 0 and less than %d.\n", MAX_TEXT_SIZE);
        return 1;
    }

    // Generate random key
    int key[key_length];
    generate_random_key(key, key_length);
    display_key(key, key_length);

    // Encrypt the plaintext
    char ciphertext[MAX_TEXT_SIZE];
    encrypt(plaintext, key, key_length, ciphertext);
    
    // Display ciphertext
    printf("Ciphertext: %s\n", ciphertext);

    return 0;
}