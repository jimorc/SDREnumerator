#include <iostream>
#include "../include/Device.h"
#include "../include/Devices.h"

using namespace SoapySDR;

class Print
{
    public:
        static void printStrings(const std::vector<std::string>& strings, 
                            const uint indentSpaces)
        {
            std::string indent(indentSpaces, ' ');
            if(strings.size() == 0)
            {
                std::cout << indent << "None\n";
            }
            else
            {
                for(const auto& format : strings)
                {
                    std::cout << indent << format << '\n';
                } 
            }
        }

        static void printStringMap(std::map<std::string, std::string>& stringMap,
                                   const uint indentSpaces)
        {
            std::string indent(indentSpaces, ' ');
           for(const auto& [key, _] : stringMap)
            {
                std::cout << indent << key << ": " << stringMap[key] << '\n';
            }
        }

        static void printStringMapOrNone(std::map<std::string, std::string>& stringMap,
                                   const uint indentSpaces)
        {
            if(stringMap.size() == 0)
            {
                std::string indent(indentSpaces, ' ');
                std::cout << indent << "None\n";
            }
            else
            {
                printStringMap(stringMap, indentSpaces);
            }
        }

        static void printAllDeviceArguments(const SDR::Device& device)
        {
            std::cout << "All Device Arguments:\n";
            SoapySDR::Kwargs kwargs = device;
            Print::printStringMap(kwargs, 4);
        }

        static void printDriverKey(const SDR::Device& device)
        {
        const auto driverKey = device.getDriverKey();
        std::cout << "Driver key = " << driverKey << '\n';
        }

        static void printHardwareKey(const SDR::Device& device)
        {
            const auto hardwareKey = device.getHardwareKey();
            std::cout << "Hardware key = " << hardwareKey << '\n';
        }

        static void printHardwareInfo(const SDR::Device& device)
        {
            auto info = device.getHardwareInfo();
            std::cout << "Hardware Info:\n";
            Print::printStringMap(info, 4);          
        }

        static void printRXFrontendMapping(const SDR::Device& device)
        {
            const auto& rxFrontendMapping = device.getFrontendMapping(SDR::Direction::RX);
            std::cout << "Frontend RX Mapping = ";
            std::cout << (rxFrontendMapping.empty() ? "none" : rxFrontendMapping) << '\n';
        }

        static void printRXChannelProperties(const SDR::Device& device)
        {
            const auto rxNumChannels = device.getNumberOfChannels(SDR::Direction::RX);
            std::cout << "Number of RX channels = " << rxNumChannels << '\n';
            for(size_t channel = 0; channel < rxNumChannels; ++channel)
            {
                auto channelInfo = device.getChannelInfo(channel, SDR::Direction::RX);
                std::cout << "RX Channel " << channel << " Info: \n";
                Print::printStringMapOrNone(channelInfo, 4); 

                auto rxStreamFormats = device.getStreamFormats(channel, SDR::Direction::RX);
                std::cout << "    RX Stream Formats:\n";
                Print::printStrings(rxStreamFormats, 8);

                auto [format, fullScale] = device.getNativeStreamFormat(channel,
                        SDR::Direction::RX);
                std::cout << "    RX Native Stream Format: ";
                std::cout << (format.empty() ? "none" : format);
                std::cout << ", Full scale value: " << fullScale << '\n';

                Print::printRXStreamArgsInfo(device, channel);
            }
        }

        static void printTXFrontendMapping(const SDR::Device& device)
        {
            const auto& txFrontendMapping = device.getFrontendMapping(SDR::Direction::TX);
            std::cout << "Frontend TX Mapping = ";
            std::cout << (txFrontendMapping.empty() ? "none" : txFrontendMapping) << '\n';
        }

