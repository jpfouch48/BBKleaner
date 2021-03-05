#include "Kleaner.h"
#include "CfgMgr.h"

#include <iostream>
#include <unistd.h>

// ****************************************************************************
//
// ****************************************************************************
Kleaner::Kleaner() :
  mLogMgr("Kleaner"),
  mRunning(true)
{
  mLogMgr.Trace("Kleaner - start\n");
  mCfgMgr = CfgMgr::get_instance();
  mLogMgr.Trace("Kleaner - end\n");
}

// ****************************************************************************
//
// ****************************************************************************
Kleaner::~Kleaner()
{  
  mLogMgr.Trace("~Kleaner - start\n");
  mLogMgr.Trace("~Kleaner - end\n");
}

// ****************************************************************************
//
// ****************************************************************************
bool Kleaner::setup()
{
  mLogMgr.Trace("setup - start\n");
  mCfgMgr->parse_config();
  mLogMgr.Trace(":setup - end\n");
  return true;
}

// ****************************************************************************
//
// ****************************************************************************
bool Kleaner::run()
{
  mLogMgr.Trace("run - start\n");

  while(mRunning)
  {
    usleep(5000);
  }

  mLogMgr.Trace("run - end\n");
  return true;
}

// ****************************************************************************
//
// ****************************************************************************
bool Kleaner::shutdown()
{
  mLogMgr.Trace("shutdown - start\n");

  // TODO: CLEANUP --- E.G LogMgr

  mLogMgr.Trace("shutdown - end\n");
  return true;
}

