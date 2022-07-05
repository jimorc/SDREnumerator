cmake_minimum_required(VERSION 3.22)

project(SDREnumerator
VERSION 0.1
DESCRIPTION "Program to enumerate the functionality of attached Software Defined Radios"
LANGUAGES CXX)

add_executable(SDREnumerator src/main.cpp)

target_compile_features(SDREnumerator PRIVATE cxx_std_20)
    

    