#ifndef FORJ128_H
#define FORJ128_H

#include <stddef.h>
#include <stdint.h>

#define FORJ128_DIGEST_BYTES 16

void forj128(const uint8_t *data, size_t len, uint8_t out[FORJ128_DIGEST_BYTES]);
void forj128_to_hex(const uint8_t digest[FORJ128_DIGEST_BYTES], char out_hex[33]);

#endif
