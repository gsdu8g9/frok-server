#ifndef FACECOMMONLIB_H
#define FACECOMMONLIB_H

// Lib includes
#include "json.h"               // class for easy json (de)serializing, MIT LICENSE
#include "commonThread.h"       // class for safe working with unix threads
#include "io.h"                 // File system - depend operations, input - output operations
#include "trace.h"              // trace system

// FaceDetectionLib defaults
#define LOG_MESSAGE_MAX_LENGTH      1024
const char DEFAULT_LOG_FILE_NAME [] = "facelog.log";

// Externals
extern pthread_mutex_t filePrint_cs;

// Result of Face*Libraries
enum FrokResult
{
    FROK_RESULT_SUCCESS,
    FROK_RESULT_CASCADE_ERROR,
    FROK_RESULT_UNSPECIFIED_ERROR,
    FROK_RESULT_INVALID_PARAMETER,
    // etc
};

// Common defines
#define UNREFERENCED_PARAMETER(P)           (P=P)
#define SOCKET                          int
#define SOCKET_ERROR                    (-1)
#define INVALID_SOCKET                  (-1)
#define COMMAND_WITH_LENGTH(__CHARS__)      (__CHARS__), strlen((__CHARS__))

// Library init functions
bool InitFaceCommonLib(const char *logFileName = DEFAULT_LOG_FILE_NAME);
bool DeinitFaceCommonLib();
void set_time_stamp(unsigned *sec, unsigned *usec);

#endif // FACECOMMONLIB_H
