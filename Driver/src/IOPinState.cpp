#include "IOPinState.h"

#include <iostream>


// ****************************************************************************
//
// ****************************************************************************
IOPinState::IOPinState(const char *aName, int aPinCount) :
  mName(aName),
  mPinCount(aPinCount),
  mLogMgr("IOPinState")
{  
  mLogMgr.Trace("(%s)::IOPinState - start\n", mName);
  mLogMgr.Trace("(%s)::IOPinState - end\n", mName);
}
 
// ****************************************************************************
//
// ****************************************************************************
IOPinState::~IOPinState()
{
  mLogMgr.Trace("(%s)::~IOPinState - start\n", mName);
  mLogMgr.Trace("(%s)::~IOPinState - end\n", mName);
}

// ****************************************************************************
//
// ****************************************************************************
bool IOPinState::set_state(int aPin, int aValue)
{
  mLogMgr.Trace("(%s)::set_state - start\n", mName);

  if(mPinState.find(aPin) != mPinState.end())
  {
    mLogMgr.Error("(%s)::set_state - pin already set - %d\n", mName, aPin);
    return false;
  }

  mPinState.insert(std::pair<int, int>(aPin, aValue));

  mLogMgr.Trace("(%s)::set_state - end\n", mName);
  return true;
}

// ****************************************************************************
//
// ****************************************************************************
int IOPinState::get_state(int aPin)
{
  mLogMgr.Trace("(%s)::get_state - start\n", mName);

  if(mPinState.find(aPin) == mPinState.end())
  {
    mLogMgr.Error("(%s)::get_state state invalid pin : %d - end \n", mName, -1);
  
    return -1;
  }

  mLogMgr.Trace("(%s)::get_state state:%d - end \n", mName, mPinState[aPin]);

  return mPinState[aPin];
}