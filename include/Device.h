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
            Device(Device&&);
            ~Device();
            Device& operator=(const Device&) = delete;
            Device&& operator=(Device&&) = delete;
            operator SoapySDR::Device*() const { return _device; }
            operator SoapySDR::Kwargs() const { return _kwargs; }
            const std::string getDriverKey() const;
            const std::string getHardwareKey() const;
            const SoapySDR::Kwargs getHardwareInfo() const;
            const std::string getRXFrontendMapping() const;
            const std::string getTXFrontendMapping() const;
            size_t getNumberOfRXChannels() const;
            size_t getNumberOfTXChannels() const;
            SoapySDR::Kwargs getRXChannelInfo(size_t channel) const;
            SoapySDR::Kwargs getTXChannelInfo(size_t channel) const;
            const std::vector<std::string> getRXStreamFormats(size_t channel) const;
            const std::vector<std::string> getTXStreamFormats(size_t channel) const;
        private:
            SoapySDR::Device* _device;
            std::map<std::string, std::string> _kwargs;
    };
}
