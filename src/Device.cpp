#include "../include/Device.h"

namespace SDR
{
    Device::Device(const SoapySDR::Kwargs& kwargs) 
        : _kwargs(kwargs)
    {
        _device = SoapySDR::Device::make(kwargs);
    }

    Device::Device(Device&& dev)
        : _kwargs(dev._kwargs)
    {
        _device = dev._device;
        dev._device = nullptr;
    }

    Device::~Device()
    {
        if(_device != nullptr)
        {
            SoapySDR::Device::unmake(_device);
            _device = nullptr;
        }
    }

    const std::string Device::operator[](const std::string& key) const
    {
        if(_kwargs.find(key) != _kwargs.cend())
        {
            return _kwargs.at(key);
        }
        else
        {
            return "not found";
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

    const std::string Device::getFrontendMapping(const int direction) const
    {
        return _device->getFrontendMapping(direction);
    }

    size_t Device::getNumberOfChannels(const int direction) const
    {
        return _device->getNumChannels(direction);
    }

    SoapySDR::Kwargs Device::getRXChannelInfo(size_t channel) const
    {
        return _device->getChannelInfo(SOAPY_SDR_RX, channel);
    }

    SoapySDR::Kwargs Device::getTXChannelInfo(size_t channel) const
    {
        return _device->getChannelInfo(SOAPY_SDR_TX, channel);
    }

    const std::vector<std::string> Device::getRXStreamFormats(size_t channel) const
    {
        return _device->getStreamFormats(SOAPY_SDR_RX, channel);
    }

    const std::vector<std::string> Device::getTXStreamFormats(size_t channel) const
    {
        return _device->getStreamFormats(SOAPY_SDR_TX, channel);
    }
}