#include <stdio.h>
#include <math.h>

// Function to calculate factorial
unsigned long long factorial(int n) {
    unsigned long long result = 1;
    for (int i = 1; i <= n; i++) {
        result *= i;
    }
    return result;
}

int main() {
    // Total number of letters in the Playfair cipher (A-Z without 'J')
    const int num_letters = 25;

    // Calculate total possible keys as 25!
    unsigned long long total_keys = factorial(num_letters);
    
    // Output total possible keys
    printf("Total possible keys for Playfair cipher: %llu\n", total_keys);
    
    // Estimate of effectively unique keys (simple estimate)
    // Assume a rough estimate of unique keys to be around 1/2 of total keys
    unsigned long long unique_keys = total_keys / 2;

    // Output estimated unique keys
    printf("Estimated effectively unique keys for Playfair cipher: %llu\n", unique_keys);

    // Displaying in terms of power of 2
    printf("Total possible keys (as power of 2): ~%llu\n", (unsigned long long)log2(total_keys));
    printf("Estimated effectively unique keys (as power of 2): ~%llu\n", (unsigned long long)log2(unique_keys));

    return 0;
}