# SDREnumerator
A program to enumerate the properties of Software Defined Radios

# How to Build
This program is built using CMake and a C++ compiler.

At the moment, it is being developed on MacOS, so those are the only build
instructions that I will provide for now. You can try similar instructions on
other OSes.

## Building on MacOS
To build this application on MacOS, do the following:
1. Install Xcode and the Xcode command line utilities.
1. Install the required libraries using Homebrew or MacPorts. Some libraries are only available on MacPorts. Because I only have an RTL-SDR dongle,
   that is the only library I installed:

   > % sudo port install SoapyRTLSDR

   Homebrew and MacPorts will install all libraries that SoapyRTLSDR depends on, including SoapySDR.
1. Now download and build SDREnumerator
   > % cd _\<your projects folder\>_
   >
   > % git clone https://github.com/jimorc/SDREnumerator.git
   >
   > % cd SDREnumerator
   >
   > % mkdir build
   >
   > % cd build
   >
   > % cmake ..
   >
   > % make
   
   If you are using an IDE, then modify the _cmake_ line to generate the project files
    for that IDE. If you are using an IDE, then the _make_ line is probably not needed.