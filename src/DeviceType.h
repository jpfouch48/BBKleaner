#pragma once

#include "LogInstance.h"
#include "GPIOConst.h"
#include "GPIOMgr.h"
#include <string>
#include <map>
#include <array>
#include <nlohmann/json.hpp>

// ****************************************************************************
//
// ****************************************************************************
using json = nlohmann::json;
using PinArray_t = std::vector<int>;
using PinStateMap_t = std::map<std::string, PinArray_t>;
using PinStatePair_t = std::pair<std::string, PinArray_t>;

// ****************************************************************************
//
// ****************************************************************************
class DeviceType
{
public:
  DeviceType(std::string aName);
  ~DeviceType();

  void          set_num_pins(int aNumPins)       { mNumPins = aNumPins; }
  int           get_num_pins()             const { return mNumPins; }

  GPIODirection get_direction()                       const { return mDirection; }
  void          set_direction(std::string aDirection)       { mDirection.set(aDirection); }
  
  void          set_state_delay(int aStateDelay) { mStateDelay = aStateDelay; }
  int           get_state_delay()          const { return mStateDelay; }

  std::string   get_name()                 const { return mName; }
  PinStateMap_t get_pin_states()           const { return mPinStates; }

  bool          create_pin_state(std::string aStateName);
  bool          add_pin_state(std::string aStateName, int aState);
  bool          parse_json(const json &aCfg);
  std::string   toString() const;

protected:

private:
  std::string   mName;  
  GPIODirection mDirection;
  int           mNumPins;
  int           mStateDelay;
  PinStateMap_t mPinStates;

  LogInstance   mLogMgr;
};
