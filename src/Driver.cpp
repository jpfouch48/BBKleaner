#include <iostream>
#include "Kleaner.h"

#include "LogMgr.h"
#include "CfgMgr.h"
#include "CommMgr.h"

using namespace std;

int main(int aArgc, char **aArgv)
{
//    try {  
//        std::cout << "creating cppcms::service" << std::endl;
//        cppcms::service srv(aArgc, aArgv);  
//        std::cout << "mounting CommMgr" << std::endl;
//        srv.applications_pool().mount(cppcms::applications_factory<hello>());
//        std::cout << "Running" << std::endl;
//        srv.run();
//        std::cout << "Done Running" << std::endl;
//    }  
//    catch(std::exception const &e) {  
//        std::cerr << e.what() << std::endl;  
//    }
    
    if(aArgc != 2)
    {
        std::cout << "Usage: " << aArgv[0] << " [cfgfilename]" << std::endl;
        return -1;
    }

    // Create Singleton instances before starting
    LogMgr::create_instance();
    CfgMgr::create_instance(aArgv[1]);    

    Kleaner lKleaner;
    lKleaner.setup();
    lKleaner.run();
    return 0;
}