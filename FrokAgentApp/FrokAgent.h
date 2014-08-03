#ifndef FROKAGENT_H
#define FROKAGENT_H

#define DEFAULT_PORT                28015
#define MAX_SOCKET_BUFF_SIZE            (163840)

// include dependencies
#include "FrokAPI.h"
#include "faceCommonLib.h"

typedef enum NetResult
{
    NET_SUCCESS                 = 0x00,
    NET_SOCKET_ERROR            = 0x01,
    NET_MEM_ALLOCATION_FAIL     = 0x02,
    NET_NO_CALLBACK             = 0x03,
    NET_UNSPECIFIED_ERROR       = 0x04,
    NET_INVALID_PARAM           = 0x05,
    NET_COMMON_THREAD_ERROR     = 0x06,
    NET_ALREADY_STARTED         = 0x07
    //...
} NetResult;

#pragma pack(push, 1)

typedef struct
{
    SOCKET      replySocket;
    unsigned    dataLength;
    char       *data;
} FaceRequest;

#pragma pack(pop)

class FrokAgent
{
private:
    char                   *photoBasePath;
    char                   *targetsFolderPath;
    unsigned short          localPortNumber;
    SOCKET                  localSock;
    CommonThread           *threadServerListener;
    FaceRecognizerAbstract *recognizer;
    FaceDetectorAbstract   *detector;
    FrokAPI                *fapi;

public:
    FrokAgent(std::map<std::string, FrokAPIFunction*> enabledFucntions, unsigned short localPort = DEFAULT_PORT, const char *photoBasePath = DEFAULT_PHOTO_BASE_PATH, const char *targetsFolderPath = DEFAULT_TARGETS_FOLDER_PATH);
    ~FrokAgent();

    bool StartFrokAgent();
    bool StopFrokAgent();
protected:
    NetResult StartNetworkServer();
    NetResult StopNetworkServer();
    NetResult SendData(SOCKET sock, const char* pBuffer, unsigned uBufferSize);
private:
    // Only one connected server is allowed. Disconnect current connection to allow new server connect
    static void ServerListener(void* param);
};

#endif // FROKAGENT_H
