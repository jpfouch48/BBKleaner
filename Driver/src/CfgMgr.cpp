#include "CfgMgr.h"
#include "LogMgr.h"
#include "DeviceType.h"

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


  if(false == parse_device_types())
    return false;


  return true;
}

// ****************************************************************************
//
// ****************************************************************************
bool CfgMgr::parse_device_types()
{
  bool lRc = true;

  // Verify device types exist
  if(false == mJson.contains("device types"))
  {
    mLogMgr->Error("CfgMgr::parse_device_types() - no device types found\n");
    return false;
  }

  // Loop through each device type
  for(auto &lDeviceTypeCfg : mJson["device types"].items())
  {
    mLogMgr->Info("CfgMgr::parse_device_types() - Device Type Config: %s\n\t%s\n", 
      lDeviceTypeCfg.key().c_str(), 
      lDeviceTypeCfg.value().dump().c_str());

    // Verify that this is a unique device type
    if(0 != mDeviceTypes.count(lDeviceTypeCfg.key()))
    {
      mLogMgr->Error("CfgMgr::parse_device_types() - device type (%s) already exists\n", 
        lDeviceTypeCfg.key().c_str());
      return false;
    }

    // Create the device type and parse
    DeviceType *lDeviceType = new DeviceType(lDeviceTypeCfg.key());
    if(false == lDeviceType->parse_json(lDeviceTypeCfg.value()))
    {
      mLogMgr->Error("CfgMgr::parse_device_types() - device type (%s) error parsing\n", 
        lDeviceTypeCfg.key().c_str());
      delete lDeviceType;
      return false;
    }

    // Add devcie type to map
    mDeviceTypes.insert(DeviceTypePair_t(lDeviceTypeCfg.key(), lDeviceType));
    mLogMgr->Info("CfgMgr::validate_config() - added %s\n", lDeviceTypeCfg.key().c_str());
  }
  

  // Verify devices exist
  if(false == mJson.contains("devices"))
  {
    mLogMgr->Error("CfgMgr::validate_config() - no devices found\n");
    return false;
  }


  // Loop through each device
//  for(auto &lDeviceCfg : mJson["devices"].items())
//  {
//    mLogMgr->Info("Device Config: %s\n%s\n", 
//      lDeviceCfg.key().c_str(), 
//      lDeviceCfg.value().dump().c_str());
//  }

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