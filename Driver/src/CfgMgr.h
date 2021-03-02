#pragma once

#include <nlohmann/json.hpp>
using json = nlohmann::json;

class LogMgr;

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
  bool validate_config();

  json mJson;
  LogMgr *mLogMgr;
  const char *mCfgFileName;
  static CfgMgr *gInstance;
};