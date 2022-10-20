from DeviceManager import *
from inspect import getmembers
import os, sys

print("sys.path:")
print('\n'.join(sys.path))

#for attr in getmembers(DeviceManager):
#    print(attr)

cpu = CPU()

for attr in getmembers(cpu):
    print(attr)

