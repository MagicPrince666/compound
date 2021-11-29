#include <iostream>
#include <fstream>
#include <sys/stat.h>
#include <unistd.h>

#include "separator.h"
#include "interface.h"

#define UBOOT_FILE_NAME         "image/uboot.bin"
#define UBOOT_ENV_FILE_NAME     "image/uboot_env.bin"
#define FACTORY_FILE_NAME       "image/factory.bin"
#define FIRMWARE_FILE_NAME      "image/firmware.bin"
#define KERNEL_FILE_NAME        "image/kernel.bin"
#define ROOTFS_FILE_NAME        "image/rootfs.bin"
#define MSG1_FILE_NAME          "image/mag1.bin"

Separator::Separator(std::string image_file)
{
    struct stat buffer;   
    if(stat(image_file.c_str(), &buffer) != 0) {
        std::cout << RED <<"Image file " << image_file <<" not extits\n";
        exit(1);
    }
    std::cout << GREEN <<"Start Separator Image " << image_file <<"\n";

    image_.open(image_file, std::ios::in | std::ios::binary);

    if(!IsPathExist("image"))
    {
        mkdir("image", 0775);
    }
    uboot_.open(UBOOT_FILE_NAME, std::ios::out | std::ios::binary);
    uboot_env_.open(UBOOT_ENV_FILE_NAME, std::ios::out | std::ios::binary);
    factory_.open(FACTORY_FILE_NAME, std::ios::out | std::ios::binary);
    firmware_.open(FIRMWARE_FILE_NAME, std::ios::out | std::ios::binary);
    kernel_.open(KERNEL_FILE_NAME, std::ios::out | std::ios::binary);
    rootfs_.open(ROOTFS_FILE_NAME, std::ios::out | std::ios::binary);
    msg1_.open(MSG1_FILE_NAME, std::ios::out | std::ios::binary);

    Start();
}

Separator::~Separator()
{
    image_.close();
    uboot_.close();
    uboot_env_.close();
    factory_.close();
    firmware_.close();
    msg1_.close();
}

bool Separator::Start()
{
    if (!image_.is_open()) {
        std::cout << RED <<"Image is not open\n";
        return false;
    }
    if (!uboot_.is_open()) {
        std::cout << RED <<"Uboot is not open\n";
        return false;
    }
    OutputFile(image_, uboot_, UBOOT_ADDR, UBOOT_SIZE);

    if (!uboot_env_.is_open()) {
        std::cout << RED <<"Uboot env is not open\n";
        return false;
    }
    OutputFile(image_, uboot_env_, UBOOT_ENV_ADDR, UBOOT_ENV_SIZE);

    if (!factory_.is_open()) {
        std::cout << RED <<"Factory is not open\n";
        return false;
    }
    OutputFile(image_, factory_, FACTORY_ADDR, FACTORY_SIZE);

    if (!firmware_.is_open()) {
        std::cout << RED <<"Firmware is not open\n";
        return false;
    }
    OutputFile(image_, firmware_, FIRMWARE_ADDR, FIRMWARE_SIZE);

    if (!msg1_.is_open()) {
        std::cout << RED <<"unknow message is not open\n";
        return false;
    }
    OutputFile(image_, msg1_, MSG1_ADDR, MSG1_SIZE);

    if (!kernel_.is_open()) {
        std::cout << RED <<"Kernel is not open\n";
        return false;
    }
    OutputFile(image_, kernel_, KERNEL_ADDR, KERNEL_SIZE);

    if (!rootfs_.is_open()) {
        std::cout << RED <<"Rootfs is not open\n";
        return false;
    }
    OutputFile(image_, rootfs_, ROOTFS_ADDR, ROOTFS_SIZE);

    return true;
}

bool Separator::OutputFile(std::ifstream &infile, std::ofstream &outfile, uint32_t addr, uint32_t size)
{
    char *buff = new char[size]();
    infile.seekg(addr, std::ios::beg);
    infile.read(buff, size);
    
    outfile.write(buff, size);
    delete[] buff;
    std::cout << GREEN <<"Write output file done\n";

    return true;
}

// 判断文件是否存在
bool Separator::IsPathExist(const std::string &path) {
    if (access(path.c_str(), 0) == F_OK) {
        return true;
    }
    return false;
}

// 判断路径是否是文件
bool Separator::IsFile(const std::string &path) {
    if (!IsPathExist(path)) {
        printf("%s:%d %s not exist\n", __FILE__, __LINE__, path.c_str());
        return false;
    }
    struct stat buffer;
    return (stat(path.c_str(), &buffer) == 0 && S_ISREG(buffer.st_mode));
}

// 判断路径是否是文件夹
bool Separator::IsFolder(const std::string &path) {
    if (!IsPathExist(path)) {
        return false;
    }
    struct stat buffer;
    return (stat(path.c_str(), &buffer) == 0 && S_ISDIR(buffer.st_mode));
}
