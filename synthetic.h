#pragma once

#include <fstream>

class Synthetic
{
public:
    Synthetic(std::string image_file, std::string uboot_file, std::string firmware_file);
    Synthetic(std::string image_file, std::string uboot_file, std::string kernel_file, std::string rootfs_file);
    ~Synthetic();

private:
    bool Start();
    bool Start_UKR();

    std::ofstream image_;
    std::ifstream uboot_;
    std::ifstream kernel_;
    std::ifstream rootfs_;
    std::ifstream firmware_;
};
