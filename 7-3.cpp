#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TOTAL_LANES 25 // SHA-3 state has 25 lanes
#define LANE_BITS 64 // Each lane is 64 bits
#define CAPACITY_LANES 12 // SHA-3-1024 has 12 lanes for capacity (64 * 12 = 768 bits)

void initialize_state(unsigned long long state[]) {
    for (int i = 0; i < TOTAL_LANES; i++) {
        state[i] = 0; // Initialize all lanes to zero
    }
}

int all_capacity_nonzero(unsigned long long state[]) {
    for (int i = 0; i < CAPACITY_LANES; i++) {
        if (state[i] == 0) {
            return 0; // Found a lane in capacity that is still zero
        }
    }
    return 1; // All capacity lanes have at least one nonzero bit
}

void add_message_block(unsigned long long state[]) {
    // Simulate adding a message block, which sets a random bit in the state
    for (int i = 0; i < TOTAL_LANES; i++) {
        // Randomly set a bit in the lane to make it non-zero
        int bit_position = rand() % LANE_BITS; // Random bit position
        state[i] |= (1ULL << bit_position); // Set the bit at that position
    }
}

int main() {
    unsigned long long state[TOTAL_LANES];
    initialize_state(state);

    srand(time(NULL)); // Seed random number generator
    int count = 0;

    while (!all_capacity_nonzero(state)) {
        add_message_block(state);
        count++;
    }

    printf("It took %d message blocks before all capacity lanes had at least one nonzero bit.\n", count);
    
    return 0;
}