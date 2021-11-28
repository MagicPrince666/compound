#include <iostream>
#include <fstream>
#include <sys/stat.h>

#include "interface.h"
#include "synthetic.h"
#include "separator.h"

int main(int argc, char* argv[])
{
    if(argc == 2) {
        Separator separator(argv[1]);
    }
    if(argc > 4) {
        Synthetic synthetic(argv[1], argv[2], argv[3]);
    }
    return 0;
}
