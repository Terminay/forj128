# forj128

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
[![C](https://img.shields.io/badge/Language-C-blue.svg)](https://en.wikipedia.org/wiki/C_(programming_language))
[![Build](https://img.shields.io/badge/Build-Make-green.svg)](https://www.gnu.org/software/make/)

**Educational 128-bit hash function implemented from scratch in C.**

> **Warning:** This is a learning project. It is **not cryptographically audited** and should **not** be used to protect real secrets.

## What It Is

Forj128 is a 128-bit cryptographic hash function demonstrating **Merkle-Damgard construction**. It processes data in 512-bit blocks and produces a 32-character hexadecimal digest.

**Key characteristics:**
- Built for learning how hash functions work
- Transparent design with runtime constant generation
- Measurable avalanche effect (~50% output bit flip rate)
- Fast and lightweight (no heavy dependencies)

## Installation

### Prerequisites

- GCC or Clang
- Make
- `libm` (standard C math library)

### Build from Source

```bash
git clone https://github.com/yourusername/forj128.git
cd forj128
make
```

This creates two binaries:
- `forj128_cli` - Command-line hash tool
- `avalanche_test` - Avalanche effect benchmark

## Usage

### Command Line

```bash
$ ./forj128_cli "hello world"
a1b2c3d4e5f6...
```

### C Library

```c
#include "forj128.h"

uint8_t digest[FORJ128_DIGEST_BYTES];
char hex[33];

forj128((const uint8_t *)"input", 5, digest);
forj128_to_hex(digest, hex);
printf("%s\n", hex);
```

### Python

Install the Python bindings:

```bash
cd python
pip install .
```

Or use directly with ctypes:

```python
from forj128 import hash, hash_hex

# Hash bytes
digest = hash(b"hello world")
print(digest.hex())  # a1b2c3d4e5f6...

# Get hex string directly
hex_str = hash_hex(b"hello world")
print(hex_str)
```

### Node.js / JavaScript

Build the native addon:

```bash
cd node
npm install
npm run build
```

Use in your code:

```javascript
const forj128 = require('./node');

// Hash string
const digest = forj128.hash("hello world");
console.log(digest.toString('hex'));

// Get hex string
const hex = forj128.hashHex("hello world");
console.log(hex);
```

### WebAssembly (WASM)

You can also compile to WebAssembly for browser use:

```bash
emcc forj128.c -o forj128.wasm -O2 -s EXPORTED_FUNCTIONS="['forj128']" -s EXPORTED_RUNTIME_METHODS="['ccall']"
```

## Run Tests

```bash
./avalanche_test
```

Example output:

```
Avalanche test over 2752 single-bit flips:
  Average bits flipped: 64.01 (50.0%)
  Ideal: 64.00 bits (50.0%)
```

## Design

| Aspect | Implementation | Details |
|--------|---------------|---------|
| **Construction** | Merkle-Damgard | Same as MD5, SHA-1, SHA-256 |
| **Digest size** | 128 bits | Four 32-bit words |
| **Block size** | 512 bits | Standard |
| **IV** | `sqrt(23,29,31,37)` frac. bits | Computed at runtime |
| **Round constants** | 5th root of first 64 primes | Computed at runtime |
| **S-box** | Generated from seed | Fisher-Yates shuffle |
| **Round function** | MD5-style with S-box | Adds "fingerprint" step |
| **Finalization** | Cross-XOR with rotation | "Forge" step |

### Key Features

- **Runtime constant generation** - No hardcoded magic numbers
- **Custom S-box** - Generated from seed using splitmix32 PRNG
- **Strong avalanche** - Each input bit flip changes ~50% of output bits
- **Cross-platform** - Works on Linux, macOS, Windows

## Project Structure

```
forj128/
├── forj128.h                  # Public API (C)
├── forj128.c                  # Core hash implementation
├── main.c                     # CLI tool
├── avalanche_test.c           # Avalanche effect benchmark
├── Makefile                   # Build system
├── LICENSE                    # MIT License
├── .gitignore                 # Git ignore rules
├── python/
│   ├── forj128/
│   │   └── __init__.py       # Python bindings (ctypes)
│   └── setup.py              # Python package setup
├── node/
│   ├── index.js              # Node.js wrapper
│   ├── binding.gyp           # node-gyp config
│   └── forj128_binding.cpp   # N-API/NAN bindings
└── README.md                  # This file
```

## Limitations

- Not peer-reviewed or cryptographically audited
- No formal proof of collision resistance
- S-box not tested for differential/linear cryptanalysis
- Not suitable for password hashing (no cost/work factor)

## When to Use This

**Good for:**
- Learning how hash functions work
- Teaching cryptography concepts
- Non-security-critical applications
- Experimenting with hash design

**Bad for:**
- Password hashing (use bcrypt/argon2 instead)
- Digital signatures (use SHA-256/SHA-3)
- Security-sensitive applications
- Production systems

## Contributing

This is an educational project. Contributions welcome!

1. Fork the repo
2. Create a branch (`git checkout -b feature/your-feature`)
3. Commit changes (`git commit -am 'Add feature'`)
4. Push (`git push origin feature/your-feature`)
5. Open a Pull Request
## License

MIT License - see [LICENSE](LICENSE) file for details. Feel free to use this code for learning purposes.

## Credits

Built as a learning exercise to understand hash function design. Inspired by MD5, SHA-1, SHA-256, and AES.

## Related Projects

- [hashlib](https://docs.python.org/3/library/hashlib.html) - Python's standard hash library
- [crypto](https://nodejs.org/api/crypto.html) - Node.js crypto module
- [OpenSSL](https://www.openssl.org/) - Production-grade cryptography

---

**Questions?** Open an issue or reach out. Happy hashing!
