#include "CfgMgr.h"
#include "LogMgr.h"
#include <iostream>
#include <fstream>

CfgMgr *CfgMgr::gInstance(NULL);

// ****************************************************************************
//
// ****************************************************************************
CfgMgr::CfgMgr(const char* aCfgFileName) : mCfgFileName(aCfgFileName)
{
  mLogMgr = LogMgr::get_instance();
}


// ****************************************************************************
//
// ****************************************************************************
bool CfgMgr::parse_config()
{
  mLogMgr->Trace("CfgMgr::parse_config - start\n");
  std::ifstream lStream(mCfgFileName);
  lStream >> mJson;

  // TODO: READ IN THE DEVICE TYPES AND STORE THEM
  json lDeviceTypes = mJson["device types"];
  mLogMgr->Info("Device Type:\n%s\n", lDeviceTypes.dump());
  
  // TODO: READ IN THE DEVICES AND STORE THEM
  json lDevices = mJson["devices"];
  mLogMgr->Info("Devices:\n%s\n", lDevices.dump());

  mLogMgr->Trace("CfgMgr::parse_config - end\n");
  return true;
}


// ****************************************************************************
//
// ****************************************************************************
CfgMgr *CfgMgr::create_instance(const char* aCfgFileName)
{
  std::cout << "LogMgr::create_instance - start" << std::endl;

  if(NULL == gInstance)
  {
    gInstance = new CfgMgr(aCfgFileName);
    return gInstance;
  }

  std::cout << "LogMgr::create_instance - error - instance already created" << std::endl;
  // Instance already created, return NULL to indicate ERROR
  return NULL;
}

// ****************************************************************************
//
// ****************************************************************************
CfgMgr *CfgMgr::get_instance()
{ 
//  std::cout << "LogMgr::get_instance - start" << std::endl;
//  std::cout << "LogMgr::get_instance - finished" << std::endl;
  // Return static instance. Note, if instance is not yet created this will
  // return NULL.
  return gInstance;
}