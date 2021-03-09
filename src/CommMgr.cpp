#include "CommMgr.h"


void CommMgr::main(std::string aUrl)  
{  
    std::cout << "CommMgr main " << aUrl << std::endl;
    response().out() <<  
        "<html>\n"  
        "<body>\n"  
        "  <h1>Hello World</h1>\n"  
        "</body>\n"       
        "</html>\n";  
}  
