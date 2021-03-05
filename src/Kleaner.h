#pragma once

#include "LogInstance.h"

// Forward declaration
class CfgMgr;

class Kleaner
{
public:
  Kleaner();
  ~Kleaner();

  bool setup();
  bool run();
  bool shutdown();

protected:

private:
  LogInstance mLogMgr;
  CfgMgr *mCfgMgr;
  bool mRunning;
};