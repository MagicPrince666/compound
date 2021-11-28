#pragma once

#include <fstream>

class Synthetic
{
public:
    Synthetic(std::string image_file, std::string uboot_file, std::string firmware_file);
    ~Synthetic();

    bool Start();

private:
    std::ofstream image_;
    std::ifstream uboot_;
    std::ifstream firmware_;
};
