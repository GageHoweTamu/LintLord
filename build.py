#!/usr/bin/env python3

import os
import sys
import subprocess
import json
from pathlib import Path

# This is a custom cross platform build script to compile this project and projects like it.

linux_build_command = "g++ simple.cpp -o main"
mac_build_command = "clang simple.cpp -o main"
windows_build_command = "msvc simple.cpp -o main"

def get_platform():
    if sys.platform.startswith('linux'):
        return 'linux'
    elif sys.platform == 'darwin':
        return 'mac'
    elif sys.platform == 'win32':
        return 'windows'
    else:
        return 'unknown'

def run_command(command):
    try:
        subprocess.run(command, shell=True, check=True)
    except subprocess.CalledProcessError as e:
        print(f"Error: {command}")
        print(f"Reason: {e}")
        sys.exit(1)

def build():
    platform = get_platform()
    if platform == 'linux':
        run_command(linux_build_command)
    elif platform == 'mac':
        run_command(mac_build_command)
    elif platform == 'windows':
        run_command(windows_build_command)
    else:
        print(f"Unsupported platform: {platform}")
        sys.exit(1)

def main():
    build()

if __name__ == "__main__":
    main()