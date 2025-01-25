#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TOTAL_NUMBERS 20 // Total numbers in the lottery
#define CHOICES 6        // Numbers chosen by the player

// Function to simulate the lottery and track relative frequency
void simulate_lottery(int simulations, int interval, double* results) {
    int win_count = 0;

    // Seed the random number generator
    srand(time(0));

    for (int i = 0; i < simulations; i++) {
        int fixed_numbers[CHOICES], chosen_numbers[CHOICES];
        int is_match = 1;

        // Generate fixed lottery numbers
        for (int j = 0; j < CHOICES; j++) {
            fixed_numbers[j] = (rand() % TOTAL_NUMBERS) + 1;
        }

        // Generate player's chosen numbers
        for (int j = 0; j < CHOICES; j++) {
            chosen_numbers[j] = (rand() % TOTAL_NUMBERS) + 1;
        }

        // Check for match
        for (int j = 0; j < CHOICES; j++) {
            if (fixed_numbers[j] != chosen_numbers[j]) {
                is_match = 0;
                break;
            }
        }

        if (is_match) {
            win_count++;
        }

        // Record relative frequency at intervals
        if ((i + 1) % interval == 0) {
            results[i / interval] = (double)win_count / (i + 1);
        }
    }
}
