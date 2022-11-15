import os, sys
from inspect import getmembers

if os.name == 'nt': # Check Python version 
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

amsNetId = "5.69.55.236.1.1"  # Windows 10
#amsNetId = "5.80.201.232.1.1" # TwinCAT/BSD
#ipAddr   = "192.168.1.98"
ipAddr   = "192.168.1.102"

if os.name == 'nt': 
    #cpu = CPU(amsNetId)
    #tc  = TwinCAT(amsNetId)
    #fs   = FileSystem(amsNetId)
    mb = Mainboard(amsNetId)
    #misc  = Miscellaneous(amsNetId)
    #general = General(amsNetId)
    #device = Device(amsNetId)
else:
    #cpu = CPU(amsNetId, ipAddr)
    #tc  = TwinCAT(amsNetId, ipAddr)
    #fs   = FileSystem(amsNetId, ipAddr) # tested
    #mb = Mainboard(amsNetId, ipAddr)
    #misc  = Miscellaneous(amsNetId, ipAddr)
    #general = General(amsNetId, ipAddr)
    device = Device(amsNetId, ipAddr)

#######
# CPU #
#######

# for attr in getmembers(cpu):
#     print(attr)

#print('CPU frequency: ' + str(cpu.getFreq()) + ' MHz')
#print('CPU usage: ' + str(cpu.getUsage()) + ' %')
#print('CPU temperature: ' + str(cpu.getTemp()) + '°C')

###########
# TWINCAT #
###########

#print('TwinCAT version on target: ' + str(tc.getTcMajor()) + '.' + str(tc.getTcMinor()) + '.' + str(tc.getTcBuild()))
#tc.deleteAdsRoute('CX-50C9E8')

###############
# FILE SYSTEM #
###############

#folders, files = fs.dir(r'/usr/local/etc/TwinCAT/3.1/Boot/*')

#print('>>> Folders: ')
#for _folder in folders:
#    print(_folder + '/')
#print('>>> Files')
#for _file in files:
#    print(_file)

# fs.deleteFile(r'/usr/local/etc/TwinCAT/3.1/Boot/test.txt', False)
#fs.mkdir(r'C:\TwinCAT\3.1\Boot\NewFolder')

#localFile = os.path.expanduser(os.sep.join(['~','Downloads', 'CurrentConfig.tszip']))
#fs.readFile(r'C:\TwinCAT\3.1\Boot\CurrentConfig.tszip', localFile)

#fs.writeFile(r'C:\TwinCAT\3.1\Boot\TestRoutes.xml', r'C:\TwinCAT\3.1\Target\StaticRoutes.xml')

#fs.copyFile(r'C:\TwinCAT\3.1\Boot\CurrentConfig.tszip', r'C:\TwinCAT\3.1\CurrentConfig_backup.tszip')

#############
# MAINBOARD #
#############
#print('Mainboard serila number: ' + mb.serialNumber())
#print('Mainboard minimal temperature: ' + str(mb.getMinTemp()) + '°C')
#print('Mainboard maximal temperature: ' + str(mb.getMaxTemp()) + '°C')
#print('Mainboard actual temperature: ' + str(mb.getTemp()) + '°C')

#misc.reboot()

################
# GENERAL AREA #
################
#print(general.deviceName())

################
# DEVICE AREA #
################
print(device.serialNumber())




print('END')