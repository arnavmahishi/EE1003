#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

// Function definitions for the quadratic equation
double f(double x) {
    return x * x - x - 306;  // Original quadratic equation
}

double f_derivative(double x) {
    return 2 * x - 1;  // Derivative of f(x)
}

// Fixed-point iteration functions for both roots
double g_positive(double x) {
    return sqrt(x + 306);  // For the positive root
}

double g_negative(double x) {
    return -sqrt(x + 306);  // For the negative root
}

// Random number generator for initial guesses
double random_double_in_range(double min, double max) {
    if (min > max) {
        fprintf(stderr, "Invalid range: min should be less than or equal to max.\n");
        return -1;
    }
    double scale = rand() / (double)RAND_MAX;  // Random value in [0, 1]
    return min + scale * (max - min);
}

// Fixed-point iteration function
int run_fixed_point_iterations(double (*g)(double), double init_guess, int num_iter, double tolerance) {
    for (int i = 0; i < num_iter; i++) {
        double next_guess = g(init_guess);

        printf("Iteration %d: x = %lf, f(x) = %lf\n", i + 1, next_guess, f(next_guess));

        // Check for convergence
        if (fabs(next_guess - init_guess) < tolerance) {
            printf("Converged to solution: x = %lf\n", next_guess);
            return 0;
        }

        init_guess = next_guess;
    }

    printf("Failed to converge within %d iterations.\n", num_iter);
    return -1;
}

// Newton-Raphson iteration function
int run_newton_iterations(double init_guess, int num_iter, double tolerance) {
    for (int i = 0; i < num_iter; i++) {
        if (fabs(f_derivative(init_guess)) < tolerance) {
            printf("Failure: Derivative too small\n");
            return -1;
        }

        double next_guess = init_guess - f(init_guess) / f_derivative(init_guess);

        printf("Iteration %d: x = %lf, f(x) = %lf\n", i + 1, next_guess, f(next_guess));

        // Check for convergence
        if (fabs(next_guess - init_guess) < tolerance) {
            printf("Converged to solution: x = %lf\n", next_guess);
            return 0;
        }

        init_guess = next_guess;
    }

    printf("Failed to converge within %d iterations.\n", num_iter);
    return -1;
}

int main() {
    srand(time(NULL));  // Seed the random number generator

    // Parameters for iterations
    int max_iterations = 1000;
    double tolerance = 1e-6;

    // Fixed-point iteration for both roots
    printf("Fixed-Point Iteration for Positive Root:\n");
    double init_guess_positive = random_double_in_range(0, 50);
    run_fixed_point_iterations(g_positive, init_guess_positive, max_iterations, tolerance);

    printf("\nFixed-Point Iteration for Negative Root:\n");
    double init_guess_negative = random_double_in_range(-306, 0);  // Ensure domain validity
    run_fixed_point_iterations(g_negative, init_guess_negative, max_iterations, tolerance);

    // Newton-Raphson iteration for both roots
    printf("\nNewton-Raphson Iteration for Positive Root:\n");
    double newton_guess_positive = random_double_in_range(0, 50);
    run_newton_iterations(newton_guess_positive, max_iterations, tolerance);

    printf("\nNewton-Raphson Iteration for Negative Root:\n");
    double newton_guess_negative = random_double_in_range(-50, 0);
    run_newton_iterations(newton_guess_negative, max_iterations, tolerance);

    return 0;
}

