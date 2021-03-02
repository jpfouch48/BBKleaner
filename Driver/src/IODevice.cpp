#include "IODevice.h"
#include "IOPinState.h"

#include <iostream>

using namespace std;
// ****************************************************************************
//
// ****************************************************************************
IODevice::IODevice(const char* aName, int aPinCount) :
  mName(aName),
  mPinCount(aPinCount),
  mLogMgr("IODevice")
{
  mLogMgr.Trace("(%s)::IODevice - start\n", mName);
  mLogMgr.Trace("(%s)::IODevice - end\n", mName);
}

// ****************************************************************************
//
// ****************************************************************************
IODevice::~IODevice()
{
  mLogMgr.Trace("(%s)::~IODevice - start\n", mName);
//  std::Iterator<const char*, IOPinState*> lIter = mPinStateMap.begin();
  mLogMgr.Trace("(%s)::~IODevice - end\n", mName);
}

// ****************************************************************************
//
// ****************************************************************************
bool IODevice::create_pin_state(const char* aStateName, int aPinCount)
{
  mLogMgr.Trace("(%s)::create_pin_state - start\n", mName);

  // check to see if state already exits. if so, return false
  if(mPinStateMap.find(aStateName) != mPinStateMap.end())
  {
    mLogMgr.Error("(%s)::create_pin_state - state already exists - %s\n", mName, aStateName);
    return false;
  }

  IOPinState *lState = new IOPinState(aStateName, aPinCount);
  mPinStateMap.insert(std::pair<const char*, IOPinState*>(lState->get_name(), lState));

  mLogMgr.Trace("(%s)::create_pin_state - end\n", mName);

  return true;
}

// ****************************************************************************
//
// ****************************************************************************
bool IODevice::set_pin_state(const char* aStateName, int aPinNum, int aPinValue)
{
  mLogMgr.Trace("(%s)::set_pin_state - start\n", mName);

  // check to see if state already exits. if so, return false
  if(mPinStateMap.find(aStateName) == mPinStateMap.end())
  {
    mLogMgr.Error("(%s)::set_pin_state - state does not exists - %s\n", mName, aStateName);
    return false;
  }

  IOPinState *lState = mPinStateMap[aStateName];
  lState->set_state(aPinNum, aPinNum);

  mLogMgr.Trace("(%s)::set_pin_state - end\n", mName);

  return true;
}


