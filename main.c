#include "forj128.h"
#include <stdio.h>
#include <string.h>

int main(int argc, char **argv) {
    if (argc < 2) {
        fprintf(stderr, "usage: %s <string>\n", argv[0]);
        return 1;
    }
    uint8_t digest[FORJ128_DIGEST_BYTES];
    char hex[33];

    forj128((const uint8_t *)argv[1], strlen(argv[1]), digest);
    forj128_to_hex(digest, hex);

    printf("%s\n", hex);
    return 0;
}
