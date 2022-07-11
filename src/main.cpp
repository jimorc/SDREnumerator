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
                                   uint indentSpaces)
        {
            std::string indent(indentSpaces, ' ');
           for(const auto& [key, _] : stringMap)
            {
                std::cout << indent << key << ": " << stringMap[key] << '\n';
            }
        }

        static void printStringMapOrNone(std::map<std::string, std::string>& stringMap,
                                   uint indentSpaces)
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

        static void printAllDeviceArguments(SDR::Device& device)
        {
            std::cout << "All Device Arguments:\n";
            SoapySDR::Kwargs kwargs = device;
            Print::printStringMap(kwargs, 4);
        }

        static void printDriverKey(SDR::Device& device)
        {
        const auto driverKey = device.getDriverKey();
        std::cout << "Driver key = " << driverKey << '\n';
        }

        static void printHardwareKey(SDR::Device& device)
        {
            const auto hardwareKey = device.getHardwareKey();
            std::cout << "Hardware key = " << hardwareKey << '\n';
        }

        static void printHardwareInfo(SDR::Device& device)
        {
            auto info = device.getHardwareInfo();
            std::cout << "Hardware Info:\n";
            Print::printStringMap(info, 4);          
        }

        static void printDeviceProperties(SDR::Device& device)
        {
        std::cout << "Tuner: " << device["tuner"] << '\n';

        Print::printAllDeviceArguments(device);
        Print::printDriverKey(device);
        Print::printHardwareKey(device);
        Print::printHardwareInfo(device);

        const auto& rxFrontendMapping = device.getFrontendMapping(SOAPY_SDR_RX);
        
        std::cout << "Frontend RX Mapping = ";
        std::cout << (rxFrontendMapping.empty() ? "none" : rxFrontendMapping) << '\n';

        const auto rxNumChannels = device.getNumberOfRXChannels();
        std::cout << "Number of RX channels = " << rxNumChannels << '\n';
        for(size_t channel = 0; channel < rxNumChannels; ++channel)
        {
            auto channelInfo = device.getRXChannelInfo(channel);
            std::cout << "RX Channel " << channel << " Info: \n";
            Print::printStringMapOrNone(channelInfo, 4); 

            auto rxStreamFormats = device.getRXStreamFormats(channel);
            std::cout << "    RX Stream Formats:\n";
            Print::printStrings(rxStreamFormats, 8);
        }

        const auto& txFrontendMapping = device.getFrontendMapping(SOAPY_SDR_TX);
        
        std::cout << "Frontend TX Mapping = ";
        std::cout << (txFrontendMapping.empty() ? "none" : txFrontendMapping) << '\n';

        const auto txNumChannels = device.getNumberOfTXChannels();
        std::cout << "Number of TX channels = " << txNumChannels << '\n';
        for(size_t channel = 0; channel < txNumChannels; ++channel)
        {
            auto channelInfo = device.getTXChannelInfo(channel);
            std::cout << "TX Channel " << channel << " Info: \n";
            Print::printStringMapOrNone(channelInfo, 8);
            auto txStreamFormats = device.getTXStreamFormats(channel);
            std::cout << "    TX Stream Formats:\n";
            Print::printStrings(txStreamFormats, 8);
        }        }
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