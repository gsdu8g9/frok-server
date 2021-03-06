#ifndef IO_H
#define IO_H

#include "frokCommonTypes.h"

// include dependencies
#include <stdio.h>
#include <sys/stat.h>
#include <sys/time.h>

#pragma GCC poison cout
#pragma GCC poison printf

extern char *tracePrefix;
// Trace system
#ifdef TRACE_DEBUG

// Colored print defines
#define _FAIL(__x__, ...)    "[%s][%s->%s] \x1b[1;91m[FAIL] "   __x__ "\n\x1b[0m", tracePrefix, MODULE_NAME, __FUNCTION__, ##__VA_ARGS__
#define _WARN(__x__, ...)    "[%s][%s->%s] \x1b[1;93m[WARN] "   __x__ "\n\x1b[0m", tracePrefix, MODULE_NAME, __FUNCTION__, ##__VA_ARGS__
#define _SUCC(__x__, ...)    "[%s][%s->%s] \x1b[1;97m[SUCC] "   __x__ "\n\x1b[0m", tracePrefix, MODULE_NAME, __FUNCTION__, ##__VA_ARGS__
#define _RES(__x__, ...)     "[%s][%s->%s] \x1b[1;95m[RES] "    __x__ "\n\x1b[0m", tracePrefix, MODULE_NAME, __FUNCTION__, ##__VA_ARGS__
#define _N(__x__, ...)       "[%s][%s->%s] "                    __x__ "\n",        tracePrefix, MODULE_NAME, __FUNCTION__, ##__VA_ARGS__
#else
#define _FAIL(__x__, ...)    "[%s][%s->%s] [FAIL] "   __x__ "\n", tracePrefix, MODULE_NAME, __FUNCTION__, ##__VA_ARGS__
#define _WARN(__x__, ...)    "[%s][%s->%s] [WARN] "   __x__ "\n", tracePrefix, MODULE_NAME, __FUNCTION__, ##__VA_ARGS__
#define _SUCC(__x__, ...)    "[%s][%s->%s] [SUCC] "   __x__ "\n", tracePrefix, MODULE_NAME, __FUNCTION__, ##__VA_ARGS__
#define _RES(__x__, ...)     "[%s][%s->%s] [RES] "    __x__ "\n", tracePrefix, MODULE_NAME, __FUNCTION__, ##__VA_ARGS__
#define _N(__x__, ...)       "[%s][%s->%s] "          __x__ "\n", tracePrefix, MODULE_NAME, __FUNCTION__, ##__VA_ARGS__
#endif //TRACE_DEBUG

#define TRACE_F_T(__x__, ...)   TRACE_TIMESTAMP(_FAIL(__x__,  ##__VA_ARGS__))
#define TRACE_W_T(__x__, ...)   TRACE_TIMESTAMP(_WARN(__x__,  ##__VA_ARGS__))
#define TRACE_S_T(__x__, ...)   TRACE_TIMESTAMP(_SUCC(__x__,  ##__VA_ARGS__))
#define TRACE_R_T(__x__, ...)   TRACE_TIMESTAMP(_RES(__x__, ##__VA_ARGS__))
#define TRACE_T(__x__, ...)     TRACE_TIMESTAMP(_N(__x__,  ##__VA_ARGS__))

#define TRACE_F(__x__, ...)     TRACE(_FAIL(__x__,  ##__VA_ARGS__))
#define TRACE_W(__x__, ...)     TRACE(_WARN(__x__,  ##__VA_ARGS__))
#define TRACE_S(__x__, ...)     TRACE(_SUCC(__x__,  ##__VA_ARGS__))
#define TRACE_R(__x__, ...)     TRACE(_RES(__x__, ##__VA_ARGS__))
#define TRACE_N(__x__, ...)     TRACE(_N(__x__, ##__VA_ARGS__))

#define TRACE_TIMESTAMP(format...)      do{struct timeval tv = {0, 0};                          \
                                        pthread_mutex_lock(&commonContext->trace_cs);           \
                                        gettimeofday(&tv,NULL);                                 \
                                        int sec, usec;                                          \
                                        sec  = tv.tv_sec - commonContext->startTime.tv_sec;     \
                                        if(commonContext->startTime.tv_usec > tv.tv_usec){--sec;\
                                        usec=1e6+tv.tv_usec-commonContext->startTime.tv_usec;}  \
                                        else{usec=tv.tv_usec-commonContext->startTime.tv_usec;} \
                                        fprintf(stdout, "[%5d.%06d]", sec, usec);               \
                                        fprintf(stdout, ##format);                              \
                                        pthread_mutex_unlock(&commonContext->trace_cs);}while(0)

#define TRACE(format...)                fprintf(stdout, ##format);

//externals

#ifdef __cplusplus
extern "C" {
#endif

// don't forget '/' in the end of dir name.
// Example: good = "/home/workspace/" bad: "/home/workspace"
BOOL getFilesFromDir(const char *dir, char ***files, unsigned *filesNum);
BOOL getSubdirsFromDir(const char *dir, char ***files, unsigned *filesNum);
BOOL mkpath(const char *path, mode_t mode);
#ifdef __cplusplus
}
#endif

#endif // IO_H
