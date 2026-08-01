#include "../forj128.h"
#include <stdio.h>
#include <string.h>

static int check_digest_consistency(void) {
    const char *input = "hello world";
    uint8_t digest1[FORJ128_DIGEST_BYTES];
    uint8_t digest2[FORJ128_DIGEST_BYTES];
    char hex1[33];
    char hex2[33];

    forj128((const uint8_t *)input, strlen(input), digest1);
    forj128((const uint8_t *)input, strlen(input), digest2);
    forj128_to_hex(digest1, hex1);
    forj128_to_hex(digest2, hex2);

    return memcmp(digest1, digest2, FORJ128_DIGEST_BYTES) == 0 && strcmp(hex1, hex2) == 0;
}

static int check_empty_input(void) {
    uint8_t digest[FORJ128_DIGEST_BYTES];
    char hex[33];

    forj128(NULL, 0, digest);
    forj128_to_hex(digest, hex);

    return hex[0] != '\0' && hex[32] == '\0';
}

static int check_different_inputs(void) {
    uint8_t digest_a[FORJ128_DIGEST_BYTES];
    uint8_t digest_b[FORJ128_DIGEST_BYTES];
    char hex_a[33];
    char hex_b[33];

    forj128((const uint8_t *)"alpha", 5, digest_a);
    forj128((const uint8_t *)"beta", 4, digest_b);
    forj128_to_hex(digest_a, hex_a);
    forj128_to_hex(digest_b, hex_b);

    return strcmp(hex_a, hex_b) != 0;
}

int main(void) {
    if (!check_digest_consistency()) {
        fprintf(stderr, "consistency test failed\n");
        return 1;
    }
    if (!check_empty_input()) {
        fprintf(stderr, "empty input test failed\n");
        return 1;
    }
    if (!check_different_inputs()) {
        fprintf(stderr, "distinct input test failed\n");
        return 1;
    }

    printf("All Forj128 tests passed.\n");
    return 0;
}
