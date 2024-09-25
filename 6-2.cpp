#include <stdio.h>
#include <math.h> // Include math.h for log2 function

// Function to calculate factorial
unsigned long long factorial(int n) {
    unsigned long long result = 1;
    for (int i = 1; i <= n; i++) {
        result *= i;
    }
    return result;
}

// Estimate the total possible keys for Playfair
unsigned long long total_possible_keys() {
    return factorial(25); // Roughly using the first 25 letters (A-Z excluding J)
}

// Main function
int main() {
    unsigned long long possible_keys = total_possible_keys();
    double log2_possible_keys = log2(possible_keys); // Log base 2 of possible keys

    // For effectively unique keys (hypothetical example)
    // This would generally require complex combinatorial mathematics to determine accurately
    unsigned long long effectively_unique_keys = possible_keys / 100; // Arbitrary divisor for uniqueness

    printf("Approximate number of possible keys: %llu\n", possible_keys);
    printf("Expressed as power of 2: ~%.2f\n", log2_possible_keys);
    printf("Estimated effectively unique keys: %llu\n", effectively_unique_keys);

    return 0;
}