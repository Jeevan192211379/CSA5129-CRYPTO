#include <stdio.h>
#include <stdint.h>

// Function to perform modular exponentiation
uint64_t mod_exp(uint64_t base, uint64_t exp, uint64_t mod) {
    uint64_t result = 1;
    base = base % mod;
    while (exp > 0) {
        if (exp % 2 == 1)
            result = (result * base) % mod;
        exp = exp >> 1;
        base = (base * base) % mod;
    }
    return result;
}

// Function to perform Diffie-Hellman key exchange
void diffie_hellman(uint64_t p, uint64_t g, uint64_t a, uint64_t b) {
    uint64_t A = mod_exp(g, a, p); // Alice's public key
    uint64_t B = mod_exp(g, b, p); // Bob's public key

    uint64_t shared_secret_A = mod_exp(B, a, p); // Shared secret computed by Alice
    uint64_t shared_secret_B = mod_exp(A, b, p); // Shared secret computed by Bob

    printf("Alice's public key (A): %llu\n", A);
    printf("Bob's public key (B): %llu\n", B);
    printf("Shared secret computed by Alice: %llu\n", shared_secret_A);
    printf("Shared secret computed by Bob: %llu\n", shared_secret_B);
}

int main() {
    // Public parameters (prime number and generator)
    uint64_t p = 23; // Prime number
    uint64_t g = 5;  // Generator

    // Private keys for Alice and Bob
    uint64_t a = 6; // Alice's private key
    uint64_t b = 15; // Bob's private key

    // Perform Diffie-Hellman key exchange
    diffie_hellman(p, g, a, b);

    return 0;
}