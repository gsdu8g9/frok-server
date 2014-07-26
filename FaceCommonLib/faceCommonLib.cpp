#include <pthread.h>
#include <string.h>
#include "faceCommonLib.h"

#include <sys/time.h>

#define MODULE_NAME     "COMMON_LIB"

pthread_mutex_t filePrint_cs;
struct timeval startTime;

bool InitFaceCommonLib(const char *log_name)
{
    int result = 0;

    pthread_mutexattr_t mAttr;
    if(0 != (result = pthread_mutexattr_init(&mAttr)))
    {
        TRACE_F("pthread_mutexattr_init failed on error %s", strerror(result));
        return false;
    }
    if(0 != (result = pthread_mutexattr_settype(&mAttr, PTHREAD_MUTEX_RECURSIVE_NP)))
    {
        TRACE_F("pthread_mutexattr_settype failed on error %s", strerror(result));
        return false;
    }

    if(0 != (result = pthread_mutex_init(&filePrint_cs, &mAttr)))
    {
        TRACE_F("pthread_mutex_init failed on error %s", strerror(result));
        return false;
    }

    if(0 != (result = pthread_mutexattr_destroy(&mAttr)))
    {
        TRACE_F("pthread_mutexattr_destroy failed on error %s", strerror(result));
        return false;
    }

    if(log_name != NULL)
    {
        pthread_mutex_lock(&filePrint_cs);
        if(log_file != NULL)
        {
            delete []log_file;
        }
        log_file = new char[strlen(log_name) + 1];
        strcpy(log_file, log_name);
        pthread_mutex_unlock(&filePrint_cs);
    }

    memset(&startTime, 0, sizeof(startTime));
    gettimeofday(&startTime, NULL);

    return true;
}

bool DeinitFaceCommonLib()
{
    int result = 0;
    if(log_file != NULL)
    {
        delete []log_file;
    }

    if(0 != (result = pthread_mutex_destroy(&filePrint_cs)))
    {
        printf("pthread_mutexattr_destroy failed on error %s", strerror(result));
        return false;
    }
    return true;
}

void set_time_stamp(unsigned *sec, unsigned *usec)
{
    struct timeval currentTime;
    memset(&currentTime, 0, sizeof(currentTime));

    gettimeofday(&currentTime, NULL);

    (*sec)  = currentTime.tv_sec - startTime.tv_sec;
    (*usec) = currentTime.tv_usec - startTime.tv_usec;

    if (startTime.tv_usec > currentTime.tv_usec)
    {
        (*sec)--;
        (*usec) += 1e6;
    }
}

void print_time(timespec &startTime, timespec &endTime)
{
    unsigned sec  = endTime.tv_sec - startTime.tv_sec;
    unsigned nsec = endTime.tv_nsec - startTime.tv_nsec;

    if (startTime.tv_nsec > endTime.tv_nsec)
    {
        sec--;
        nsec += 1e9;
    }

    fprintf(stdout, "Time elapsed: %u.%09u\n", sec, nsec);
}

char *FrokResultToString(FrokResult res)
{
    switch(res)
    {
        CASE_RET_STR(FROK_RESULT_SUCCESS);
        CASE_RET_STR(FROK_RESULT_CASCADE_ERROR);
        CASE_RET_STR(FROK_RESULT_UNSPECIFIED_ERROR);
        CASE_RET_STR(FROK_RESULT_NOT_A_FACE);
        CASE_RET_STR(FROK_RESULT_INVALID_PARAMETER);
        CASE_RET_STR(FROK_RESULT_OPENCV_ERROR);
        CASE_RET_STR(FROK_RESULT_NO_MODELS);
        default:
        {
            return "UNKNOWN_RESULT";
        }
    }
}
