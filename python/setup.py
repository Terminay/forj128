from setuptools import setup, Extension
import os

# Determine the shared library extension
lib_name = "libforj128.so"
if os.path.exists("forj128.dll"):
    lib_name = "forj128.dll"
elif os.path.exists("libforj128.dylib"):
    lib_name = "libforj128.dylib"

setup(
    name="forj128",
    version="1.0.0",
    description="Forj128 - Educational 128-bit hash function",
    author="Forj128",
    license="MIT",
    packages=["forj128"],
    package_dir={"forj128": "forj128"},
    package_data={"forj128": [lib_name]},
    data_files=[("", [lib_name])],
    install_requires=[],
    python_requires=">=3.6",
)