#include "Kleaner.h"
#include "IODevice.h"
#include "IOPinState.h"
#include "LogMgr.h"
#include "CfgMgr.h"

#include <iostream>
#include <unistd.h>

// ****************************************************************************
//
// ****************************************************************************
Kleaner::Kleaner(const char *aCfgFileName) :
//  mIOCo2(NULL),
//  mIOPump(NULL),
//  mIOInputWater(NULL),
//  mIOInputSanitizer(NULL),
//  mIOInputCleaner(NULL),
//  mIOOutputWaste(NULL),
//  mIOOutputSanitizer(NULL),
//  mIOOutputCleaner(NULL),
  mLogMgr(NULL),
  mCfgMgr(NULL),
  mRunning(true)
{
  mLogMgr = LogMgr::create_instance();
  mCfgMgr = CfgMgr::create_instance(aCfgFileName);
  mLogMgr->Trace("Kleaner::Kleaner - start\n");
  mLogMgr->Trace("Kleaner::Kleaner - end\n");
}

// ****************************************************************************
//
// ****************************************************************************
Kleaner::~Kleaner()
{  
  mLogMgr->Trace("Kleaner::~Kleaner - start\n");
//  if(NULL != mIOCo2)             delete mIOCo2;
//  if(NULL != mIOPump)            delete mIOPump;
//  if(NULL != mIOInputWater)      delete mIOInputWater;
//  if(NULL != mIOInputSanitizer)  delete mIOInputSanitizer;
//  if(NULL != mIOInputCleaner)    delete mIOInputCleaner;
//  if(NULL != mIOOutputWaste)     delete mIOOutputWaste;
//  if(NULL != mIOOutputSanitizer) delete mIOOutputSanitizer;
//  if(NULL != mIOOutputCleaner)   delete mIOOutputCleaner;
  mLogMgr->Trace("Kleaner::~Kleaner - end\n");
}

