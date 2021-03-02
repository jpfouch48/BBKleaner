#pragma once

#include "LogInstance.h"
#include <string>
#include <map>
#include <array>

#include <nlohmann/json.hpp>
using json = nlohmann::json;

class DeviceType
{
public:
  DeviceType(std::string aName);
  ~DeviceType();

  void set_num_pins(int aNumPins) { mNumPins = aNumPins; }
  int  get_num_pins()             { return mNumPins; }

  bool create_pin_state(std::string aStateName);
  bool add_pin_state(std::string aStateName, int aState);

  bool parse_json(const json &aCfg);

protected:

private:
  std::string mName;
  int mNumPins;

  using PinArray_t = std::vector<int>;
  using PinStateMap_t = std::map<std::string, PinArray_t>;
  using PinStatePair_t = std::pair<std::string, PinArray_t>;
  PinStateMap_t mPinStates;

  LogInstance mLogMgr;
};