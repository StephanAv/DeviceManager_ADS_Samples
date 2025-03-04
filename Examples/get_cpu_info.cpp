#if defined(USE_TWINCAT_ROUTER)
	#include "TC1000_AdsClient.h"
#else
	#include "GenericAdsClient.h"
#endif

#include "cpu.h"
#include "ads_error.h"
#include "ads_exception.h"
#include <iostream>
#include <optional>

int main() {

    static const AmsNetId remoteNetId{ 5, 80, 201, 232, 1, 1 };

#if defined(USE_TWINCAT_ROUTER)
	auto adsClient = std::shared_ptr<BasicADS>(new TC1000AdsClient(remoteNetId));
#else
	static const char remoteIpV4[] = "192.168.1.98";
	auto adsClient = std::shared_ptr<BasicADS>(new GenericAdsClient(remoteNetId, remoteIpV4));
#endif
	
	std::optional<DeviceManager::CPU> cpu;
	size_t size_opt_cpu_a = sizeof(cpu);
	try {
		cpu.emplace(*adsClient);
	}
	catch (const DeviceManager::AdsException& ex) {
		std::cout << ex.what() << std::endl;
		exit(-1);
	}

	if (!cpu) {
		std::cerr << "Module not available on target" << std::endl;
		return -1;
	}

	int32_t error = 0;

	uint32_t frequency = 0;
	error = cpu->getFrequency(frequency);
	handleError(error);
	std::cout << ">>> CPU frequency: " << frequency << "MHz" << std::endl;

	uint16_t usage = 0;
	error = cpu->getUsage(usage);
	handleError(error);
	std::cout << ">>> CPU usage: " << usage << "%" << std::endl;

	int16_t temperature = 0;
	error = cpu->getTemp(temperature);
	handleError(error);
	std::cout << ">>> CPU temperature: " << temperature << " C" << std::endl;
}