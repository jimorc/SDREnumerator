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

    const std::string Device::getTXFrontendMapping() const
    {
        return _device->getFrontendMapping(SOAPY_SDR_TX);
    }

    size_t Device::getNumberOfRXChannels() const
    {
        return _device->getNumChannels(SOAPY_SDR_RX);
    }

    size_t Device::getNumberOfTXChannels() const
    {
        return _device->getNumChannels(SOAPY_SDR_TX);
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
}