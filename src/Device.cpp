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
}