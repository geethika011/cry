#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void encrypt(char *text, int shift) {
    for (int i = 0; text[i] != '\0'; i++) {
        char c = text[i];

        // Encrypt uppercase letters
        if (c >= 'A' && c <= 'Z') {
            c = (c - 'A' + shift) % 26 + 'A';
        }
        // Encrypt lowercase letters
        else if (c >= 'a' && c <= 'z') {
            c = (c - 'a' + shift) % 26 + 'a';
        }
        text[i] = c; // Update the character in the string
    }
}

void decrypt(char *text, int shift) {
    for (int i = 0; text[i] != '\0'; i++) {
        char c = text[i];

        // Decrypt uppercase letters
        if (c >= 'A' && c <= 'Z') {
            c = (c - 'A' - shift + 26) % 26 + 'A'; // +26 to avoid negative
        }
        // Decrypt lowercase letters
        else if (c >= 'a' && c <= 'z') {
            c = (c - 'a' - shift + 26) % 26 + 'a'; // +26 to avoid negative
        }
        text[i] = c; // Update the character in the string
    }
}

int main() {
    char text[100];
    int shift;
    
    printf("Enter the text (letters only): ");
    fgets(text, sizeof(text), stdin);
    
    // Remove newline character from input
    text[strcspn(text, "\n")] = 0;

    printf("Enter shift (1-25): ");
    scanf("%d", &shift);

    if (shift < 1 || shift > 25) {
        printf("Shift must be between 1 and 25.\n");
        return 1;
    }

    // Encrypt the text
    encrypt(text, shift);
    printf("Encrypted Text: %s\n", text);

    // Decrypt the text
    decrypt(text, shift);
    printf("Decrypted Text: %s\n", text);

    return 0;
}