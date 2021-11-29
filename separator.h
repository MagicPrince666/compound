#pragma once

#define UBOOT_ADDR 0x0
#define UBOOT_SIZE 0x30000

#define UBOOT_ENV_ADDR 0x30000
#define UBOOT_ENV_SIZE 0x10000

#define FACTORY_ADDR 0x40000
#define FACTORY_SIZE 0x10000

#define FIRMWARE_ADDR 0x50000
//#define FIRMWARE_SIZE 0xfb0000
//#define FIRMWARE_SIZE 0x172a04
#define FIRMWARE_SIZE 0x492430

#define MSG1_ADDR 0x4E0000
#define MSG1_SIZE 0x2430 // 0x4E2430 - 0x4E0000

#define KERNEL_ADDR 0x50000
#define KERNEL_SIZE 0xc38ed

#define ROOTFS_ADDR (KERNEL_ADDR + KERNEL_SIZE)
#define ROOTFS_SIZE 0xeec713

class Separator
{
public:
    Separator(std::string image_file);
    ~Separator();

    bool Start();

private:
    bool OutputFile(std::ifstream &infile, std::ofstream &outfile, uint32_t addr, uint32_t size);
    bool IsPathExist(const std::string &path);
    bool IsFile(const std::string &path);
    bool IsFolder(const std::string &path);

    std::ifstream image_;
    std::ofstream uboot_;
    std::ofstream uboot_env_;
    std::ofstream factory_;
    std::ofstream firmware_;
    std::ofstream kernel_;
    std::ofstream rootfs_;
    std::ofstream rootfs_data_;
    std::ofstream msg1_;
};
