/* Avalanche test: flip each input bit and measure output bit changes */

#include "forj128.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

static int popcount16(const uint8_t d1[16], const uint8_t d2[16]) {
    int count = 0;
    for (int i = 0; i < 16; i++) {
        uint8_t x = d1[i] ^ d2[i];
        while (x) { count += x & 1; x >>= 1; }
    }
    return count;
}

int main(void) {
    const char *base = "The quick brown fox jumps over the lazy dog";
    size_t len = strlen(base);

    uint8_t *input = (uint8_t *)malloc(len);
    memcpy(input, base, len);

    uint8_t base_digest[16];
    forj128(input, len, base_digest);

    long total_bits_flipped = 0;
    int trials = 0;

    for (size_t byte_i = 0; byte_i < len; byte_i++) {
        for (int bit_i = 0; bit_i < 8; bit_i++) {
            input[byte_i] ^= (1 << bit_i);   /* flip one bit */

            uint8_t digest[16];
            forj128(input, len, digest);

            int flipped = popcount16(base_digest, digest);
            total_bits_flipped += flipped;
            trials++;

            input[byte_i] ^= (1 << bit_i);   /* flip it back */
        }
    }

    double avg = (double)total_bits_flipped / trials;
    printf("Avalanche test over %d single-bit flips:\n", trials);
    printf("  Average bits flipped: %.2f (%.1f%%)\n",
           avg, (avg / 128.0) * 100.0);
    printf("  Ideal: 64.00 bits (50.0%%)\n");

    free(input);
    return 0;
}
