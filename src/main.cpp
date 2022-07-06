#include <iostream>
#include "SoapySDR/Device.hpp"

using namespace SoapySDR;

int main()
{
    std::vector<Kwargs> kList = Device::enumerate();
 
    std::cout << "Number of SDRs = " << kList.size() << '\n'; 
    for(auto& kwargs : kList)
    {
        for(const auto& [key, _] : kwargs)
        {
            std::cout << key << ": " << kwargs[key] << '\n';
        }
    }
}