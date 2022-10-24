#!/bin/sh
# sudo dnf debuginfo-install python3-3.9.9-2.fc33.x86_64 
export PYTHONPATH="../build/PyModule/"
gdb --args python3 -i main.py
