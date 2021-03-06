#include "Driver.h"
#include "Kleaner.h"

#include "LogMgr.h"
#include "CfgMgr.h"
#include "GPIOMgr.h"

#include <iostream>

using namespace std;

int main(int aArgc, char **aArgv)
{
    if(aArgc != 2)
    {
        std::cout << "Usage: " << aArgv[0] << " [cfgfilename]" << std::endl;
        return -1;
    }

    // Create Singleton instances before starting
    GPIOMgr::create_instance();
    LogMgr::create_instance();
    CfgMgr::create_instance(aArgv[1]);    

    Kleaner lKleaner;
    lKleaner.setup();
    lKleaner.run();
    return 0;
}