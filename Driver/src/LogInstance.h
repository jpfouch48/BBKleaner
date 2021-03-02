#pragma once

#include <string>

class LogMgr;

class LogInstance
{
public:
  LogInstance(std::string aClassName);
  ~LogInstance();

  void Trace(const char *aFormat, ...);
  void Info(const char *aFormat, ...);
  void Warning(const char *aFormat, ...);
  void Error(const char *aFormat, ...);
  void Fatal(const char *aFormat, ...);

protected:

private:
  std::string mClassName;
  LogMgr *mLogMgr;
  static pthread_mutex_t mVaArgMutex;
};
