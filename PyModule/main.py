from inspect import getmembers
import os, sys
import DeviceManager

print("sys.path:")
print('\n'.join(sys.path))

for attr in getmembers(DeviceManager):
    print(attr)

