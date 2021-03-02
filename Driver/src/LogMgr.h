#pragma once

#include <iostream>
#include <queue>
#include <string>

class LogMgr
{
public:
  class LogMsg
  {
  public:
    enum LogLevel
    {
      Off = 0,
      Trace,
      Info,
      Warning,
      Error,
      Fatal
    };

    static const int MAX_MSG_SIZE = 1024;

    const char * get_log_level_string()
    {
      switch(mMsgLevel)
      {
        case LogLevel::Off:     return "[Off]   "; break;
        case LogLevel::Trace:   return "[Trace] "; break;
        case LogLevel::Info:    return "[Info]  "; break;
        case LogLevel::Warning: return "[Warn]  "; break;
        case LogLevel::Error:   return "[Error] "; break;
        case LogLevel::Fatal:   return "[Fatal] "; break;
        default:                return "[?????] ";
      }
    }

    LogLevel       mMsgLevel;
    char           mMsg[MAX_MSG_SIZE];
    struct timeval mMsgTime;
    const char    *mClassName;
  private:
  protected:
  };

  static LogMgr *create_instance();
  static LogMgr *get_instance();
  
  ~LogMgr() { }

  void *thread_proc();

  void Log(const char *aClassName, LogMsg::LogLevel aLevel, const char* aFormat, va_list aVaList);

protected:

private:
  LogMgr() : mRunning(true) { }

  std::queue<LogMsg*> mMsgQueue;
  bool mRunning;

  static LogMgr *gInstance;
  static pthread_t gMsgThread;
  static pthread_mutex_t mMsgQueueMutex;
  static pthread_mutex_t mVaArgMutex;
};
