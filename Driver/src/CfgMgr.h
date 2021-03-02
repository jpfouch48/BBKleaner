#pragma once

#include "LogInstance.h"
#include <map>

#include <nlohmann/json.hpp>
using json = nlohmann::json;

class DeviceType;
class Device;

class CfgMgr
{
public:
  static CfgMgr *create_instance(const char* aCfgFileName);
  static CfgMgr *get_instance();
  
  ~CfgMgr() { }


  bool parse_config();

  const DeviceType * get_device_type(std::string aDeviceTypeName);
  const Device * get_device(std::string aDeviceName);

protected:


private:
  CfgMgr(const char* aCfgFileName);

  bool parse_device_types();
  bool parse_devices();

  using DeviceTypeMap_t = std::map<std::string, DeviceType*>;
  using DeviceTypePair_t = std::pair<std::string, DeviceType*>;
  DeviceTypeMap_t mDeviceTypes;

  using DeviceMap_t = std::map<std::string, Device*>;
  using DevicePair_t = std::pair<std::string, Device*>;
  DeviceMap_t mDevices;

  json mJson;
  const char *mCfgFileName;
  static CfgMgr *gInstance;
  LogInstance mLogMgr;
};