#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MATRIX_SIZE 5
#define MAX_MESSAGE_LENGTH 256

// Playfair matrix
char playfair_matrix[MATRIX_SIZE][MATRIX_SIZE] = {
    {'M', 'F', 'H', 'I', 'J'},
    {'K', 'U', 'N', 'O', 'P'},
    {'Q', 'Z', 'V', 'W', 'X'},
    {'Y', 'E', 'L', 'A', 'R'},
    {'G', 'D', 'S', 'T', 'B'},
};

// Function to find the position of a character in the matrix
void find_position(char c, int *row, int *col) {
    for (int i = 0; i < MATRIX_SIZE; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            if (playfair_matrix[i][j] == c) {
                *row = i;
                *col = j;
                return;
            }
        }
    }
}

// Function to prepare the plaintext
void prepare_text(char *input, char *output) {
    int index = 0;
    for (int i = 0; i < strlen(input); i++) {
        char c = toupper(input[i]);
        if (isalpha(c)) {
            output[index++] = c;
        }
    }

    // Pair the letters, and handle odd length
    for (int i = 0; i < index; i++) {
        if (i < index - 1 && output[i] == output[i + 1]) {
            // Insert 'X' between two identical letters
            for (int j = index; j > i + 1; j--) {
                output[j] = output[j - 1];
            }
            output[i + 1] = 'X';
            index++;
        }
    }
    output[index] = '\0'; // Null-terminate the output string
}

// Function to encrypt using Playfair cipher
void playfair_encrypt(char *input, char *output) {
    int index = 0;
    for (int i = 0; i < strlen(input); i += 2) {
        char a = input[i];
        char b = (i + 1 < strlen(input)) ? input[i + 1] : 'X'; // Add 'X' if odd length

        int row_a, col_a, row_b, col_b;
        find_position(a, &row_a, &col_a);
        find_position(b, &row_b, &col_b);

        if (row_a == row_b) {
            // Same row: Shift right
            output[index++] = playfair_matrix[row_a][(col_a + 1) % MATRIX_SIZE];
            output[index++] = playfair_matrix[row_b][(col_b + 1) % MATRIX_SIZE];
        } else if (col_a == col_b) {
            // Same column: Shift down
            output[index++] = playfair_matrix[(row_a + 1) % MATRIX_SIZE][col_a];
            output[index++] = playfair_matrix[(row_b + 1) % MATRIX_SIZE][col_b];
        } else {
            // Rectangle swap
            output[index++] = playfair_matrix[row_a][col_b];
            output[index++] = playfair_matrix[row_b][col_a];
        }
    }
    output[index] = '\0'; // Null-terminate the output string
}

int main() {
    char input[MAX_MESSAGE_LENGTH] = "Must see you over Cadogan West. Coming at once.";
    char prepared_text[MAX_MESSAGE_LENGTH];
    char encrypted_text[MAX_MESSAGE_LENGTH];

    // Prepare the plaintext
    prepare_text(input, prepared_text);
    
    // Encrypt the plaintext
    playfair_encrypt(prepared_text, encrypted_text);

    // Display results
    printf("Original message: %s\n", input);
    printf("Prepared message: %s\n", prepared_text);
    printf("Encrypted message: %s\n", encrypted_text);

    return 0;
}