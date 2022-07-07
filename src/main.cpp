#include <iostream>
#include "../include/Device.h"

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
};

int main()
{
    std::vector<Kwargs> kList = Device::enumerate();
 
    std::cout << "Number of SDRs = " << kList.size() << '\n'; 
    for(auto& kwargs : kList)
    {
        if(kwargs.find("tuner") != kwargs.end())
        {
            std::cout << "Tuner: " << kwargs["tuner"] << '\n';
        }
        std::cout << "All Device Arguments:\n";
        Print::printStringMap(kwargs, 4);

        SDR::Device dev = SDR::Device(kwargs);
        SoapySDR::Device* device = dev;
        const auto driverKey = dev.getDriverKey();
        std::cout << "Driver key = " << driverKey << '\n';
        const auto hardwareKey = dev.getHardwareKey();
        std::cout << "Hardware key = " << hardwareKey << '\n';
        auto info = dev.getHardwareInfo();
        std::cout << "Hardware Info:\n";
        Print::printStringMap(info, 4);
        const auto& rxFrontendMapping = dev.getRXFrontendMapping();
        
        std::cout << "Frontend RX Mapping = ";
        std::cout << (rxFrontendMapping.empty() ? "none" : rxFrontendMapping) << '\n';

        const auto rxNumChannels = device->getNumChannels(SOAPY_SDR_RX);
        std::cout << "Number of RX channels = " << rxNumChannels << '\n';
        for(size_t channel = 0; channel < rxNumChannels; ++channel)
        {
            auto channelInfo = device->getChannelInfo(SOAPY_SDR_RX, channel);
            std::cout << "RX Channel " << channel << " Info: \n";
            Print::printStringMapOrNone(channelInfo, 4); 

            auto rxStreamFormats = device->getStreamFormats(SOAPY_SDR_RX, channel);
            std::cout << "    RX Stream Formats:\n";
            Print::printStrings(rxStreamFormats, 8);
        }

        const auto& txFrontendMapping = device->getFrontendMapping(SOAPY_SDR_TX);
        
        std::cout << "Frontend TX Mapping = ";
        std::cout << (txFrontendMapping.empty() ? "none" : txFrontendMapping) << '\n';

        const auto txNumChannels = device->getNumChannels(SOAPY_SDR_TX);
        std::cout << "Number of TX channels = " << txNumChannels << '\n';
        for(size_t channel = 0; channel < txNumChannels; ++channel)
        {
            auto channelInfo = device->getChannelInfo(SOAPY_SDR_TX, channel);
            std::cout << "TX Channel " << channel << " Info: \n";
            Print::printStringMapOrNone(channelInfo, 8);
            auto txStreamFormats = device->getStreamFormats(SOAPY_SDR_TX, channel);
            std::cout << "    TX Stream Formats:\n";
            Print::printStrings(txStreamFormats, 8);
        }
    }
}