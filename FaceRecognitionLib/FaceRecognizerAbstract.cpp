#include "FaceRecognizerAbstract.h"
#include "FaceModelEigenfaces.h"
#include "FaceModelAbstract.h"
#include "unistd.h"

#pragma GCC poison IplImage
#define MODULE_NAME     "FACE_RECOGNIZER_ABSTRACT"

FaceRecognizerAbstract::FaceRecognizerAbstract()
{
    TRACE_T("new FaceRecognizerAbstract");
}
FaceRecognizerAbstract::~FaceRecognizerAbstract()
{
    TRACE_T("~FaceRecognizerAbstract");
}
