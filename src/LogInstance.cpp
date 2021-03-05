#include "LogInstance.h"
#include "LogMgr.h"
#include <stdarg.h>

pthread_mutex_t LogInstance::mVaArgMutex;


// ****************************************************************************
//
// ****************************************************************************
LogInstance::LogInstance(std::string aClassName) : mClassName(aClassName)
{
  mLogMgr = LogMgr::get_instance();      
  pthread_mutex_init(&mVaArgMutex, NULL);
}

// ****************************************************************************
//
// ****************************************************************************
LogInstance::~LogInstance()
{      
}

// ****************************************************************************
//
// ****************************************************************************
void LogInstance::Trace(const char *aFormat, ...)
{
  pthread_mutex_lock(&mVaArgMutex);
  va_list lVaList;
  va_start(lVaList, aFormat);
  mLogMgr->Log(mClassName.c_str(), LogMgr::LogMsg::LogLevel::Trace, aFormat, lVaList);
  va_end(lVaList);
  pthread_mutex_unlock(&mVaArgMutex); 
}

// ****************************************************************************
//
// ****************************************************************************
void LogInstance::Info(const char *aFormat, ...)
{
  pthread_mutex_lock(&mVaArgMutex);
  va_list lVaList;
  va_start(lVaList, aFormat);
  mLogMgr->Log(mClassName.c_str(), LogMgr::LogMsg::LogLevel::Info, aFormat, lVaList);
  va_end(lVaList);
  pthread_mutex_unlock(&mVaArgMutex); 
}

// ****************************************************************************
//
// ****************************************************************************
void LogInstance::Warning(const char *aFormat, ...)
{
  pthread_mutex_lock(&mVaArgMutex);
  va_list lVaList;
  va_start(lVaList, aFormat);
  mLogMgr->Log(mClassName.c_str(), LogMgr::LogMsg::LogLevel::Warning, aFormat, lVaList);
  va_end(lVaList);
  pthread_mutex_unlock(&mVaArgMutex); 
}

// ****************************************************************************
//
// ****************************************************************************
void LogInstance::Error(const char *aFormat, ...)
{
  pthread_mutex_lock(&mVaArgMutex);
  va_list lVaList;
  va_start(lVaList, aFormat);
  mLogMgr->Log(mClassName.c_str(), LogMgr::LogMsg::LogLevel::Error, aFormat, lVaList);
  va_end(lVaList);
  pthread_mutex_unlock(&mVaArgMutex); 
}

// ****************************************************************************
//
// ****************************************************************************
void LogInstance::Fatal(const char *aFormat, ...)
{
  pthread_mutex_lock(&mVaArgMutex);
  va_list lVaList;
  va_start(lVaList, aFormat);
  mLogMgr->Log(mClassName.c_str(), LogMgr::LogMsg::LogLevel::Fatal, aFormat, lVaList);
  va_end(lVaList);
  pthread_mutex_unlock(&mVaArgMutex); 
}
