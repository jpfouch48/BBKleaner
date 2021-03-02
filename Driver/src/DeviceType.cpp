#include "DeviceType.h"

// ****************************************************************************
//
// ****************************************************************************
DeviceType::DeviceType(std::string aName) : 
  mName(aName),
  mLogMgr("DeviceType")
{
  mPinStates.clear();
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
  // Verify that this is a unique pin state
  if(0 != mPinStates.count(aStateName))
  {
    mLogMgr.Error("create_pin_state() - state (%s) already exists\n", 
      aStateName.c_str());
    return false;
  }

  mLogMgr.Info("add_pin_state() - state (%s) added\n", 
    aStateName.c_str());

  mPinStates.insert(PinStatePair_t(aStateName, PinArray_t()));

  return true;
}

// ****************************************************************************
//
// ****************************************************************************
bool DeviceType::add_pin_state(std::string aStateName, int aState)
{
  // Verify that the state exists
  if(0 == mPinStates.count(aStateName))
  {
    mLogMgr.Error("add_pin_state() - state (%s) does not exists\n", 
      aStateName.c_str());
    return false;
  }

  mLogMgr.Info("add_pin_state() - state (%s) added %d\n", 
    aStateName.c_str(), aState);

  mPinStates[aStateName].push_back(aState);
 
  return true;
}

// ****************************************************************************
//
// ****************************************************************************
bool DeviceType::parse_json(const json &aCfg)
{
  if(false == aCfg.contains("num pins"))
  {
    mLogMgr.Error("parse_json(%s) - 'num pins' not found\n", mName.c_str());
    return false;
  }
  set_num_pins(aCfg["num pins"]);

  if(false == aCfg.contains("pin states"))
  {
    mLogMgr.Error("parse_json(%s) - 'pin states' not found\n", mName.c_str());
    return false;
  }

  for(auto &lDeviceTypeState : aCfg["pin states"].items())
  {
    mLogMgr.Info("parse_json(%s) - parsing state %s\n", 
      mName.c_str(),
      lDeviceTypeState.key().c_str());

    if(false == create_pin_state(lDeviceTypeState.key()))
    {
      mLogMgr.Error("parse_json(%s) - error create_pin_state %s\n", 
        mName.c_str(),
        lDeviceTypeState.key().c_str());
      return false;
    }

    if(lDeviceTypeState.value().size() != get_num_pins())
    {
      mLogMgr.Error("parse_json(%s) - state %s - invalid pin count %d\n", 
        mName.c_str(),
        lDeviceTypeState.key().c_str(),
        lDeviceTypeState.value().size());
      return false;
    }

    for(auto &lPinValue : lDeviceTypeState.value().items())
    {
      add_pin_state(lDeviceTypeState.key(), lPinValue.value().get<int>());
    }
  }

  return true;
}

