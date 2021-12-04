#include <iostream>
#include <fstream>
#include <string>
#include <sys/stat.h>

#include "analyze_bin.h"
#include "interface.h"

AnalyzeBin::AnalyzeBin(std::string binary_file) 
{
    struct stat buffer;
    if(stat(binary_file.c_str(), &buffer) != 0) {
        std::cout << RED <<"No " << binary_file <<" binary file\n";
        exit(0);
    }
    std::cout << GREEN <<"Start Analyze binary " << binary_file <<"\n";

    binary_.open(binary_file, std::ios::in | std::ios::binary);
    Start();
}

AnalyzeBin::~AnalyzeBin() 
{
     if (binary_.is_open()) {
        binary_.close();
        std::cout << GREEN <<"Read uboot done\n";
    }
}

bool AnalyzeBin::Start()
{
    if (!binary_.is_open()) {
        std::cout << RED <<"binary is not open\n";
        return false;
    }

    binary_.seekg(0, std::ios::end);    // go to the end
    int length = binary_.tellg();
    char *buff = new char[length]();

    binary_.seekg(0, std::ios::beg);
    binary_.read(buff, length);

    uint32_t *end = nullptr;
    for(int i = 0; i < length; i++) {
        printf("%02x ", buff[i]);
        end = (uint32_t*)(buff + i);
        if(*end == 0x6b726f77) {
            printf("\n");
        }
    }

    delete[] buff;

    return true;
}