#ifndef FORJ128_H
#define FORJ128_H

#include <stddef.h>
#include <stdint.h>

#define FORJ128_DIGEST_BYTES 16

/* Computes the Forj128 digest of `data` (length `len` bytes) into `out`,
 * which must point to a buffer of at least FORJ128_DIGEST_BYTES. */
void forj128(const uint8_t *data, size_t len, uint8_t out[FORJ128_DIGEST_BYTES]);

/* Renders a digest as a 32-char lowercase hex string (33 bytes incl NUL). */
void forj128_to_hex(const uint8_t digest[FORJ128_DIGEST_BYTES], char out_hex[33]);

#endif
