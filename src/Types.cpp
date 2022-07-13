#include "../include/Types.h"

namespace SDR
{
    SDRRange::SDRRange(const SoapySDR::Range& range)
        : _minimum(range.minimum()), _maximum(range.maximum()), _step(range.step()) {}

    double SDRRange::minimum() const
    {
        return _minimum;
    }

    double SDRRange::maximum() const
    {
        return _maximum;
    }

    double SDRRange::step() const
    {
        return _step;
    }

    SDRArgInfo::SDRArgInfo(const SoapySDR::ArgInfo& info)
    {
        _values["key"] = info.key;
        _values["value"] = info.value;
        _values["name"] = info.name;
        _values["description"] = info.description;
        _values["units"] = info.units;
        _values["type"] = info.type;
        _values["range"] = info.range;
        _values["options"] = info.options;
        _values["optionNames"] = info.optionNames;
    }
  
    std::string SDRArgInfo::key()
    {
        return std::get<std::string>(_values["key"]);
    }

    std::string SDRArgInfo::value()
    {
        return std::get<std::string>(_values["value"]);
    }
            
    std::string SDRArgInfo::name()
    {
        return std::get<std::string>(_values["name"]);
    }
    
    std::string SDRArgInfo::description()
    {
        return std::get<std::string>(_values["description"]);
    }
   
    std::string SDRArgInfo::units()
    {
        return std::get<std::string>(_values["units"]);
    }

    SoapySDR::ArgInfo::Type SDRArgInfo::type()
    {
        return std::get<SoapySDR::ArgInfo::Type>(_values["type"]);
    }
    
    SDR::SDRRange SDRArgInfo::range()
    {
        return std::get<SDR::SDRRange>(_values["range"]);
    }
    
    std::vector<std::string> SDRArgInfo::options()
    {
        return std::get<std::vector<std::string>>(_values["options"]);
    }
    
    std::vector<std::string> SDRArgInfo::optionNames()
    {
        return std::get<std::vector<std::string>>(_values["optionNames"]);
    }
 }