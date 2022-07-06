#include "BDM_ConfigurationArea.h"
#include "Mdp.h"
#include "BasicADS.h"

#include <iostream>
#include <cstddef>
#include <cstring>
#include <cstdint>

#if defined _WIN32 || defined __FreeBSD__
#include "TcAdsDef.h"
#else
#include "AdsDef.h"
#endif



ConfigurationArea::ConfigurationArea(BasicADS* adsClient)
	: m_adsClient(*adsClient) {};

ConfigurationArea::ConfigurationArea(const ConfigurationArea& other)
	: m_adsClient(other.m_adsClient) {};

ConfigurationArea& ConfigurationArea::operator=(const ConfigurationArea& other){
	m_adsClient = other.m_adsClient;
	return *this;
}




void ConfigurationArea::readModules() {

	uint32_t n_err = 0;
	uint32_t n_bytesRead = 0;

	// Read length of list of module IDs https://infosys.beckhoff.com/content/1031/devicemanager/45035996536742667.html?id=5503267175110745821
	uint16_t u16_len_module_id_list = 0;
	n_err = m_adsClient.AdsReadReq(MDP_IDX_GRP, MDP_IDX_OFFS_DEVICE_AREA, sizeof(u16_len_module_id_list), &u16_len_module_id_list, &n_bytesRead);

	if (n_err != ADSERR_NOERR) {
		std::cout << "Error AdsSyncReadReq: 0x" << std::hex << n_err << std::endl;
		exit(-1);
	}

	std::cout << "Number of MDP modules available on target: " << u16_len_module_id_list << std::endl;

	// Download table of module IDs (Configuration Area)
	for (int i = 1; i < u16_len_module_id_list; ++i) {

		uint32_t  u32_module_entry = 0;
		uint32_t indexOffset = MDP_IDX_OFFS_DEVICE_AREA + i;
		n_err = m_adsClient.AdsReadReq(MDP_IDX_GRP, indexOffset, sizeof(u32_module_entry), &u32_module_entry, &n_bytesRead);

		if (n_err != ADSERR_NOERR) {
			std::cout << "Error AdsSyncReadReq: 0x" << std::hex << n_err << std::endl;
			break;
		}

		uint16_t u16_highWord = u32_module_entry >> 16; // ModuleType
		uint16_t u16_lowWord = u32_module_entry & 0xFF; // ModuleId

		switch (u16_highWord) {
		case MODULETYPE_ACCESSCTRL:
			std::cout << "MODULETYPE_ACCESSCTRL " << u16_lowWord << std::endl;
			break;
		case MODULETYPE_NIC:
			std::cout << "MODULETYPE_NIC " << u16_lowWord << std::endl;
			//changeIPAddress(u16_lowWord);
			break;
		case MODULETYPE_TIME:
			std::cout << "MODULETYPE_TIME " << u16_lowWord << std::endl;
			break;
		case MODULETYPE_USERMGMT:
			std::cout << "MODULETYPE_USERMGMT " << u16_lowWord << std::endl;
			break;
		case MODULETYPE_RAS:
			std::cout << "MODULETYPE_RAS " << u16_lowWord << std::endl;
			break;
		case MODULETYPE_FTP:
			std::cout << "MODULETYPE_FTP " << u16_lowWord << std::endl;
			break;
		case MODULETYPE_SMB:
			std::cout << "MODULETYPE_SMB " << u16_lowWord << std::endl;
			break;
		case MODULETYPE_TWINCAT:
			std::cout << "MODULETYPE_TWINCAT " << u16_lowWord << std::endl;
			//deleteAdsRoute(u16_lowWord);
			break;
		case MODULETYPE_DATASTORE:
			std::cout << "MODULETYPE_DATASTORE " << u16_lowWord << std::endl;
			break;
		case MODULETYPE_SOFTWARE:
			std::cout << "MODULETYPE_SOFTWARE " << u16_lowWord << std::endl;
			break;
		case MODULETYPE_CPU:
			std::cout << "MODULETYPE_CPU " << u16_lowWord << std::endl;
			readCPU(u16_lowWord);
			break;
		case MODULETYPE_MEMORY:
			std::cout << "MODULETYPE_MEMORY " << u16_lowWord << std::endl;
			break;
		case MODULETYPE_LOGFILE:
			std::cout << "MODULETYPE_LOGFILE " << u16_lowWord << std::endl;
			break;
		case MODULETYPE_FIREWALLCE:
			std::cout << "MODULETYPE_FIREWALLCE " << u16_lowWord << std::endl;
			break;
		case MODULETYPE_FW_RULES:
			std::cout << "MODULETYPE_FW_RULES " << u16_lowWord << std::endl;
			break;
		case MODULETYPE_FSO:
			std::cout << "MODULETYPE_FSO " << u16_lowWord << std::endl;
			break;
		case MODULETYPE_REGISTRY:
			std::cout << "MODULETYPE_REGISTRY " << u16_lowWord << std::endl;
			break;
		case MODULETYPE_PLC:
			std::cout << "MODULETYPE_PLC " << u16_lowWord << std::endl;
			break;
		case MODULETYPE_DISPLAY:
			std::cout << "MODULETYPE_DISPLAY " << u16_lowWord << std::endl;
			break;
		case MODULETYPE_EWF:
			std::cout << "MODULETYPE_EWF " << u16_lowWord << std::endl;
			break;
		case MODULETYPE_FBWF:
			std::cout << "MODULETYPE_FBWF " << u16_lowWord << std::endl;
			break;
		case MODULETYPE_REGFILTER:
			std::cout << "MODULETYPE_REGFILTER " << u16_lowWord << std::endl;
			break;
		case MODULETYPE_SILICONDRIVE:
			std::cout << "MODULETYPE_SILICONDRIVE " << u16_lowWord << std::endl;
			break;
		case MODULETYPE_OS:
			std::cout << "MODULETYPE_OS " << u16_lowWord << std::endl;
			break;
		case MODULETYPE_RAID:
			std::cout << "MODULETYPE_RAID " << u16_lowWord << std::endl;
			break;
		case MODULETYPE_CX9FLASH:
			std::cout << "MODULETYPE_CX9FLASH " << u16_lowWord << std::endl;
			break;
		case MODULETYPE_FAN:
			std::cout << "MODULETYPE_FAN " << u16_lowWord << std::endl;
			break;
		case MODULETYPE_MAINBOARD:
			std::cout << "MODULETYPE_MAINBOARD " << u16_lowWord << std::endl;
			break;
		case MODULETYPE_DISKMGMT:
			std::cout << "MODULETYPE_DISKMGMT " << u16_lowWord << std::endl;
			break;
		case MODULETYPE_UPS:
			std::cout << "MODULETYPE_UPS " << u16_lowWord << std::endl;
			break;
		case MODULETYPE_PHYSICALDRIVE:
			std::cout << "MODULETYPE_PHYSICALDRIVE " << u16_lowWord << std::endl;
			break;
		case MODULETYPE_MASSSTORAGEMONITORING:
			std::cout << "MODULETYPE_MASSSTORAGEMONITORING " << u16_lowWord << std::endl;
			break;
		case MODULETYPE_MISC:
			std::cout << "MODULETYPE_MISC " << u16_lowWord << std::endl;
			//rebootDevice(u16_lowWord);
			break;
		} // switch case
	} // For loop
}

