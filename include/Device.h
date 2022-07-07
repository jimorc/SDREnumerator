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
        private:
            SoapySDR::Device* _device;
    };
}