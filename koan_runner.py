#!/usr/bin/python3

import subprocess
import sys
import os

KOANS = [
"introduction.cpp",
"pointers.cpp",
"references.cpp",
"const_compile.cpp",
"optional.cpp",
"namespaces.cpp",
"namespaces_compile.cpp"
        ]

def run_koan(cpp_file):
    print("=== Compiling koan {} ===".format(cpp_file))
    os.makedirs("build", exist_ok=True)
    output_file = "build/" + cpp_file.replace(".cpp", "")
    p = subprocess.run(["clang++", "-std=c++17", "-ferror-limit=2", "-Wall", "-Werror", "-Wno-tautological-constant-out-of-range-compare", "-Wno-unused-variable", "-o", output_file, "-I", "include", "src/" + cpp_file])
    p.check_returncode()
    print("=== Running koan {} ===".format(cpp_file))
    if os.environ.get("RUN_ALL"):
        p = subprocess.run([output_file])
    else:
        p = subprocess.run([output_file, '-a'])
    p.check_returncode()

successful = 0

if len(sys.argv) > 1:
    koans_to_run = sys.argv[1:]
else:
    koans_to_run = KOANS

for k in koans_to_run:
    try:
        run_koan(k)
        successful += 1
    except subprocess.CalledProcessError as e:
        print()
        print()
        print()
        print("{} out of {} koans ran successfully".format(successful, len(KOANS)))
        print("Koan src/{} failed".format(k))
        print("Check the output above and fix up the file to proceed")
        if os.environ.get("RUN_ALL"):
            continue
        sys.exit(1)

