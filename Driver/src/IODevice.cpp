#include "IODevice.h"
#include "IOPinState.h"
#include "LogMgr.h"

#include <iostream>

using namespace std;
// ****************************************************************************
//
// ****************************************************************************
IODevice::IODevice(const char* aName, int aPinCount) :
  mName(aName),
  mPinCount(aPinCount)
{
  mLogMgr = LogMgr::get_instance();
  mLogMgr->Trace("IODevice(%s)::IODevice - start\n", mName);
  mLogMgr->Trace("IODevice(%s)::IODevice - end\n", mName);
}

// ****************************************************************************
//
// ****************************************************************************
IODevice::~IODevice()
{
  mLogMgr->Trace("IODevice(%s)::~IODevice - start\n", mName);
//  std::Iterator<const char*, IOPinState*> lIter = mPinStateMap.begin();
  mLogMgr->Trace("IODevice(%s)::~IODevice - end\n", mName);
}

// ****************************************************************************
//
// ****************************************************************************
bool IODevice::create_pin_state(const char* aStateName, int aPinCount)
{
  mLogMgr->Trace("IODevice(%s)::create_pin_state - start\n", mName);

  // check to see if state already exits. if so, return false
  if(mPinStateMap.find(aStateName) != mPinStateMap.end())
  {
    mLogMgr->Error("IODevice(%s)::create_pin_state - state already exists - %s\n", mName, aStateName);
    return false;
  }

  IOPinState *lState = new IOPinState(aStateName, aPinCount);
  mPinStateMap.insert(std::pair<const char*, IOPinState*>(lState->get_name(), lState));

  mLogMgr->Trace("IODevice(%s)::create_pin_state - end\n", mName);

  return true;
}

// ****************************************************************************
//
// ****************************************************************************
bool IODevice::set_pin_state(const char* aStateName, int aPinNum, int aPinValue)
{
  mLogMgr->Trace("IODevice(%s)::set_pin_state - start\n", mName);

  // check to see if state already exits. if so, return false
  if(mPinStateMap.find(aStateName) == mPinStateMap.end())
  {
    mLogMgr->Error("IODevice(%s)::set_pin_state - state does not exists - %s\n", mName, aStateName);
    return false;
  }

  IOPinState *lState = mPinStateMap[aStateName];
  lState->set_state(aPinNum, aPinNum);

  mLogMgr->Trace("IODevice(%s)::set_pin_state - end\n", mName);

  return true;
}


