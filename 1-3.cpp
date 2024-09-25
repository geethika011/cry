#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define SIZE 5

// Function prototypes
void create_key_matrix(char key[], char key_matrix[SIZE][SIZE]);
void preprocess_text(char text[], char processed_text[]);
void encrypt_pair(char a, char b, char key_matrix[SIZE][SIZE], char result[2]);
void find_position(char ch, char key_matrix[SIZE][SIZE], int *row, int *col);
void encrypt_text(char plaintext[], char key_matrix[SIZE][SIZE], char ciphertext[]);

// Function to create the 5x5 key matrix
void create_key_matrix(char key[], char key_matrix[SIZE][SIZE]) {
    int letter_exists[26] = {0};  // To track if a letter is already added to the matrix
    letter_exists['J' - 'A'] = 1; // Combine I and J, so skip J

    int i = 0, j = 0;

    // Add key letters to the matrix
    for (int k = 0; key[k] != '\0'; k++) {
        char ch = toupper(key[k]);
        if (isalpha(ch) && !letter_exists[ch - 'A']) {
            key_matrix[i][j] = ch;
            letter_exists[ch - 'A'] = 1;
            j++;
            if (j == SIZE) {
                j = 0;
                i++;
            }
        }
    }

    // Add remaining letters of the alphabet
    for (char ch = 'A'; ch <= 'Z'; ch++) {
        if (!letter_exists[ch - 'A']) {
            key_matrix[i][j] = ch;
            j++;
            if (j == SIZE) {
                j = 0;
                i++;
            }
        }
    }
}

// Preprocess the plaintext to make it suitable for encryption
void preprocess_text(char text[], char processed_text[]) {
    int len = strlen(text);
    int idx = 0;

    for (int i = 0; i < len; i++) {
        char ch = toupper(text[i]);
        if (isalpha(ch)) {
            if (ch == 'J') {
                ch = 'I'; // Replace 'J' with 'I'
            }
            processed_text[idx++] = ch;
        }
    }
    processed_text[idx] = '\0';
    
    // Insert 'X' between duplicate letters in the same digraph
    char temp[200];
    int k = 0;
    for (int i = 0; i < idx; i += 2) {
        temp[k++] = processed_text[i];
        if (processed_text[i + 1] == processed_text[i]) {
            temp[k++] = 'X';
            temp[k++] = processed_text[i + 1];
        } else {
            temp[k++] = processed_text[i + 1];
        }
    }
    temp[k] = '\0';
    strcpy(processed_text, temp);

    // If the length of processed text is odd, add 'X' at the end
    if (strlen(processed_text) % 2 != 0) {
        processed_text[strlen(processed_text)] = 'X';
        processed_text[strlen(processed_text) + 1] = '\0';
    }
}

// Function to find the position of a character in the key matrix
void find_position(char ch, char key_matrix[SIZE][SIZE], int *row, int *col) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (key_matrix[i][j] == ch) {
                *row = i;
                *col = j;
                return;
            }
        }
    }
}

// Encrypt a pair of letters
void encrypt_pair(char a, char b, char key_matrix[SIZE][SIZE], char result[2]) {
    int row1, col1, row2, col2;
    find_position(a, key_matrix, &row1, &col1);
    find_position(b, key_matrix, &row2, &col2);

    if (row1 == row2) {
        result[0] = key_matrix[row1][(col1 + 1) % SIZE];
        result[1] = key_matrix[row2][(col2 + 1) % SIZE];
    } else if (col1 == col2) {
        result[0] = key_matrix[(row1 + 1) % SIZE][col1];
        result[1] = key_matrix[(row2 + 1) % SIZE][col2];
    } else {
        result[0] = key_matrix[row1][col2];
        result[1] = key_matrix[row2][col1];
    }
}

// Function to encrypt the plaintext
void encrypt_text(char plaintext[], char key_matrix[SIZE][SIZE], char ciphertext[]) {
    int len = strlen(plaintext);
    int idx = 0;
    for (int i = 0; i < len; i += 2) {
        char a = plaintext[i];
        char b = plaintext[i + 1];
        char encrypted_pair[2];
        encrypt_pair(a, b, key_matrix, encrypted_pair);
        ciphertext[idx++] = encrypted_pair[0];
        ciphertext[idx++] = encrypted_pair[1];
    }
    ciphertext[idx] = '\0';
}

int main() {
    char key[100], plaintext[200], processed_text[200], ciphertext[200];
    char key_matrix[SIZE][SIZE];

    // Input key and plaintext
    printf("Enter the key: ");
    fgets(key, sizeof(key), stdin);
    key[strcspn(key, "\n")] = '\0'; // Remove newline character from input

    printf("Enter the plaintext: ");
    fgets(plaintext, sizeof(plaintext), stdin);
    plaintext[strcspn(plaintext, "\n")] = '\0'; // Remove newline character from input

    // Create the key matrix
    create_key_matrix(key, key_matrix);

    // Display the key matrix
    printf("\nKey Matrix:\n");
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            printf("%c ", key_matrix[i][j]);
        }
        printf("\n");
    }

    // Preprocess the plaintext
    preprocess_text(plaintext, processed_text);
    printf("\nProcessed Text: %s\n", processed_text);

    // Encrypt the text
    encrypt_text(processed_text, key_matrix, ciphertext);
    printf("\nEncrypted Text: %s\n", ciphertext);

    return 0;
}