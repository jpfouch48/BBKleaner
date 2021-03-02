#pragma once

#include "LogInstance.h"

#include <string>
#include <nlohmann/json.hpp>
using json = nlohmann::json;

class DeviceType;

class Device
{
public:
  Device(std::string aName);
  ~Device();

  bool parse_json(const json &aCfg);

protected:

private:
  std::string mName;
  const DeviceType *mDeviceType;
  std::vector<int> mPins;

  LogInstance mLogMgr;  
};