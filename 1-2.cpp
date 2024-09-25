#include <stdio.h>
#include <ctype.h>

// Function to encrypt the text using Caesar Cipher
void caesar_encrypt(char text[], int k) {
    for (int i = 0; text[i] != '\0'; i++) {
        char ch = text[i];

        // Encrypt only alphabetic characters
        if (isalpha(ch)) {
            // Handle uppercase letters
            if (isupper(ch)) {
                ch = ((ch - 'A' + k) % 26) + 'A';
            }
            // Handle lowercase letters
            else if (islower(ch)) {
                ch = ((ch - 'a' + k) % 26) + 'a';
            }
        }
        // Print encrypted character
        printf("%c", ch);
    }
    printf("\n");
}

// Function to decrypt the text using Caesar Cipher
void caesar_decrypt(char text[], int k) {
    for (int i = 0; text[i] != '\0'; i++) {
        char ch = text[i];

        // Decrypt only alphabetic characters
        if (isalpha(ch)) {
            // Handle uppercase letters
            if (isupper(ch)) {
                ch = ((ch - 'A' - k + 26) % 26) + 'A'; // Adding 26 ensures we don't get negative results
            }
            // Handle lowercase letters
            else if (islower(ch)) {
                ch = ((ch - 'a' - k + 26) % 26) + 'a';
            }
        }
        // Print decrypted character
        printf("%c", ch);
    }
    printf("\n");
}

int main() {
    char text[100];
    int k;

    // Input plaintext
    printf("Enter the text: ");
    fgets(text, sizeof(text), stdin);

    // Input the shift value
    printf("Enter the shift value (1-25): ");
    scanf("%d", &k);

    // Encrypt the text
    printf("Encrypted Text: ");
    caesar_encrypt(text, k);

    // Decrypt the text
    printf("Decrypted Text: ");
    caesar_decrypt(text, k);

    return 0;
}