#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define SIZE 5
#define MAX_TEXT_LENGTH 256 // Define a maximum length for plaintext

// Function to create the Playfair matrix
void createPlayfairMatrix(char* key, char matrix[SIZE][SIZE]) {
    int used[26] = {0}; // To keep track of letters already used
    int len = strlen(key);
    int index = 0;

    // Add characters from the key to the matrix
    for (int i = 0; i < len; i++) {
        char ch = toupper(key[i]);
        if (ch == 'J') ch = 'I'; // Treat 'J' as 'I'
        if (ch < 'A' || ch > 'Z' || used[ch - 'A']) continue; // Skip if not a letter or already used
        used[ch - 'A'] = 1; // Mark letter as used
        matrix[index / SIZE][index % SIZE] = ch;
        index++;
    }

    // Fill the remaining letters of the alphabet
    for (char ch = 'A'; ch <= 'Z'; ch++) {
        if (ch == 'J') continue; // Skip 'J'
        if (used[ch - 'A']) continue; // Skip if already used
        matrix[index / SIZE][index % SIZE] = ch;
        index++;
    }
}

// Function to find the position of a letter in the matrix
void findPosition(char matrix[SIZE][SIZE], char letter, int *row, int *col) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (matrix[i][j] == letter) {
                *row = i;
                *col = j;
                return;
            }
        }
    }
}

// Function to decrypt the message
void decryptPlayfair(char* ciphertext, char matrix[SIZE][SIZE], char* plaintext) {
    int len = strlen(ciphertext);
    int index = 0;

    for (int i = 0; i < len; i += 2) {
        char a = ciphertext[i];
        char b = ciphertext[i + 1];

        // If both characters are the same, replace the second character
        if (a == b) {
            b = 'X'; // Add 'X' if the same
            i--; // Decrement i to process this character again
        }

        int row1, col1, row2, col2;
        findPosition(matrix, a, &row1, &col1);
        findPosition(matrix, b, &row2, &col2);

        // Same row: move left
        if (row1 == row2) {
            plaintext[index++] = matrix[row1][(col1 + SIZE - 1) % SIZE];
            plaintext[index++] = matrix[row2][(col2 + SIZE - 1) % SIZE];
        }
        // Same column: move up
        else if (col1 == col2) {
            plaintext[index++] = matrix[(row1 + SIZE - 1) % SIZE][col1];
            plaintext[index++] = matrix[(row2 + SIZE - 1) % SIZE][col2];
        }
        // Rectangle: swap columns
        else {
            plaintext[index++] = matrix[row1][col2];
            plaintext[index++] = matrix[row2][col1];
        }
    }
    plaintext[index] = '\0'; // Null-terminate the decrypted message
}

int main() {
    char key[] = "PT109"; // The keyword to create the matrix
    char matrix[SIZE][SIZE];
    char ciphertext[] = "KXJEYUREBEZWEHEWRYTUHEYFSKREHEGOYFIWTTTUOLKSYCAJPOBOTEIZONTXBYBNTGONEYCUZWRGDSONSXBOUYWRHEBAAHYUSEDQ";
    char plaintext[MAX_TEXT_LENGTH];

    // Create the Playfair matrix
    createPlayfairMatrix(key, matrix);

    // Decrypt the message
    decryptPlayfair(ciphertext, matrix, plaintext);

    // Output the decrypted plaintext
    printf("Decrypted Plaintext: %s\n", plaintext);
    
    return 0;
}