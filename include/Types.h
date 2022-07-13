#pragma once

#include "SoapySDR/Types.hpp"

namespace SDR
{
    class SDRRange
    {
        public:
            SDRRange(const SoapySDR::Range& range);
            double minimum() const;
            double maximum() const;
            double step() const;
        private:
            double _minimum;
            double _maximum;
            double _step;
    };

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
            SDRRange range();
            std::vector<std::string> options();
            std::vector<std::string> optionNames();
        private:
            std::map<std::string, std::variant<std::string, SoapySDR::ArgInfo::Type,
                SDR::SDRRange, std::vector<std::string>>> _values;
    };
}