#include <iostream>
#include <fstream>
#include <sys/stat.h>

#define RESET   "\033[0m"
#define BLACK   "\033[30m"      /* Black */
#define RED     "\033[31m"      /* Red */
#define GREEN   "\033[32m"      /* Green */
#define YELLOW  "\033[33m"      /* Yellow */
#define BLUE    "\033[34m"      /* Blue */
#define MAGENTA "\033[35m"      /* Magenta */
#define CYAN    "\033[36m"      /* Cyan */
#define WHITE   "\033[37m"      /* White */
#define BOLDBLACK   "\033[1m\033[30m"      /* Bold Black */
#define BOLDRED     "\033[1m\033[31m"      /* Bold Red */
#define BOLDGREEN   "\033[1m\033[32m"      /* Bold Green */
#define BOLDYELLOW  "\033[1m\033[33m"      /* Bold Yellow */
#define BOLDBLUE    "\033[1m\033[34m"      /* Bold Blue */
#define BOLDMAGENTA "\033[1m\033[35m"      /* Bold Magenta */
#define BOLDCYAN    "\033[1m\033[36m"      /* Bold Cyan */
#define BOLDWHITE   "\033[1m\033[37m"      /* Bold White */

int main(int argc, char* argv[])
{
    std::ofstream image;
    std::ifstream uboot;
    std::ifstream firmware;

    if(argc >= 3) {
        struct stat buffer;   
        if(stat(argv[1], &buffer) == 0) {
            std::cout << RED <<"Remove " << argv[1] <<" Image file\n";
            remove(argv[1]);
        }
        image.open(argv[1], std::ios::out | std::ios::binary);
        uboot.open(argv[2], std::ios::in | std::ios::binary);
        firmware.open(argv[3], std::ios::in | std::ios::binary);
    } else {
        struct stat buffer;   
        if(stat("mt7628.bin", &buffer) == 0) {
            std::cout << RED <<"Remove " << "mt7628.bin" <<" Image file\n";
            remove("mt7628.bin");
        }
        image.open("mt7628.bin", std::ios::out | std::ios::binary);
        uboot.open("uboot.bin", std::ios::in | std::ios::binary);
        firmware.open("firmware.bin", std::ios::in | std::ios::binary);
    }

    if (!image.is_open()) {
        std::cout << RED <<"Image is not open\n";
        return -1;
    }
    if (!uboot.is_open()) {
        std::cout << RED <<"Uboot is not open\n";
        return -1;
    }
    if (!firmware.is_open()) {
        std::cout << RED <<"Firmware is not open\n";
        return -1;
    }

    char *buffer = new char[192*1024]();//192k

    uboot.seekg(0, std::ios::end);    // go to the end
    int length = uboot.tellg();
    uboot.seekg(0, std::ios::beg);
    uboot.read(buffer, length);
    uboot.close();
    std::cout << GREEN <<"Read uboot done\n";

    image.write(buffer, 192*1024);
    delete[] buffer;
    std::cout << GREEN <<"Write uboot done\n";

    image << firmware.rdbuf();
    firmware.close();
    std::cout << GREEN <<"Write firmware done\n";

    image.close();
    std::cout << GREEN <<"Close image done\n";

    return 0;
}