        static void printArgInfoType(SDR::SDRArgInfo& info)
        {
            SDR::SDRArgInfo::ArgType type = info.type();

            std::cout << "        Type: ";
            switch(type)
            {
                case SDR::SDRArgInfo::ArgType::BOOL:
                    std::cout << "bool\n";
                    break;
                case SDR::SDRArgInfo::ArgType::INT:
                    std::cout << "int\n";
                    break;
                case SDR::SDRArgInfo::ArgType::FLOAT:
                    std::cout << "float\n";
                    break;
                case SDR::SDRArgInfo::ArgType::STRING:
                    std::cout << "string\n";
                    break;
                }
        }

        static void printRXStreamArgsInfo(const SDR::Device& device, 
                                          const size_t channel)
        {
            std::vector<SDR::SDRArgInfo> argsInfo = device.getStreamArgsInfo(channel,
                                                SDR::Direction::RX);
            std::cout << "    Stream Args Info for channel " << channel << ":\n";
            for(auto& argInfo : argsInfo)
            {
                Print::printStreamArgsInfo(argInfo);
            }
        }

        static void printStreamArgsInfo(SDR::SDRArgInfo& argInfo)
        {
            std::cout << "        Key: " << argInfo.key() << '\n';
            std::cout << "        Value: " << argInfo.value() << '\n';
            std::cout << "        Name: " << argInfo.name() << '\n';
            std::cout << "        Description: " << argInfo.description() << '\n';
            std::cout << "        Units: " << argInfo.units() << '\n';
            Print::printArgInfoType(argInfo);
            std::cout << "        Range:\n";
            SDR::SDRRange range = argInfo.range();
            std::cout << "            Minimum: " << range.minimum() << '\n';
            std::cout << "            Maximum: " << range.maximum() << '\n';
            std::cout << "            Range: "  << range.step() << '\n';
            std::vector<std::string> options = argInfo.options();
            std::cout << "        Options:\n";
            Print::printStrings(options, 12);
            std::vector<std::string> optionNames = argInfo.optionNames();
            std::cout << "        Option Names:\n";
            Print::printStrings(optionNames, 12);
            std::cout << '\n';
        }
        
        static void printTXStreamArgsInfo(const SDR::Device& device, 
                                          const size_t channel)
        {
            std::vector<SDR::SDRArgInfo> argsInfo = device.getStreamArgsInfo(channel,
                                                SDR::Direction::TX);
            std::cout << "    Stream Args Info for channel " << channel << ":\n";
            for(auto& argInfo : argsInfo)
            {
                Print::printStreamArgsInfo(argInfo);
            }
        }
        
        static void printTXChannelProperties(const SDR::Device& device)
        {
            const auto txNumChannels = device.getNumberOfChannels(SDR::Direction::TX);
            std::cout << "Number of TX channels = " << txNumChannels << '\n';
            for(size_t channel = 0; channel < txNumChannels; ++channel)
            {
                auto channelInfo = device.getChannelInfo(channel, SDR::Direction::TX);
                std::cout << "TX Channel " << channel << " Info: \n";
                Print::printStringMapOrNone(channelInfo, 4); 

                auto txStreamFormats = device.getStreamFormats(channel, SDR::Direction::TX);
                std::cout << "    TX Stream Formats:\n";
                Print::printStrings(txStreamFormats, 8);

                auto [format, fullScale] = device.getNativeStreamFormat(channel,
                        SDR::Direction::TX);
                std::cout << "    TX Native Stream Format: ";
                std::cout << (format.empty() ? "none" : format);
                std::cout << ", Full scale value: " << fullScale << '\n';
             }
        }
        static void printDeviceProperties(const SDR::Device& device)
        {
        std::cout << "Tuner: " << device["tuner"] << '\n';

        Print::printAllDeviceArguments(device);
        Print::printDriverKey(device);
        Print::printHardwareKey(device);
        Print::printHardwareInfo(device);

        Print::printRXFrontendMapping(device);
        Print::printRXChannelProperties(device);
        Print::printTXFrontendMapping(device);
        Print::printTXChannelProperties(device);
    }
};



int main()
{
    std::vector<SDR::Device> devices = SDR::Devices::getDevices();
 
    std::cout << "Number of SDRs = " << devices.size() << '\n'; 

    for(auto& device : devices)
    {
        Print::printDeviceProperties(device);
    }
}