void ConfigurationArea::changeIPAddress(unsigned short moduleId) {

	// https://infosys.beckhoff.com/content/1031/devicemanager/263013131.html 
	uint32_t n_err = 0;
	uint32_t strLen = 0;

	uint32_t u32_NIC_properties = 0;
	u32_NIC_properties = 0x8001 + (moduleId << 4);
	u32_NIC_properties = (u32_NIC_properties << 16) + 2; // subindex for IP-Address

	char s_ipAddr[50] = {};
	n_err = m_adsClient.AdsReadReq(MDP_IDX_GRP, u32_NIC_properties, sizeof(s_ipAddr), s_ipAddr, &strLen);

	if (n_err != ADSERR_NOERR) {
		std::cout << "Error AdsSyncReadReq: 0x" << std::hex << n_err << std::endl;
		exit(-1);
	}

	s_ipAddr[strLen] = 0;

	std::cout << ">>> Current IP-Address:: " << s_ipAddr << std::endl;

	// Change IP-Address of NIC 1

	if (moduleId == 1) {

		std::cout << ">>> Changing IP-Address..." << std::endl;

		char new_address[] = "192.168.3.106";

		// Write new address
		n_err = m_adsClient.AdsWriteReq(MDP_IDX_GRP, u32_NIC_properties, strlen(new_address), new_address);
		if (n_err != ADSERR_NOERR) {
			std::cout << "Error AdsSyncReadReq: 0x" << std::hex << n_err << std::endl;
			exit(-1);
		}

		// Read new address again
		n_err = m_adsClient.AdsReadReq(MDP_IDX_GRP, u32_NIC_properties, sizeof(s_ipAddr), s_ipAddr, &strLen);
		if (n_err != ADSERR_NOERR) {
			std::cout << "Error AdsSyncReadReq: 0x" << std::hex << n_err << std::endl;
			exit(-1);
		}
		s_ipAddr[strLen] = 0;

		std::cout << ">>> New IP-Address:: " << s_ipAddr << std::endl;
	}
}

