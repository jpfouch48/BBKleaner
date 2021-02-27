#pragma once

#include <map>

class IOPinState;
class LogMgr;

// ****************************************************************************
//
// ****************************************************************************
class IODevice
{
public:
  // **************************************************************************
  //
  // **************************************************************************
  IODevice(const char* aName, int aPinCount);

  // **************************************************************************
  //
  // **************************************************************************
  ~IODevice();

  // **************************************************************************
  //
  // **************************************************************************
  bool create_pin_state(const char* aStateName, int aPinCount);

  // **************************************************************************
  //
  // **************************************************************************
  bool set_pin_state(const char* aStateName, int aPinNum, int aPinValue);

protected:

private:
  const char* mName;
  int mPinCount;
  std::map<const char*, IOPinState*> mPinStateMap;
  LogMgr* mLogMgr;
};