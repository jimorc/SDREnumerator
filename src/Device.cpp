#include "../include/Device.h"

namespace SDR
{
    Device::Device(const SoapySDR::Kwargs& kwargs)
    {
        _device = SoapySDR::Device::make(kwargs);
    }

    Device::~Device()
    {
        if(_device != 0)
        {
            SoapySDR::Device::unmake(_device);
            _device = nullptr;
        }
    }

    const std::string Device::getDriverKey()  const
    {
        return _device->getDriverKey();
    }

    const std::string Device::getHardwareKey() const
    {
        return _device->getHardwareKey();
    }

    const SoapySDR::Kwargs Device::getHardwareInfo() const
    {
        return _device->getHardwareInfo();
    }

    const std::string Device::getRXFrontendMapping() const
    {
        return _device->getFrontendMapping(SOAPY_SDR_RX);
    }

    size_t Device::getNumberOfRXChannels() const
    {
        return _device->getNumChannels(SOAPY_SDR_RX);
    }
}