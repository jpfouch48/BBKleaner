#include "LogMgr.h"
#include <stdarg.h>
#include <unistd.h>
#include <assert.h>
#include <sys/time.h>

// ****************************************************************************
// TODO: Make thread safe
// ****************************************************************************

// ****************************************************************************
// Static declarations
// ****************************************************************************
LogMgr    *LogMgr::gInstance(NULL);
pthread_t  LogMgr::gMsgThread;
pthread_mutex_t LogMgr::mMsgQueueMutex;
pthread_mutex_t LogMgr::mVaArgMutex;

// ****************************************************************************
//
// ****************************************************************************
static void *thread_proc_helper(void *aContext)
{  
//  std::cout << "thread_proc_helper - start" << std::endl;
  void *lRc = ((LogMgr*)aContext)->thread_proc();
//  std::cout << "thread_proc_helper - end" << std::endl;
  return lRc;
}

// ****************************************************************************
//
// ****************************************************************************
void LogMgr::Trace(const char *aFormat, ...)
{
  LogMsg *lMsg = new LogMsg();
  gettimeofday(&lMsg->mMsgTime, NULL);
  lMsg->mMsgLevel = LogMsg::LogLevel::Trace;

  pthread_mutex_lock(&mVaArgMutex);
  va_list lVaList;
  va_start(lVaList, aFormat);
  int lRc = vsnprintf(lMsg->mMsg, LogMsg::MAX_MSG_SIZE, aFormat, lVaList);
  pthread_mutex_unlock(&mVaArgMutex);

  assert(lRc != -1 && lRc < LogMsg::MAX_MSG_SIZE);

  pthread_mutex_lock(&mMsgQueueMutex);
  mMsgQueue.push(lMsg);
  pthread_mutex_unlock(&mMsgQueueMutex);  
}

// ****************************************************************************
//
// ****************************************************************************
void LogMgr::Info(const char *aFormat, ...)
{
  LogMsg *lMsg = new LogMsg();
  gettimeofday(&lMsg->mMsgTime, NULL);
  lMsg->mMsgLevel = LogMsg::LogLevel::Info;

  pthread_mutex_lock(&mVaArgMutex);
  va_list lVaList;
  va_start(lVaList, aFormat);
  int lRc = vsnprintf(lMsg->mMsg, LogMsg::MAX_MSG_SIZE, aFormat, lVaList);
  pthread_mutex_unlock(&mVaArgMutex);

  assert(lRc != -1 && lRc < LogMsg::MAX_MSG_SIZE);

  pthread_mutex_lock(&mMsgQueueMutex);
  mMsgQueue.push(lMsg);
  pthread_mutex_unlock(&mMsgQueueMutex);  
}

// ****************************************************************************
//
// ****************************************************************************
void LogMgr::Warning(const char *aFormat, ...)
{
  LogMsg *lMsg = new LogMsg();
  gettimeofday(&lMsg->mMsgTime, NULL);
  lMsg->mMsgLevel = LogMsg::LogLevel::Warning;

  pthread_mutex_lock(&mVaArgMutex);
  va_list lVaList;
  va_start(lVaList, aFormat);
  int lRc = vsnprintf(lMsg->mMsg, LogMsg::MAX_MSG_SIZE, aFormat, lVaList);
  pthread_mutex_unlock(&mVaArgMutex);

  assert(lRc != -1 && lRc < LogMsg::MAX_MSG_SIZE);

  pthread_mutex_lock(&mMsgQueueMutex);
  mMsgQueue.push(lMsg);
  pthread_mutex_unlock(&mMsgQueueMutex);  
}

