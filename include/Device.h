#pragma once
#include "SoapySDR/Device.hpp"

namespace SDR
{
    class Device
    {
        public:
            Device() = delete;
            Device(const SoapySDR::Kwargs& kwargs);
            Device(const Device&) = delete;
            Device(Device&&) = delete;
            ~Device();
            Device& operator=(const Device&) = delete;
            Device&& operator=(Device&&) = delete;
            operator SoapySDR::Device*() const { return _device; }
            const std::string getDriverKey() const;
            const std::string getHardwareKey() const;
            const SoapySDR::Kwargs getHardwareInfo() const;
            const std::string getRXFrontendMapping() const;
            size_t getNumberOfRXChannels() const;
            SoapySDR::Kwargs getRXChannelInfo(size_t channel) const;
            const std::vector<std::string> getRXStreamFormats(size_t channel) const;
        private:
            SoapySDR::Device* _device;
    };
}