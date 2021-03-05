#pragma once

// ****************************************************************************
//
// ****************************************************************************
#include "LogInstance.h"
#include <string>
#include <ostream>
#include <iomanip>
#include <nlohmann/json.hpp>

// ****************************************************************************
//
// ****************************************************************************
using json = nlohmann::json;

// ****************************************************************************
//
// ****************************************************************************
class DeviceType;

// ****************************************************************************
//
// ****************************************************************************
class Device
{
public:
  Device(std::string aName);
  ~Device();

  bool parse_json(const json &aCfg);
  
  std::string        get_name()        const { return mName; }
  std::vector<int>   get_pins()        const { return mPins; }
  const DeviceType * get_device_type() const { return mDeviceType; }

  std::string toString() const;
protected:

private:
  std::string mName;
  const DeviceType *mDeviceType;
  std::vector<int> mPins;
  LogInstance mLogMgr;  
};