// ****************************************************************************
//
// ****************************************************************************
void LogMgr::Error(const char *aFormat, ...)
{
  LogMsg *lMsg = new LogMsg();
  gettimeofday(&lMsg->mMsgTime, NULL);
  lMsg->mMsgLevel = LogMsg::LogLevel::Error;

  pthread_mutex_lock(&mVaArgMutex);
  va_list lVaList;
  va_start(lVaList, aFormat);
  int lRc = vsnprintf(lMsg->mMsg, LogMsg::MAX_MSG_SIZE, aFormat, lVaList);
  pthread_mutex_unlock(&mVaArgMutex);

  assert(lRc != -1 && lRc < LogMsg::MAX_MSG_SIZE);

  pthread_mutex_lock(&mMsgQueueMutex);
  mMsgQueue.push(lMsg);
  pthread_mutex_unlock(&mMsgQueueMutex);  
}

// ****************************************************************************
//
// ****************************************************************************
void LogMgr::Fatal(const char *aFormat, ...)
{
  LogMsg *lMsg = new LogMsg();
  gettimeofday(&lMsg->mMsgTime, NULL);
  lMsg->mMsgLevel = LogMsg::LogLevel::Fatal;

  pthread_mutex_lock(&mVaArgMutex);
  va_list lVaList;
  va_start(lVaList, aFormat);
  int lRc = vsnprintf(lMsg->mMsg, LogMsg::MAX_MSG_SIZE, aFormat, lVaList);
  pthread_mutex_unlock(&mVaArgMutex);

  assert(lRc != -1 && lRc < LogMsg::MAX_MSG_SIZE);

  pthread_mutex_lock(&mMsgQueueMutex);
  mMsgQueue.push(lMsg);
  pthread_mutex_unlock(&mMsgQueueMutex);  
}

// ****************************************************************************
//
// ****************************************************************************
LogMgr *LogMgr::create_instance()
{
//  std::cout << "LogMgr::create_instance - start" << std::endl;

  if(NULL == gInstance)
  {
    gInstance = new LogMgr();

    pthread_mutex_init(&mMsgQueueMutex, NULL);
    pthread_mutex_init(&mVaArgMutex, NULL);

    pthread_create(&gMsgThread, NULL, &thread_proc_helper, gInstance);
//    std::cout << "LogMgr::create_instance - finished" << std::endl;
    return gInstance;
  }

  std::cout << "LogMgr::create_instance - error - instance already created" << std::endl;
  // Instance already created, return NULL to indicate ERROR
  return NULL;
}

// ****************************************************************************
//
// ****************************************************************************
LogMgr *LogMgr::get_instance()
{ 
//  std::cout << "LogMgr::get_instance - start" << std::endl;
//  std::cout << "LogMgr::get_instance - finished" << std::endl;
  // Return static instance. Note, if instance is not yet created this will
  // return NULL.
  return gInstance;
}


// ****************************************************************************
//
// ****************************************************************************
void * LogMgr::thread_proc()
{
  Trace("LogMgr::thread_proc - start\v");

  while(mRunning)
  {
    pthread_mutex_lock(&mMsgQueueMutex);
    int lCount = mMsgQueue.size();
    pthread_mutex_unlock(&mMsgQueueMutex);


    if(lCount > 0)
    {
      do
      {
        pthread_mutex_lock(&mMsgQueueMutex);
        LogMsg* lMsg = mMsgQueue.front();
        mMsgQueue.pop();
        pthread_mutex_unlock(&mMsgQueueMutex);

        static char lTimeBuf[20];
        snprintf(lTimeBuf, 20, "%ld.%06ld", lMsg->mMsgTime.tv_sec, lMsg->mMsgTime.tv_usec);
        std::cout << lTimeBuf << ": ";
        std::cout << lMsg->get_log_level_string();
        std::cout << lMsg->mMsg;

        if(NULL != lMsg)
        {
          delete lMsg;
          lMsg = NULL;
        }

        pthread_mutex_lock(&mMsgQueueMutex);
        lCount = mMsgQueue.size();
        pthread_mutex_unlock(&mMsgQueueMutex);

      } while (lCount > 0);
      
    }
    else
    {
      usleep(100);
    }
  }

//  std::cout << "LogMgr::thread_proc - finished" << std::endl;

  return NULL;
}

