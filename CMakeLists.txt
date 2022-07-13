cmake_minimum_required(VERSION 3.22)

project(SDREnumerator
VERSION 0.1
DESCRIPTION "Program to enumerate the functionality of attached Software Defined Radios"
LANGUAGES CXX)

find_package(SoapySDR)

add_executable(SDREnumerator src/main.cpp)

target_compile_features(SDREnumerator PRIVATE cxx_std_20)
    
target_include_directories(SDREnumerator PUBLIC ${SoapySDR_SOURCE_DIR}/include)

target_link_libraries(SDREnumerator 
    PRIVATE 
    SoapySDR
    SDR)

add_library(SDR 
    SHARED 
    src/Device.cpp 
    src/Devices.cpp
    src/Types.cpp
    include/Device.h
    include/Devices.h
    include/Enums.h
    include/Types.h
    )

target_compile_features(SDR PRIVATE cxx_std_20)
    
target_include_directories(SDR PUBLIC ${SoapySDR_SOURCE_DIR}/include)

target_link_libraries(SDR 
    PRIVATE 
    SoapySDR)



