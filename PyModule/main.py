import os, sys
from inspect import getmembers

if os.name == 'nt':
    os.add_dll_directory('C:/TwinCAT/Common64')
    sys.path.append('C:/Users/StephanA/source/repos/DeviceManager_ADS_Samples/out/build/x64-Release/PyModule')

print("sys.path:")
print('\n'.join(sys.path))
print('os.name: {}'.format(os.name))

import DeviceManager
from DeviceManager import *
print('Loaded DeviceManager binary: {}'.format(DeviceManager.__file__))

#for attr in getmembers(DeviceManager):
#    print(attr)

amsNetId = "5.80.201.232.1.1.7.8"
ipAddr   = "192.168.1.98"

if os.name == 'nt':
    #cpu = CPU(amsNetId)
    tc  = TwinCAT(amsNetId)
else:
    #cpu = CPU(amsNetId, ipAddr)
    tc  = TwinCAT(amsNetId, ipAddr)

# for attr in getmembers(cpu):
#     print(attr)

#print('CPU frequency: ' + str(cpu.getFreq()) + ' MHz')
#print('CPU usage: ' + str(cpu.getUsage()) + ' %')
#print('CPU temperature: ' + str(cpu.getTemp()) + '°C')

print('TwinCAT version on target: ' + str(tc.getTcMajor()) + '.' + str(tc.getTcMinor()) + '.' + str(tc.getTcBuild()))
#tc.deleteAdsRoute('CX-50C9E8')
print('END')