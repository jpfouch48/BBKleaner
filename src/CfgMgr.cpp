#include "CfgMgr.h"
#include "LogMgr.h"
#include "DeviceType.h"
#include "Device.h"

#include <iostream>
#include <fstream>

CfgMgr *CfgMgr::gInstance(NULL);

// ****************************************************************************
//
// ****************************************************************************
CfgMgr::CfgMgr(const char* aCfgFileName) : 
  mCfgFileName(aCfgFileName),
  mLogMgr("CfgMgr")
{
  mDeviceTypes.clear();
  mDeviceTypes.clear();  
}


// ****************************************************************************
//
// ****************************************************************************
const DeviceType * CfgMgr::get_device_type(std::string aDeviceTypeName)
{
  auto lDeviceType = mDeviceTypes.find(aDeviceTypeName);

  if(lDeviceType != mDeviceTypes.end())
    return lDeviceType->second;

  return NULL;
}

// ****************************************************************************
//
// ****************************************************************************
const Device * CfgMgr::get_device(std::string aDeviceName)
{
  auto lDevice = mDevices.find(aDeviceName);

  if(lDevice != mDevices.end())
    return lDevice->second;

  return NULL;
}

// ****************************************************************************
//
// ****************************************************************************
bool CfgMgr::parse_config()
{
  mLogMgr.Trace("parse_config(%s) - start\n", mCfgFileName);
  std::ifstream lStream(mCfgFileName);
  lStream >> mJson;
  mLogMgr.Trace("parse_config - end\n");

  if(false == parse_device_types())
    return false;

  if(false == parse_devices())
    return false;

  return true;
}

// ****************************************************************************
//
// ****************************************************************************
bool CfgMgr::parse_device_types()
{
  // Verify device types exist
  if(false == mJson.contains("device types"))
  {
    mLogMgr.Error("parse_device_types() - no device types found\n");
    return false;
  }

  // Loop through each device type
  for(auto &lDeviceTypeCfg : mJson["device types"].items())
  {
    mLogMgr.Info("parse_device_types() - Device Type Config: %s\n\t%s\n", 
      lDeviceTypeCfg.key().c_str(), 
      lDeviceTypeCfg.value().dump().c_str());

    // Verify that this is a unique device type
    if(0 != mDeviceTypes.count(lDeviceTypeCfg.key()))
    {
      mLogMgr.Error("parse_device_types() - device type (%s) already exists\n", 
        lDeviceTypeCfg.key().c_str());
      return false;
    }

    // Create the device type and parse
    DeviceType *lDeviceType = new DeviceType(lDeviceTypeCfg.key());
    if(false == lDeviceType->parse_json(lDeviceTypeCfg.value()))
    {
      mLogMgr.Error("parse_device_types() - device type (%s) error parsing\n", 
        lDeviceTypeCfg.key().c_str());
      delete lDeviceType;
      return false;
    }

    // Add devcie type to map
    mDeviceTypes.insert(DeviceTypePair_t(lDeviceTypeCfg.key(), lDeviceType));
    mLogMgr.Info("parse_device_types() - added %s\n", lDeviceTypeCfg.key().c_str());
  }
  
  return true;
}

// ****************************************************************************
//
// ****************************************************************************
bool CfgMgr::parse_devices()
{
  // Verify devices exist
  if(false == mJson.contains("devices"))
  {
    mLogMgr.Error("parse_devices() - no devices found\n");
    return false;
  }

  // Loop through each device
  for(auto &lDeviceCfg : mJson["devices"].items())
  {
    mLogMgr.Info("parse_devices() - Device Config: %s\n%s\n", 
      lDeviceCfg.key().c_str(), 
      lDeviceCfg.value().dump().c_str());


    // Verify that this is a unique device
    if(0 != mDevices.count(lDeviceCfg.key()))
    {
      mLogMgr.Error("parse_devices() - device type (%s) already exists\n", 
        lDeviceCfg.key().c_str());
      return false;
    }

    // Create the device type and parse
    Device *lDevice = new Device(lDeviceCfg.key());

    if(false == lDevice->parse_json(lDeviceCfg.value()))
    {
      mLogMgr.Error("parse_devices() - device type (%s) error parsing\n", 
        lDeviceCfg.key().c_str());
      delete lDevice;
      return false;
    }

    // Add devcie type to map
    mDevices.insert(DevicePair_t(lDeviceCfg.key(), lDevice));
    mLogMgr.Info("parse_devices() - added %s\n", lDeviceCfg.key().c_str());    

    mLogMgr.Info("\n%s\n", lDevice->toString().c_str());    
  }

  return true;
}

// ****************************************************************************
//
// ****************************************************************************
CfgMgr *CfgMgr::create_instance(const char* aCfgFileName)
{
//  std::cout << "CfgMgr::create_instance - start" << std::endl;

  if(NULL == gInstance)
  {
    gInstance = new CfgMgr(aCfgFileName);
    return gInstance;
  }

  std::cout << "CfgMgr::create_instance - error - instance already created" << std::endl;
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