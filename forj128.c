/* Forj128 - 128-bit educational hash function (Merkle-Damgard) */

#include "forj128.h"
#include <math.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

static uint32_t rotl32(uint32_t x, int s) {
    return (x << s) | (x >> (32 - s));
}

static uint32_t splitmix32(uint32_t *state) {
    uint32_t z = (*state += 0x9E3779B9u);
    z = (z ^ (z >> 16)) * 0x85EBCA6Bu;
    z = (z ^ (z >> 13)) * 0xC2B2AE35u;
    return z ^ (z >> 16);
}

static int is_prime(int n) {
    if (n < 2) return 0;
    for (int d = 2; (long)d * d <= n; d++)
        if (n % d == 0) return 0;
    return 1;
}

static void forj128_init_state(uint32_t state[4]) {
    static const int seed_primes[4] = {23, 29, 31, 37};
    for (int i = 0; i < 4; i++) {
        double root = sqrt((double)seed_primes[i]);
        double frac = root - floor(root);
        state[i] = (uint32_t)(frac * 4294967296.0);
    }
}

static void forj128_init_constants(uint32_t k[64]) {
    int count = 0, n = 2;
    while (count < 64) {
        if (is_prime(n)) {
            double root = pow((double)n, 1.0 / 5.0);
            double frac = root - floor(root);
            k[count] = (uint32_t)(frac * 4294967296.0);
            count++;
        }
        n++;
    }
}

static void forj128_init_sbox(uint8_t sbox[256]) {
    for (int i = 0; i < 256; i++) sbox[i] = (uint8_t)i;

    const char *seed_str = "FORJ128";
    uint32_t seed = 0;
    for (const char *p = seed_str; *p; p++) seed = seed * 131 + (uint8_t)(*p);

    for (int i = 255; i > 0; i--) {
        uint32_t r = splitmix32(&seed);
        int j = r % (uint32_t)(i + 1);
        uint8_t tmp = sbox[i];
        sbox[i] = sbox[j];
        sbox[j] = tmp;
    }
}

static void forj128_compress(uint32_t state[4], const uint8_t block[64],
                              const uint32_t k[64], const uint8_t sbox[256]) {
    uint32_t w[64];
    for (int i = 0; i < 16; i++) {
        w[i] = ((uint32_t)block[i * 4 + 0] << 24) |
               ((uint32_t)block[i * 4 + 1] << 16) |
               ((uint32_t)block[i * 4 + 2] << 8)  |
               ((uint32_t)block[i * 4 + 3]);
    }
    for (int i = 16; i < 64; i++) {
        w[i] = rotl32(w[i - 16] ^ w[i - 14] ^ w[i - 8] ^ w[i - 3], 1);
    }

    static const int rot[4] = {5, 9, 14, 20};

    uint32_t a = state[0], b = state[1], c = state[2], d = state[3];

    for (int i = 0; i < 64; i++) {
        uint32_t f;
        int group = i / 16;
        if (group == 0)      f = (b & c) | (~b & d);          /* choice */
        else if (group == 1) f = (b & d) | (c & ~d);
        else if (group == 2) f = b ^ c ^ d;                    /* parity */
        else                 f = c ^ (b | (~d));

        uint32_t t = rotl32(a + f + k[i] + w[i], rot[i % 4]);
        t = ((uint32_t)sbox[t & 0xFF]) ^ (t >> 8);

        uint32_t new_b = b + t;
        a = d;
        d = c;
        c = b;
        b = new_b;
    }

    state[0] += a;
    state[1] += b;
    state[2] += c;
    state[3] += d;
}


static void forj128_finalize(uint32_t state[4]) {
    state[0] ^= rotl32(state[3], 13);
    state[3] ^= rotl32(state[2], 17);
    state[2] ^= rotl32(state[1], 19);
    state[1] ^= rotl32(state[0], 23);
}

void forj128(const uint8_t *data, size_t len, uint8_t out[FORJ128_DIGEST_BYTES]) {
    uint32_t state[4];
    uint32_t k[64];
    uint8_t sbox[256];

    forj128_init_state(state);
    forj128_init_constants(k);
    forj128_init_sbox(sbox);

    size_t padded_len = len + 1 + 8;
    padded_len = ((padded_len + 63) / 64) * 64;

    uint8_t *buf = (uint8_t *)calloc(1, padded_len);
    memcpy(buf, data, len);
    buf[len] = 0x80;

    uint64_t bit_len = (uint64_t)len * 8;
    for (int i = 0; i < 8; i++) {
        buf[padded_len - 1 - i] = (uint8_t)(bit_len >> (8 * i));
    }

    for (size_t off = 0; off < padded_len; off += 64) {
        forj128_compress(state, buf + off, k, sbox);
    }

    free(buf);

    forj128_finalize(state);

    for (int i = 0; i < 4; i++) {
        out[i * 4 + 0] = (uint8_t)(state[i] >> 24);
        out[i * 4 + 1] = (uint8_t)(state[i] >> 16);
        out[i * 4 + 2] = (uint8_t)(state[i] >> 8);
        out[i * 4 + 3] = (uint8_t)(state[i]);
    }
}

void forj128_to_hex(const uint8_t digest[FORJ128_DIGEST_BYTES], char out_hex[33]) {
    static const char *hexchars = "0123456789abcdef";
    for (int i = 0; i < 16; i++) {
        out_hex[i * 2]     = hexchars[digest[i] >> 4];
        out_hex[i * 2 + 1] = hexchars[digest[i] & 0xF];
    }
    out_hex[32] = '\0';
}