void ConfigurationArea::deleteAdsRoute(unsigned short moduleId) {
	char route_name[] = "CX-50C9E8";
	std::cout << ">>> Delete ADS Route \"" << route_name << "\"" << std::endl;
	// https://infosys.beckhoff.com/content/1031/devicemanager/263030539.html?id=1967927695808387382 

	char service_transfer_object[50] = {};
	size_t route_name_length = strlen(route_name);

	// Copy length of route name to service transfer object
	*reinterpret_cast<uint32_t*>(service_transfer_object) = route_name_length;
	// Copy the route name to the service transfer object
	memcpy(service_transfer_object + sizeof(uint32_t), route_name, route_name_length);

	uint32_t u32_del_ads_route_idx = 0xB001 + (moduleId << 4);
	u32_del_ads_route_idx = (u32_del_ads_route_idx << 16) + 1; // Subindex "Write Data"

	uint32_t n_err = 0;
	n_err = m_adsClient.AdsWriteReq(MDP_IDX_GRP, u32_del_ads_route_idx, sizeof(uint32_t) + route_name_length, service_transfer_object);

	if (n_err != ADSERR_NOERR) {
		std::cout << "Error AdsSyncWriteReq: 0x" << std::hex << n_err << std::endl;
		exit(-1);
	}

	std::cout << ">>> Route deleteded successful" << std::endl;
}


