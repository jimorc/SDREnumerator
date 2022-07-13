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
            enum class ArgType
            {
                BOOL = SoapySDR::ArgInfo::BOOL,
                INT = SoapySDR::ArgInfo::INT,
                FLOAT = SoapySDR::ArgInfo::FLOAT,
                STRING = SoapySDR::ArgInfo::STRING
            };
            SDRArgInfo(const SoapySDR::ArgInfo& info);
            std::string key();
            std::string value();
            std::string name();
            std::string description();
            std::string units();
            ArgType type();
            SDRRange range();
            std::vector<std::string> options();
            std::vector<std::string> optionNames();
        private:
            std::map<std::string, std::variant<std::string, ArgType,
                SDR::SDRRange, std::vector<std::string>>> _values;
    };
}