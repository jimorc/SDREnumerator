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
    }
}