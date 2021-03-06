
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

    const std::string Device::getFrontendMapping(const Direction direction) const
    {
        return _device->getFrontendMapping(static_cast<int>(direction));
    }

    size_t Device::getNumberOfChannels(const Direction direction) const
    {
        return _device->getNumChannels(static_cast<int>(direction));
    }

    std::map<std::string, std::string> Device::getChannelInfo(const size_t channel,
                                                const Direction direction) const
    {
        return _device->getChannelInfo(static_cast<int>(direction), channel);
    }

    const std::vector<std::string> Device::getStreamFormats(const size_t channel,
                                            const Direction direction) const
    {
        return _device->getStreamFormats(static_cast<int>(direction), channel);
    }

    std::tuple<std::string, float> Device::getNativeStreamFormat(const size_t channel,
                                        const Direction direction) const
    {
        double fullScale;
        auto format =  _device->getNativeStreamFormat(static_cast<int>(direction),
                            channel, fullScale);
        return std::make_tuple(format, fullScale);
    }

    std::vector<SDRArgInfo> Device::getStreamArgsInfo(const size_t channel,
                                        const Direction direction) const
    {
        std::vector<SDRArgInfo> infoVec;
        std::vector<SoapySDR::ArgInfo> soapyInfoVec = _device->getStreamArgsInfo(
            static_cast<int>(direction), channel);
        for(auto& info : soapyInfoVec)
        {
            infoVec.push_back(SDRArgInfo(info));
        }
        return infoVec;
    }
}