#pragma once

#include <string>
#include <map>
#include <array>

#include <nlohmann/json.hpp>
using json = nlohmann::json;

class LogMgr;

class DeviceType
{
public:
  static const int MAX_PINS = 4;
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
  LogMgr *mLogMgr;
  using PinStateMap_t = std::map<std::string, std::array<int, MAX_PINS>>;
  using PinStatePair_t = std::pair<std::string, std::array<int, MAX_PINS>>;
  PinStateMap_t mPinStates;
};