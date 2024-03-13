#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define N 16
#define P 18

uint32_t P_array[P];
uint32_t S_boxes[4][256];

void F(uint32_t *l, uint32_t *r) {
    *l ^= P_array[0];
    *r ^= (((S_boxes[0][*l >> 24] + S_boxes[1][(*l >> 16) & 0xFF]) ^ S_boxes[2][(*l >> 8) & 0xFF]) + S_boxes[3][*l & 0xFF]);
}

void generate_boxes(const uint8_t *key, int key_length) {
    // Initialize P and S boxes
    // Your implementation here
}

void encrypt(uint32_t *left, uint32_t *right) {
    uint32_t l = *left, r = *right;
    for (int i = 0; i < N; ++i) {
        F(&l, &r);
        uint32_t temp = l; l = r; r = temp;
    }
    *left = l ^ P_array[N];
    *right = r;
}

void decrypt(uint32_t *left, uint32_t *right) {
    uint32_t l = *left, r = *right;
    for (int i = N + 1; i > 1; --i) {
        F(&l, &r);
        uint32_t temp = l; l = r; r = temp;
    }
    *left = l ^ P_array[1];
    *right = r;
}

int main() {
    // Key initialization and box generation
    uint8_t key[] = "my_secret_key";
    int key_length = strlen((char *)key);
    generate_boxes(key, key_length);

    // Message to encrypt
    uint32_t left = 0x00000000;
    uint32_t right = 0x00000000;

    // Encrypt the message
    encrypt(&left, &right);
    printf("Encrypted: %08X %08X\n", left, right);

    // Decrypt the message
    decrypt(&left, &right);
    printf("Decrypted: %08X %08X\n", left, right);

    return 0;
}
