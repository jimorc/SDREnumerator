#pragma once

#include "Device.h"

namespace SDR
{
    class Devices
    {
        public:
            Devices() = delete;
            Devices(const Devices&) = delete;
            Devices(Devices&&) = delete;
            Devices& operator=(const Devices&) = delete;
            Devices&& operator=(Devices&&) = delete;
            static std::vector<SDR::Device> getDevices();
    };
}       
