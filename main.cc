#include <iostream>
#include <fstream>
#include <sys/stat.h>

#include "interface.h"
#include "synthetic.h"
#include "separator.h"

int main(int argc, char* argv[])
{
    if(argc == 5) { // 合成固件
        Synthetic synthetic(argv[1], argv[2], argv[3], argv[4]);
    } else if(argc == 4) { // 合成固件
        Synthetic synthetic(argv[1], argv[2], argv[3]);
    } else if(argc == 2) { // 分离固件
        Separator separator(argv[1]);
    } else {
        std::cout << RED <<"Param Error\n";
    }

    return 0;
}
