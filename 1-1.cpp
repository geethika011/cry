#include <stdio.h>
#include <string.h>
#include <ctype.h>


const char cipher[] = "53 pm pm+305))6^ * ;4826) 4 plus/minus 0.34 pm);806^ * ;48+8960))85;;]8^ * ;: pm "
                      "(88) 5^ * dagger;46(;88^ * 96^ * ?;8)^ * pm(;485);5^ * +2;^ * pm(;4956^ * 2(5^ * "
                      "-4818 4069285);)6+8)4 +++ ; 1(plus/minus 9; 48081; 8/8 plus/minus 1; 48 + 85; 4) * 485 + 52 8806*81 "
                      "($9:48;(88;4(1?34;48)4‡;161;:188;‡?;";


void count_frequency(const char *text, int freq[]) {
    for (int i = 0; text[i] != '\0'; i++) {
        if (text[i] != ' ' && text[i] != '\n') {
            freq[(unsigned char)text[i]]++;
        }
    }
}

// Function to print frequency analysis
void print_frequency(int freq[]) {
    printf("Character Frequency Analysis:\n");
    for (int i = 0; i < 128; i++) {
        if (freq[i] > 0) {
            printf("'%c': %d\n", i, freq[i]);
        }
    }
}

// Replace characters in the cipher text based on a key
void decrypt_text(const char *cipher, const char *key) {
    char result[strlen(cipher)];
    
    for (int i = 0; cipher[i] != '\0'; i++) {
        if (isalpha(cipher[i])) {
            result[i] = key[cipher[i] - 'a']; // assuming lowercase
        } else {
            result[i] = cipher[i]; // non-alphabetic characters remain unchanged
        }
    }
    result[strlen(cipher)] = '\0';
    printf("\nDecrypted Text:\n%s\n", result);
}

int main() {
    int freq[128] = {0};  // Array to store frequency of each character
    count_frequency(cipher, freq);
    
    // Step 1: Perform frequency analysis
    print_frequency(freq);

    // Step 2: Provide a substitution key manually (this will evolve as we decipher)
    // For example, after analyzing "the" and common words, we assume the following:
    // Cipher char to Plain char: 'p' -> 't', 'm' -> 'h', '5' -> 'e', and so on.
    
    // Let's assume we have a substitution key for lowercase letters
    char key[26] = {'t', 'h', 'e', 'a', 'o', 'n', 'r', 'i', 's', 'l', 'c', 'u', 'd', 'p', 'm', 'g', 'b', 'v', 'w', 'f', 'y', 'k', 'x', 'z', 'j', 'q'};
    
    // Step 3: Decrypt using the substitution key
    decrypt_text(cipher, key);
    
    return 0;
}