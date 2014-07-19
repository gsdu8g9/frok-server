#include <stdio.h>

#include "FaceAgent.h"
#include "activities.h"
#include "FaceDetector.h"

void usage()
{
    FilePrintMessage(_SUCC("FaceDetectionApp <Local port number>"));
    return;
}

int main(void)
{
    FaceAgent agent(DEFAULT_PORT);
    agent.StartFaceAgent();
    getchar();

    agent.StopFaceAgent();

    return 0;
}
