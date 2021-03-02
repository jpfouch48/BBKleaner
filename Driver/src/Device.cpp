#include "Device.h"
#include "DeviceType.h"
#include "CfgMgr.h"


// ****************************************************************************
//
// ****************************************************************************
Device::Device(std::string aName) :
  mName(aName),
  mLogMgr("Device")
{  
}

// ****************************************************************************
//
// ****************************************************************************
Device::~Device()
{

}

// ****************************************************************************
//
// ****************************************************************************
bool Device::parse_json(const json &aCfg)
{
  CfgMgr *lCfgMgr = CfgMgr::get_instance();

  // "Sanitizer In":  { "type": "ball valve", "pins": [ 14, 15 ] },
  if(false == aCfg.contains("type"))
  {
    mLogMgr.Error("parse_json(%s) - 'type' not found\n", mName.c_str());
    return false;
  }

  const DeviceType *lDeviceType = lCfgMgr->get_device_type(aCfg["type"]);
  if(NULL == lDeviceType)
  {
    mLogMgr.Error("parse_json(%s) - %s not found in configured device types\n", mName.c_str(), aCfg["type"]);
    return false;
  }

  if(false == aCfg.contains("pins"))
  {
    mLogMgr.Error("parse_json(%s) - 'pins' not found\n", mName.c_str());
    return false;
  }

  // Add Pins
  for(auto &lPin : aCfg["pins"].items())
  {
    mLogMgr.Info("parse_json(%s) - added pin %d\n", mName.c_str(), lPin.value().get<int>());
    mPins.push_back(lPin.value().get<int>());
  }

  return true;
}