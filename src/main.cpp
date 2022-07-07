#include <iostream>
#include "SoapySDR/Device.hpp"

using namespace SoapySDR;

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
        for(const auto& [key, _] : kwargs)
        {
            std::cout << "    " << key << ": " << kwargs[key] << '\n';
        }

        Device* device = Device::make(kwargs);
        const auto& driverKey = device->getDriverKey();
        std::cout << "Driver key = " << driverKey << '\n';
        const auto& hardwareKey = device->getHardwareKey();
        std::cout << "Hardware key = " << hardwareKey << '\n';
        auto info = device->getHardwareInfo();
        for(const auto& [key, _] : info)
        {
            std::cout << key << ": " << kwargs[key] << '\n';
        }
        const auto& rxFrontendMapping = device->getFrontendMapping(SOAPY_SDR_RX);
        
        std::cout << "Frontend RX Mapping = ";
        std::cout << (rxFrontendMapping.empty() ? "none" : rxFrontendMapping) << '\n';

        const auto rxNumChannels = device->getNumChannels(SOAPY_SDR_RX);
        std::cout << "Number of RX channels = " << rxNumChannels << '\n';
        for(size_t channel = 0; channel < rxNumChannels; ++channel)
        {
            auto channelInfo = device->getChannelInfo(SOAPY_SDR_RX, channel);
            std::cout << "RX Channel " << channel << " Info: \n";
            if(channelInfo.size() == 0)
            {
                std::cout << "    None\n";
            }
            else
            {
                for(auto& [key, _] : channelInfo)
                {
                    std::cout << "    " << key << ": " << channelInfo[key] << '\n';
                }
            }
            auto streamFormats = device->getStreamFormats(SOAPY_SDR_RX, channel);
            std::cout << "    RX Stream Formats:\n";
            if(streamFormats.size() == 0)
            {
                std::cout << "        None\n";
            }
            else
            {
                for(const auto& format : streamFormats)
                {
                    std::cout << "        " << format << '\n';
                } 
            }
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
            if(channelInfo.size() == 0)
            {
                std::cout << "    None\n";
            }
            else
            {
                for(auto& [key, _] : channelInfo)
                {
                    std::cout << "    " << key << ": " << channelInfo[key] << '\n';
                }
            }
            auto txStreamFormats = device->getStreamFormats(SOAPY_SDR_TX, channel);
            std::cout << "    TX Stream Formats:\n";
            if(txStreamFormats.size() == 0)
            {
                std::cout << "        None\n";
            }
            else
            {
                for(const auto& format : txStreamFormats)
                {
                    std::cout << "        " << format << '\n';
                } 
            }
        }

        Device::unmake(device);
    }
}