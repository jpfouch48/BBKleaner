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
  mLogMgr->Trace("CfgMgr::parse_config(%s) - start\n", mCfgFileName);
  std::ifstream lStream(mCfgFileName);
  lStream >> mJson;
  mLogMgr->Trace("CfgMgr::parse_config - end\n");
  return validate_config();;
}

// ****************************************************************************
//
// ****************************************************************************
bool CfgMgr::validate_config()
{
  bool lRc = true;

  json lDeviceTypes = mJson["device types"];
  json lDevices = mJson["devices"];

  for(auto &lDeviceType : lDeviceTypes.items())
  {
    mLogMgr->Info("Device Type: %s\n%s\n", lDeviceType.key().c_str(), lDeviceType.value().dump().c_str());
  }
  
  for(auto &lDevice : lDevices.items())
  {
    mLogMgr->Info("Device: %s\n%s\n", lDevice.key().c_str(), lDevice.value().dump().c_str());
  }

  return lRc;
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