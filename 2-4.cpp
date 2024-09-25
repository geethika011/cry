#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// English letter frequencies in decreasing order
const char english_letter_freq[] = "ETAOINSHRDLCUMWFGYPBVKJXQZ";

// Function to count the frequency of each letter in the ciphertext
void count_frequencies(const char *ciphertext, int freq[]) {
    // Initialize frequencies to 0
    for (int i = 0; i < 26; i++) {
        freq[i] = 0;
    }

    // Count frequency of each letter
    for (int i = 0; ciphertext[i] != '\0'; i++) {
        char ch = ciphertext[i];
        if (ch >= 'A' && ch <= 'Z') {
            freq[ch - 'A']++;
        } else if (ch >= 'a' && ch <= 'z') {
            freq[ch - 'a']++;
        }
    }
}

// Function to sort letters by frequency in descending order
void sort_by_frequency(int freq[], char sorted_letters[]) {
    int i, j, max_idx;

    // Initialize the sorted letters array with all alphabet letters
    for (i = 0; i < 26; i++) {
        sorted_letters[i] = 'A' + i;
    }

    // Sort letters by frequency using selection sort
    for (i = 0; i < 25; i++) {
        max_idx = i;
        for (j = i + 1; j < 26; j++) {
            if (freq[j] > freq[max_idx]) {
                max_idx = j;
            }
        }

        // Swap the frequencies and corresponding letters
        int temp_freq = freq[i];
        freq[i] = freq[max_idx];
        freq[max_idx] = temp_freq;

        char temp_char = sorted_letters[i];
        sorted_letters[i] = sorted_letters[max_idx];
        sorted_letters[max_idx] = temp_char;
    }
}

// Function to map ciphertext letters to English letter frequencies
void create_substitution_mapping(const char sorted_letters[], const char letter_freq[], char mapping[]) {
    for (int i = 0; i < 26; i++) {
        mapping[sorted_letters[i] - 'A'] = letter_freq[i];
    }
}

// Function to decrypt the ciphertext using the generated mapping
void decrypt_ciphertext(const char *ciphertext, const char mapping[], char *plaintext) {
    for (int i = 0; ciphertext[i] != '\0'; i++) {
        char ch = ciphertext[i];

        if (ch >= 'A' && ch <= 'Z') {
            plaintext[i] = mapping[ch - 'A'];
        } else if (ch >= 'a' && ch <= 'z') {
            plaintext[i] = mapping[ch - 'a'] + ('a' - 'A'); // To preserve lowercase
        } else {
            plaintext[i] = ch; // Copy non-alphabet characters as they are
        }
    }
    plaintext[strlen(ciphertext)] = '\0'; // Null-terminate the plaintext string
}

// Function to print top N possible plaintexts
void print_top_plaintexts(const char *ciphertext, const int freq[], int top_n) {
    char sorted_letters[26];
    sort_by_frequency(freq, sorted_letters); // Sort the ciphertext letters by frequency

    char mapping[26]; // To store the mapping for each letter
    char freq_copy[27]; // Copy of english_letter_freq to rotate for each guess

    // Copy the original letter frequency into a temporary variable
    strcpy(freq_copy, english_letter_freq);

    // Print the top N possible plaintexts by shifting mappings
    for (int i = 0; i < top_n; i++) {
        char plaintext[256];
        create_substitution_mapping(sorted_letters, freq_copy, mapping);
        decrypt_ciphertext(ciphertext, mapping, plaintext);

        printf("Possible plaintext #%d: %s\n", i + 1, plaintext);

        // Rotate the English letter frequency by 1 to generate the next guess
        char temp = freq_copy[0];
        memmove(freq_copy, freq_copy + 1, 25);
        freq_copy[25] = temp;
    }
}

int main() {
    char ciphertext[256];
    int freq[26]; // To store the frequency of each letter

    printf("Enter the ciphertext: ");
    fgets(ciphertext, sizeof(ciphertext), stdin);
    
    // Remove newline character from input
    ciphertext[strcspn(ciphertext, "\n")] = '\0';

    // Count the frequency of letters in the ciphertext
    count_frequencies(ciphertext, freq);

    int top_n;
    printf("Enter the number of top possible plaintexts to display: ");
    
    // Ensure valid input for top_n
    while (scanf("%d", &top_n) != 1 || top_n <= 0) {
        printf("Please enter a positive integer: ");
        while(getchar() != '\n'); // Clear invalid input from buffer
    }

    // Print the top N possible plaintexts
    print_top_plaintexts(ciphertext, freq, top_n);

    return 0;
}