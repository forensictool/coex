#include "./winLogReader/winLogReader.h"
#include <iostream>

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        std::cout << "NO!" << std::endl;
        return 1;
    }

    winLogReader reader(argv[1], argv[2]);
    reader.~winLogReader();
    return 0;
}
