#include <iostream>
#include <fstream>
#include <string>
#include <sys/stat.h>

#include "synthetic.h"
#include "interface.h"

Synthetic::Synthetic(std::string image_file, std::string uboot_file, std::string firmware_file)
{
    struct stat buffer;   
    if(stat(image_file.c_str(), &buffer) == 0) {
        std::cout << RED <<"Remove " << image_file <<" Image file\n";
        remove(image_file.c_str());
    }
    std::cout << GREEN <<"Start Synthetic Image " << image_file <<"\n";

    image_.open(image_file, std::ios::out | std::ios::binary);
    uboot_.open(uboot_file, std::ios::in | std::ios::binary);
    firmware_.open(firmware_file, std::ios::in | std::ios::binary);

    Start();
}

Synthetic::Synthetic(std::string image_file, std::string uboot_file, std::string kernel_file, std::string rootfs_file)
{
    struct stat buffer;
    if(stat(image_file.c_str(), &buffer) == 0) {
        std::cout << RED <<"Remove " << image_file <<" Image file\n";
        remove(image_file.c_str());
    }
    std::cout << GREEN <<"Start Synthetic Image " << image_file <<"\n";

    image_.open(image_file, std::ios::out | std::ios::binary);
    uboot_.open(uboot_file, std::ios::in | std::ios::binary);
    kernel_.open(kernel_file, std::ios::in | std::ios::binary);
    rootfs_.open(rootfs_file, std::ios::in | std::ios::binary);

    Start_UKR();
}

bool Synthetic::Start()
{
    if (!image_.is_open()) {
        std::cout << RED <<"Image is not open\n";
        return false;
    }
    if (!uboot_.is_open()) {
        std::cout << RED <<"Uboot is not open\n";
        return false;
    }
    if (!firmware_.is_open()) {
        std::cout << RED <<"Firmware is not open\n";
        return false;
    }

    int size = 0x50000;
    char *buff = new char[size]();

    uboot_.seekg(0, std::ios::end);    // go to the end
    int length = uboot_.tellg();
    uboot_.seekg(0, std::ios::beg);
    uboot_.read(buff, length);

    image_.write(buff, size);
    delete[] buff;
    std::cout << GREEN <<"Write uboot done\n";

    image_ << firmware_.rdbuf();

    return true;
}

bool Synthetic::Start_UKR()
{
    if (!image_.is_open()) {
        std::cout << RED <<"Image is not open\n";
        return false;
    }
    if (!uboot_.is_open()) {
        std::cout << RED <<"Uboot is not open\n";
        return false;
    }
    if (!kernel_.is_open()) {
        std::cout << RED <<"Kernel is not open\n";
        return false;
    }
    if (!rootfs_.is_open()) {
        std::cout << RED <<"Rootfs is not open\n";
        return false;
    }

    int size = 0x50000;
    char *buff = new char[size]();

    uboot_.seekg(0, std::ios::end);    // go to the end
    int length = uboot_.tellg();
    uboot_.seekg(0, std::ios::beg);
    uboot_.read(buff, length);
    
    image_.write(buff, size);
    delete[] buff;
    std::cout << GREEN <<"Write uboot done\n";

    image_ << kernel_.rdbuf();
    image_ << rootfs_.rdbuf();

    return true;
}

Synthetic::~Synthetic()
{
    if (uboot_.is_open()) {
        uboot_.close();
        std::cout << GREEN <<"Read uboot done\n";
    }

    if (kernel_.is_open()) {
        kernel_.close();
        std::cout << GREEN <<"Write Kernel done\n";
    }

    if (rootfs_.is_open()) {
        rootfs_.close();
        std::cout << GREEN <<"Write rootfs done\n";
    }

    if (firmware_.is_open()) {
        firmware_.close();
        std::cout << GREEN <<"Write firmware done\n";
    }

    if (image_.is_open()) {
        image_.close();
        std::cout << GREEN <<"Close image done\n";
    }
}
