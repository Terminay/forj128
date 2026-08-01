from setuptools import setup
import os
import shutil
import subprocess
from pathlib import Path

repo_root = Path(__file__).resolve().parent.parent
python_pkg_dir = repo_root / "python" / "forj128"
source_file = repo_root / "forj128.c"

if os.name == "nt":
    lib_name = "forj128.dll"
else:
    lib_name = "libforj128.so"

build_target = python_pkg_dir / lib_name

if not build_target.exists() and source_file.exists():
    compiler = os.environ.get("CC") or ("clang" if shutil.which("clang") else "gcc")
    cmd = [compiler, "-shared", "-fPIC", "-O2", "-o", str(build_target), str(source_file), "-lm"]
    subprocess.run(cmd, cwd=str(repo_root), check=True)

package_data = {"forj128": [lib_name]}
if build_target.exists():
    package_data["forj128"].append(lib_name)

setup(
    name="forj128",
    version="1.0.1",
    description="Forj128 - Educational 128-bit hash function",
    author="Forj128",
    license="MIT",
    packages=["forj128"],
    package_dir={"forj128": "forj128"},
    package_data=package_data,
    data_files=[("", [lib_name])],
    include_package_data=True,
    install_requires=[],
    python_requires=">=3.6",
)