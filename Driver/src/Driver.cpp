#include <iostream>
#include "Kleaner.h"

using namespace std;

int main(int aArgc, char **aArgv)
{
    if(aArgc != 2)
    {
        std::cout << "Usage: " << aArgv[0] << " [cfgfilename]" << std::endl;
        return -1;
    }

    Kleaner lKleaner(aArgv[1]);
    lKleaner.setup();
    lKleaner.run();
    return 0;
}