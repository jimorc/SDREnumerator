#include "../include/Devices.h"

namespace SDR
{
    std::vector<SDR::Device> Devices::getDevices()
    {
        std::vector<SoapySDR::Kwargs> kList = SoapySDR::Device::enumerate();
        std::vector<SDR::Device> devices;
        devices.reserve(kList.size());
        for(size_t i = 0; i < kList.size(); ++i)
        {
            devices.push_back(SDR::Device(kList[i]));
        }
        return devices;
    }
}