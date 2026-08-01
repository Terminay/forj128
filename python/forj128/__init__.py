"""
Forj128 - Python bindings for the Forj128 hash function.

Example:
    >>> from forj128 import hash
    >>> digest = hash(b"hello world")
    >>> print(digest.hex())
    a1b2c3d4e5f6...
"""

import ctypes
from pathlib import Path


def _resolve_library() -> Path:
    package_dir = Path(__file__).resolve().parent
    candidates = [
        package_dir / "libforj128.so",
        package_dir / "libforj128.dylib",
        package_dir / "forj128.dll",
        package_dir.parent / "libforj128.so",
        package_dir.parent / "libforj128.dylib",
        package_dir.parent / "forj128.dll",
    ]
    for candidate in candidates:
        if candidate.exists():
            return candidate
    raise FileNotFoundError("Could not locate the forj128 shared library. Build it first or install the package with the bundled binary.")


_lib = ctypes.CDLL(str(_resolve_library()))

# Define function signatures
_lib.forj128.argtypes = [
    ctypes.POINTER(ctypes.c_uint8),
    ctypes.c_size_t,
    ctypes.POINTER(ctypes.c_uint8 * 16),
]
_lib.forj128.restype = None


def hash(data: bytes) -> bytes:
    """
    Compute Forj128 hash of input data.
    
    Args:
        data: Input bytes to hash
        
    Returns:
        16-byte digest
    """
    if not isinstance(data, (bytes, bytearray)):
        raise TypeError("data must be bytes-like")

    data_bytes = bytes(data)
    digest = (ctypes.c_uint8 * 16)()
    buffer = (ctypes.c_uint8 * len(data_bytes)).from_buffer_copy(data_bytes)
    _lib.forj128(buffer, len(data_bytes), ctypes.byref(digest))
    return bytes(digest)


def hash_hex(data: bytes) -> str:
    """
    Compute Forj128 hash and return as lowercase hex string.
    
    Args:
        data: Input bytes to hash
        
    Returns:
        32-character lowercase hex string
    """
    return hash(data).hex()


# Convenience function
def forj128(data: bytes) -> bytes:
    """Alias for hash()"""
    return hash(data)