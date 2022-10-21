#include "cpu.h"
#if defined(USE_TWINCAT_ROUTER)
	#include "TC1000_AdsClient.h"
#else
	#include "GenericAdsClient.h"
#endif

#include <iostream>


int CpuType_init(PyObject *self, PyObject *args, PyObject *kwds){
    std::cout << "CpuType init() called" << std::endl;
    
    static const AmsNetId remoteNetId{"5.80.201.232.1.1"};
    //static const AmsNetId remoteNetId{ 5, 80, 201, 232, 1, 1 };

#if defined(USE_TWINCAT_ROUTER)
	auto adsClient = std::shared_ptr<BasicADS>(new TC1000AdsClient(remoteNetId));
#else
	static const char remoteIpV4[] = "192.168.1.98";
	auto adsClient = std::shared_ptr<BasicADS>(new GenericAdsClient(remoteNetId, remoteIpV4));
#endif
	
    return 0;
}

void CpuType_dealloc(CpuType *self){
    std::cout << "CpuType dealloc() called" << std::endl;
}

PyObject* getTemp(PyObject *self, PyObject *args)
{
    return PyLong_FromUnsignedLong(123);
}
