#include <stdio.h>

// Function to calculate modular exponentiation
unsigned long long mod_exp(unsigned long long base, unsigned long long exp, unsigned long long mod) {
    unsigned long long result = 1;
    base = base % mod;
    while (exp > 0) {
        if (exp % 2 == 1)
            result = (result * base) % mod;
        exp = exp >> 1;
        base = (base * base) % mod;
    }
    return result;
}

// Function to encrypt plaintext using RSA public key
unsigned long long rsa_encrypt(unsigned long long plaintext, unsigned long long e, unsigned long long n) {
    return mod_exp(plaintext, e, n);
}

// Function to decrypt ciphertext using RSA private key
unsigned long long rsa_decrypt(unsigned long long ciphertext, unsigned long long d, unsigned long long n) {
    return mod_exp(ciphertext, d, n);
}

int main() {
    // RSA parameters (usually large prime numbers)
    unsigned long long p = 61;
    unsigned long long q = 53;
    unsigned long long n = p * q;
    unsigned long long phi = (p - 1) * (q - 1);
    unsigned long long e = 65537; // commonly used value for e
    unsigned long long d = 0;

    // Find the modular inverse of e mod phi
    for (unsigned long long i = 1; i < phi; ++i) {
        if ((e * i) % phi == 1) {
            d = i;
            break;
        }
    }

    // Message to be encrypted
    unsigned long long plaintext = 1234;

    // Encrypt plaintext
    unsigned long long encrypted = rsa_encrypt(plaintext, e, n);

    // Decrypt ciphertext
    unsigned long long decrypted = rsa_decrypt(encrypted, d, n);

    // Output results
    printf("Plaintext: %llu\n", plaintext);
    printf("Encrypted: %llu\n", encrypted);
    printf("Decrypted: %llu\n", decrypted);

    return 0;
}