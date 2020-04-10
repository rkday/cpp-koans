#!/usr/bin/python3

import subprocess
import sys
import os

KOANS = [
"introduction.cpp"
"pointers.cpp"
        ]

def run_koan(cpp_file):
    print("=== Compiling koan {} ===".format(cpp_file))
    os.makedirs("build", exist_ok=True)
    output_file = "build/" + cpp_file.replace(".cpp", "")
    p = subprocess.run(["clang++", "-fsanitize=address", "-ferror-limit=2", "-Wall", "-Werror", "-Wno-tautological-constant-out-of-range-compare", "-o", output_file, "-I", "include", "src/" + cpp_file])
    p.check_returncode()
    print("=== Running koan {} ===".format(cpp_file))
    p = subprocess.run([output_file, "-a"])
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
        sys.exit(1)

