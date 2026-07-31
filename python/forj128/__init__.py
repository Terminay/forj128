"""
Forj128 - Python bindings for the Forj128 hash function.

Example:
    >>> from forj128 import hash
    >>> digest = hash(b"hello world")
    >>> print(digest.hex())
    a1b2c3d4e5f6...
"""

import ctypes
import os
from pathlib import Path

# Load the shared library
_lib_path = Path(__file__).parent.parent / "libforj128.so"
if not _lib_path.exists():
    _lib_path = Path(__file__).parent.parent / "libforj128.dylib"
if not _lib_path.exists():
    _lib_path = Path(__file__).parent.parent / "forj128.dll"

_lib = ctypes.CDLL(str(_lib_path))

# Define function signatures
_lib.forj128.argtypes = [
    ctypes.POINTER(ctypes.c_uint8),
    ctypes.c_size_t,
    ctypes.POINTER(ctypes.c_uint8 * 16)
]
_lib.forj128.restype = None

_lib.forj128_to_hex.argtypes = [
    ctypes.POINTER(ctypes.c_uint8 * 16),
    ctypes.c_char_p
]
_lib.forj128_to_hex.restype = None


def hash(data: bytes) -> bytes:
    """
    Compute Forj128 hash of input data.
    
    Args:
        data: Input bytes to hash
        
    Returns:
        16-byte digest
    """
    digest = (ctypes.c_uint8 * 16)()
    _lib.forj128(data, len(data), ctypes.byref(digest))
    return bytes(digest)


def hash_hex(data: bytes) -> str:
    """
    Compute Forj128 hash and return as lowercase hex string.
    
    Args:
        data: Input bytes to hash
        
    Returns:
        32-character lowercase hex string
    """
    digest = hash(data)
    return digest.hex()


# Convenience function
def forj128(data: bytes) -> bytes:
    """Alias for hash()"""
    return hash(data)