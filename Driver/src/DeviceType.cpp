#include "DeviceType.h"
#include "LogMgr.h"

// ****************************************************************************
//
// ****************************************************************************
DeviceType::DeviceType(std::string aName) : 
  mName(aName)
{
  mPinStates.clear();
  mLogMgr = LogMgr::get_instance();  
}

// ****************************************************************************
//
// ****************************************************************************
DeviceType::~DeviceType()
{

}

// ****************************************************************************
//
// ****************************************************************************
bool DeviceType::create_pin_state(std::string aStateName)
{
  return true;
}

// ****************************************************************************
//
// ****************************************************************************
bool DeviceType::add_pin_state(std::string aStateName, int aState)
{
  return true;
}

// ****************************************************************************
//
// ****************************************************************************
bool DeviceType::parse_json(const json &aCfg)
{
  if(false == aCfg.contains("num pins"))
  {
    mLogMgr->Error("DeviceType::parse_json(%s) - 'num pins' not found\n", mName.c_str());
    return false;
  }
  set_num_pins(aCfg["num pins"]);

  if(false == aCfg.contains("pin states"))
  {
    mLogMgr->Error("DeviceType::parse_json(%s) - 'pin states' not found\n", mName.c_str());
    return false;
  }

  for(auto &lDeviceTypeState : aCfg["pin states"].items())
  {
    mLogMgr->Info("DeviceType::parse_json(%s) - parsing state %s\n", 
      mName.c_str(),
      lDeviceTypeState.key().c_str());

    if(false == create_pin_state(lDeviceTypeState.key()))
    {
      mLogMgr->Error("DeviceType::parse_json(%s) - error create_pin_state %s\n", 
        mName.c_str(),
        lDeviceTypeState.key().c_str());
      return false;
    }

    if(lDeviceTypeState.value().size() != get_num_pins())
    {
      mLogMgr->Error("DeviceType::parse_json(%s) - state %s - invalid pin count %d\n", 
        mName.c_str(),
        lDeviceTypeState.key().c_str(),
        lDeviceTypeState.value().size());
      return false;
    }

    for(auto &lPinValue : lDeviceTypeState.value().items())
    {
      add_pin_state(lDeviceTypeState.key(), lPinValue.value());
    }
  }

  return true;
}