void ConfigurationArea::readCPU(unsigned short moduleId) {

	std::cout << ">>> Read CPU Information:" << std::endl;
	uint32_t n_err = 0;
	uint32_t n_bytesRead = 0;

	// https://infosys.beckhoff.com/content/1033/devicemanager/54043195791430411.html?id=2286125776581746345

	/***********************************************
	 *                                             *
	 *             Read CPU frqeuency              *
	 *                                             *
	 ***********************************************/

	uint32_t u32_cpu_freq_idx = 0;
	u32_cpu_freq_idx = 0x8000 + (moduleId << 4) + 1; // +1 for CPU properties table
	u32_cpu_freq_idx = (u32_cpu_freq_idx << 16) + 1;   // 1 = Subindex of CPU frequency

	uint32_t u32_cpu_freq = 0;
	n_err = m_adsClient.AdsReadReq(MDP_IDX_GRP, u32_cpu_freq_idx, sizeof(u32_cpu_freq), &u32_cpu_freq, &n_bytesRead);

	if (n_err != ADSERR_NOERR) {
		std::cout << "Error AdsSyncReadReq: 0x" << std::hex << n_err << std::endl;
		exit(-1);
	}

	std::cout << ">>> CPU frequency: " << u32_cpu_freq << "MHz" << std::endl;

	/***********************************************
	 *                                             *
	 *               Read CPU usage                *
	 *                                             *
	 ***********************************************/

	uint32_t u32_cpu_usage_idx = 0;
	u32_cpu_usage_idx = 0x8000 + (moduleId << 4) + 1;	// + 1 for CPU properties table
	u32_cpu_usage_idx = (u32_cpu_usage_idx << 16) + 2;	// 2 = Subindex of CPU usage

	uint16_t u16_cpu_usage = 0;
	n_err = m_adsClient.AdsReadReq(MDP_IDX_GRP, u32_cpu_usage_idx, sizeof(u16_cpu_usage), &u16_cpu_usage, &n_bytesRead);

	if (n_err != ADSERR_NOERR) {
		std::cout << "Error AdsSyncReadReq: 0x" << std::hex << n_err << std::endl;
		exit(-1);
	}

	std::cout << ">>> CPU usage: " << u16_cpu_usage << "%" << std::endl;

	/***********************************************
	 *                                             *
	 *            Read CPU Temperature             *
	 *                                             *
	 ***********************************************/

	uint32_t u32_cpu_temp_idx = 0;
	u32_cpu_temp_idx = 0x8000 + (moduleId << 4) + 1; // + 1 for CPU properties table
	u32_cpu_temp_idx = (u32_cpu_temp_idx << 16) + 3; // 3 = Subindex of CPU temeprature

	uint16_t u16_cpu_temperature = 0;
	n_err = m_adsClient.AdsReadReq(MDP_IDX_GRP, u32_cpu_temp_idx, sizeof(u16_cpu_temperature), &u16_cpu_temperature, &n_bytesRead);

	if (n_err != ADSERR_NOERR) {
		std::cout << "Error AdsSyncReadReq: 0x" << std::hex << n_err << std::endl;
		exit(-1);
	}
	std::cout << ">>> CPU temperature: " << u16_cpu_temperature << " C" << std::endl;
}

void ConfigurationArea::rebootDevice(unsigned short moduleId) {

	std::cout << ">>> Read Miscellaneous Information:" << std::endl;
	uint32_t n_err = 0;
	uint32_t n_bytesRead = 0;

	/***********************************************
	 *                                             *
	 *    Read the state of the Security Wizard    *
	 *                                             *
	 ***********************************************/

	uint32_t u32_secWizard = 0;
	u32_secWizard = 0x8001 + (moduleId << 4);
	u32_secWizard = (u32_secWizard << 16) + 4; // 4 == Subindex for Security Wizard

	unsigned char bSecWizardState = 0;
	n_err = m_adsClient.AdsReadReq(MDP_IDX_GRP, u32_secWizard, sizeof(bSecWizardState), &bSecWizardState, &n_bytesRead);

	if (n_err != ADSERR_NOERR) {
		std::cout << "Error AdsSyncReadReq: 0x" << std::hex << n_err << std::endl;
		exit(-1);
	}
	std::cout << ">>> Security Wizard: " << std::boolalpha << static_cast<bool>(bSecWizardState) << std::endl;

	/**********************************************
	 *                                            *
	 *              Reboot the device             *
	 *                                            *
	 **********************************************/
	 // https://infosys.beckhoff.com/content/1033/devicemanager/263010571.html?id=2359555515732312853 

	uint32_t u32_reboot = 0;
	u32_reboot = 0xB001 + (moduleId << 4);
	u32_reboot = (u32_reboot << 16) + 1; // SubIndex = 1 as described in https://infosys.beckhoff.com/content/1033/devicemanager/263036171.html
	unsigned char dummy = 0;

	n_err = m_adsClient.AdsWriteReq(MDP_IDX_GRP, u32_reboot, sizeof(dummy), &dummy);

	if (n_err != ADSERR_NOERR) {
		std::cout << "Error AdsSyncReadReq: 0x" << std::hex << n_err << std::endl;
		exit(-1);
	}
	std::cout << ">>> Reboot Requested" << std::endl;
}