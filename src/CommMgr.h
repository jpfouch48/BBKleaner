#pragma once

#include <cppcms/application.h>  
#include <cppcms/applications_pool.h>  
#include <cppcms/service.h>  
#include <cppcms/http_response.h>  
#include <iostream>  

class CommMgr : public cppcms::application
{
public:
  CommMgr(cppcms::service &srv) :  cppcms::application(srv)  
  {  
    std::cout << "CommMgr create" << std::endl;
  }  

  virtual void main(std::string url);    
};