// ****************************************************************************
//
// ****************************************************************************
bool Kleaner::setup()
{
  mLogMgr->Trace("Kleaner::setup - start\n");


  mCfgMgr->parse_config();


//  mIOCo2 = new IODevice("Co2", 1);
//  mIOCo2->create_pin_state("off", 1);
//  mIOCo2->set_pin_state("off", 10, 0);
//  mIOCo2->create_pin_state("on", 1);
//  mIOCo2->set_pin_state("on", 10, 1);

//  mIOPump = new IODevice("Pump", 1);
//  mIOPump->create_pin_state("off", 1);
//  mIOPump->set_pin_state("off", 11, 0);
//  mIOPump->create_pin_state("on", 1);
//  mIOPump->set_pin_state("on", 11, 1);

//  mIOInputWater = new IODevice("InWater", 2);
//  mIOInputWater->create_pin_state("open", 2);
//  mIOInputWater->set_pin_state("open", 12, 1);
//  mIOInputWater->set_pin_state("open", 13, 0);
//  mIOInputWater->create_pin_state("close", 2);
//  mIOInputWater->set_pin_state("close", 12, 0);
//  mIOInputWater->set_pin_state("close", 13, 1);
//  mIOInputWater->create_pin_state("idle", 2);
//  mIOInputWater->set_pin_state("idle", 12, 0);
//  mIOInputWater->set_pin_state("idle", 13, 0);

//  mIOInputSanitizer  = new IODevice("InSanitizer", 2);
//  mIOInputSanitizer->create_pin_state("open", 2);
//  mIOInputSanitizer->set_pin_state("open", 14, 1);
//  mIOInputSanitizer->set_pin_state("open", 15, 0);
//  mIOInputSanitizer->create_pin_state("close", 2);
//  mIOInputSanitizer->set_pin_state("close", 14, 0);
//  mIOInputSanitizer->set_pin_state("close", 15, 1);
//  mIOInputSanitizer->create_pin_state("idle", 2);
//  mIOInputSanitizer->set_pin_state("idle", 14, 0);
//  mIOInputSanitizer->set_pin_state("idle", 15, 0);

//  mIOInputCleaner    = new IODevice("InCleaner", 2);
//  mIOInputCleaner->create_pin_state("open", 2);
//  mIOInputCleaner->set_pin_state("open", 16, 1);
//  mIOInputCleaner->set_pin_state("open", 17, 0);
//  mIOInputCleaner->create_pin_state("close", 2);
//  mIOInputCleaner->set_pin_state("close", 16, 0);
//  mIOInputCleaner->set_pin_state("close", 17, 1);
//  mIOInputCleaner->create_pin_state("idle", 2);
//  mIOInputCleaner->set_pin_state("idle", 16, 0);
//  mIOInputCleaner->set_pin_state("idle", 17, 0);

//  mIOOutputWaste     = new IODevice("OutWaste", 2);
//  mIOOutputWaste->create_pin_state("open", 2);
//  mIOOutputWaste->set_pin_state("open", 18, 1);
//  mIOOutputWaste->set_pin_state("open", 19, 0);
//  mIOOutputWaste->create_pin_state("close", 2);
//  mIOOutputWaste->set_pin_state("close", 18, 0);
//  mIOOutputWaste->set_pin_state("close", 19, 1);
//  mIOOutputWaste->create_pin_state("idle", 2);
//  mIOOutputWaste->set_pin_state("idle", 18, 0);
//  mIOOutputWaste->set_pin_state("idle", 19, 0);

//  mIOOutputSanitizer = new IODevice("OutSanitizer", 2);
//  mIOOutputSanitizer->create_pin_state("open", 2);
//  mIOOutputSanitizer->set_pin_state("open", 20, 1);
//  mIOOutputSanitizer->set_pin_state("open", 21, 0);
//  mIOOutputSanitizer->create_pin_state("close", 2);
//  mIOOutputSanitizer->set_pin_state("close", 20, 0);
//  mIOOutputSanitizer->set_pin_state("close", 21, 1);
//  mIOOutputSanitizer->create_pin_state("idle", 2);
//  mIOOutputSanitizer->set_pin_state("idle", 20, 0);
//  mIOOutputSanitizer->set_pin_state("idle", 21, 0);

//  mIOOutputCleaner   = new IODevice("OutCleaner", 2);
//  mIOOutputCleaner->create_pin_state("open", 2);
//  mIOOutputCleaner->set_pin_state("open", 22, 1);
//  mIOOutputCleaner->set_pin_state("open", 23, 0);
//  mIOOutputCleaner->create_pin_state("close", 2);
//  mIOOutputCleaner->set_pin_state("close", 22, 0);
//  mIOOutputCleaner->set_pin_state("close", 23, 1);
//  mIOOutputCleaner->create_pin_state("idle", 2);
//  mIOOutputCleaner->set_pin_state("idle", 22, 0);
//  mIOOutputCleaner->set_pin_state("idle", 23, 0);

  mLogMgr->Trace("Kleaner::setup - end\n");
  return true;
}

// ****************************************************************************
//
// ****************************************************************************
bool Kleaner::run()
{
  mLogMgr->Trace("Kleaner::run - start\n");

  while(mRunning)
  {
    usleep(5000);
  }

  mLogMgr->Trace("Kleaner::run - end\n");
  return true;
}

// ****************************************************************************
//
// ****************************************************************************
bool Kleaner::shutdown()
{
  mLogMgr->Trace("Kleaner::shutdown - start\n");

//  if(NULL != mIOCo2)             delete mIOCo2;
//  if(NULL != mIOPump)            delete mIOPump;
//  if(NULL != mIOInputWater)      delete mIOInputWater;
//  if(NULL != mIOInputSanitizer)  delete mIOInputSanitizer;
//  if(NULL != mIOInputCleaner)    delete mIOInputCleaner;
//  if(NULL != mIOOutputWaste)     delete mIOOutputWaste;
//  if(NULL != mIOOutputSanitizer) delete mIOOutputSanitizer;
//  if(NULL != mIOOutputCleaner)   delete mIOOutputCleaner;

  mLogMgr->Trace("Kleaner::shutdown - end\n");

  // TODO: CLEANUP LogMgr

  return true;
}

