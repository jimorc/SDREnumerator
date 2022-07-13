#pragma once

#include "SoapySDR/Types.hpp"

namespace SDR
{
    class SDRArgInfo
    {
        public:
            SDRArgInfo(const SoapySDR::ArgInfo& info);
            std::string key();
            std::string value();
            std::string name();
            std::string description();
            std::string units();
            SoapySDR::ArgInfo::Type type();
            SoapySDR::Range range();
            std::vector<std::string> options();
            std::vector<std::string> optionNames();
        private:
            std::map<std::string, std::variant<std::string, SoapySDR::ArgInfo::Type,
                SoapySDR::Range, std::vector<std::string>>> _values;
    };
}