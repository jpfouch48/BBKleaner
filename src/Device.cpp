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
  mDeviceType = lDeviceType;

  if(false == aCfg.contains("pins"))
  {
    mLogMgr.Error("parse_json(%s) - 'pins' not found\n", mName.c_str());
    return false;
  }

  // Add Pins
  for(auto &lPin : aCfg["pins"].items())
  {
    mLogMgr.Info("parse_json(%s) - added pin '%s'\n", mName.c_str(), lPin.value().get<std::string>().c_str());
    mPins.push_back(lPin.value());
  }

  if(mPins.size() != mDeviceType->get_num_pins())
  {
    mLogMgr.Error("parse_json(%s) - pin count mismatch\n", mName.c_str());
    return false;
  }

  return true;
}

// ****************************************************************************
//
// ****************************************************************************
std::string Device::toString() const
{
  std::ostringstream lStr;
  lStr << "Device: " << get_name() << std::endl;
  lStr << get_device_type()->toString();
  lStr << "Pins: [";  
  for(auto lPin : get_pins())
  {
    lStr << " '" << lPin << "'" ;
  }
  lStr << " ]" << std::endl;
  return lStr.str();  
}
