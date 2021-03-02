#pragma once

#include <map>

#include <nlohmann/json.hpp>
using json = nlohmann::json;

class LogMgr;
class DeviceType;

class CfgMgr
{
public:
  static CfgMgr *create_instance(const char* aCfgFileName);
  static CfgMgr *get_instance();
  
  ~CfgMgr() { }


  bool parse_config();

protected:


private:
  CfgMgr(const char* aCfgFileName);
  bool parse_device_types();

  json mJson;
  LogMgr *mLogMgr;
  const char *mCfgFileName;
  static CfgMgr *gInstance;

  using DeviceTypeMap_t = std::map<std::string, DeviceType*>;
  using DeviceTypePair_t = std::pair<std::string, DeviceType*>;
  DeviceTypeMap_t mDeviceTypes;
};