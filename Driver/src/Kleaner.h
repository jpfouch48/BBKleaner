#pragma once

// Forward declaration
class IODevice;
class LogMgr;
class CfgMgr;

class Kleaner
{
public:
  Kleaner(const char *aCfgFileName);
  ~Kleaner();

  bool setup();
  bool run();
  bool shutdown();

protected:

private:
//  IODevice *mIOCo2;
//  IODevice *mIOPump;  
//  IODevice *mIOInputWater;
//  IODevice *mIOInputSanitizer;
//  IODevice *mIOInputCleaner;
//  IODevice *mIOOutputWaste;
//  IODevice *mIOOutputSanitizer;
//  IODevice *mIOOutputCleaner; 

  LogMgr *mLogMgr;
  CfgMgr *mCfgMgr;
  bool mRunning;
};