import os, sys
from inspect import getmembers
sys.path.append('C:/Users/StephanA/source/repos/DeviceManager_ADS_Samples/out/build/x64-Release/PyModule')
# C:\Users\StephanA\source\repos\DeviceManager_ADS_Samples\out\build\x64-Release\PyModule
print("sys.path:")
print('\n'.join(sys.path))
print('os.name: {}'.format(os.name))
# https://learn.microsoft.com/en-us/visualstudio/python/debugging-mixed-mode-c-cpp-python-in-visual-studio?view=vs-2019
os.add_dll_directory('C:\\Users\\StephanA\\source\\repos\\DeviceManager_ADS_Samples\\out\\build\\x64-Debug\\PyModule')

import DeviceManager
from DeviceManager import *
print('Loaded DeviceManager binary: {}'.format(DeviceManager.__file__))


#for attr in getmembers(DeviceManager):
#    print(attr)
amsNetId = "5.80.201.232.1.1"
#ipAddr   = "192.168.1.98"
#ipAddr   = "192.168.1"

if os.name == 'nt':
    cpu = CPU(amsNetId)
else:
    cpu = CPU(amsNetId, ipAddr)

# for attr in getmembers(cpu):
#     print(attr)

