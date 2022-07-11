#pragma once
#include "SoapySDR/Device.hpp"
#include "Enums.h"

namespace SDR
{
    class Device
    {
        public:
            Device() = delete;
            Device(const SoapySDR::Kwargs& kwargs);
            Device(const Device&) = delete;
            Device(Device&&);
            ~Device();
            Device& operator=(const Device&) = delete;
            Device&& operator=(Device&&) = delete;
            const std::string operator[](const std::string& key) const;
            operator SoapySDR::Device*() const { return _device; }
            operator SoapySDR::Kwargs() const { return _kwargs; }
            const std::string getDriverKey() const;
            const std::string getHardwareKey() const;
            const SoapySDR::Kwargs getHardwareInfo() const;
            const std::string getFrontendMapping(const Direction direction) const; 
            size_t getNumberOfChannels(const Direction direction) const;
            std::map<std::string, std::string> getChannelInfo(const size_t channel,
                                                const Direction direction) const;
            const std::vector<std::string> getStreamFormats(const size_t channel,
                                            const Direction direction) const;
            std::tuple<std::string, float> getNativeStreamFormat(
                const size_t channel, const Direction direction) const;
        private:
            SoapySDR::Device* _device;
            std::map<std::string, std::string> _kwargs;
    };
}
