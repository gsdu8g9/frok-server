#include <stdio.h>
#include "FrokAgent.h"

void usage()
{
    printf("FaceDetectionApp <Local port number>");
    return;
}

#define MODULE_NAME ""

int main(void)
{
    if(!InitFaceCommonLib())
    {
        TRACE_F("InitFaceCommonLib");
        return -1;
    }

    /*FaceRecognizerAbstract *recognizer = new FaceRecognizerEigenfaces;
    FaceDetectorAbstract *detector = new FrokFaceDetector;*/

    //FAPI_Recognize_JSON2FUNCP(recognizer);

    std::vector<std::string> ids;
    //ids.push_back("0");fgfh
    //ids.push_back("1");
    ids.push_back("2");
    /*ids.push_back("3");
    ids.push_back("4");
    ids.push_back("5");
    ids.push_back("6");
    ids.push_back("7");
    ids.push_back("8");
    ids.push_back("9");
    ids.push_back("10");
    ids.push_back("11");
    ids.push_back("12");
    ids.push_back("13");
    ids.push_back("14");
    ids.push_back("15");
    ids.push_back("16");
    ids.push_back("17");*/
    printf("Calling TrainUserModel...\n");
    //TrainUserModel(ids, DEFAULT_PHOTO_BASE_PATH, detector, recognizer);
    printf("TrainUserModel finished\n");
    std::vector< std::map<std::string, double> > similarities;
    printf("Calling Recognize...\n");
    /*FaceUserModel model(ids[0], RECOGNIZER_EIGENFACES);
    std::string modelPath = DEFAULT_PHOTO_BASE_PATH;
    modelPath.append(ids[0]).append("/");
    model.LoadUserModel(modelPath.c_str());
    recognizer->AddFaceUserModel(ids[0], model);*/
    //Recognize(similarities, ids, DEFAULT_PHOTO_BASE_PATH, "1.jpg", DEFAULT_TARGETS_FOLDER_PATH, detector, recognizer);
    //Recognize(similarities, ids, DEFAULT_PHOTO_BASE_PATH, "2.jpg", DEFAULT_TARGETS_FOLDER_PATH, detector, recognizer);

    printf("Recognize finished\n");
    /*std::vector< std::map<std::string, double> > similarities;
    printf("Calling Recognize...\n");
    Recognize(similarities, ids, DEFAULT_PHOTO_BASE_PATH, "1.jpg", DEFAULT_TARGETS_FOLDER_PATH, detector, recognizer);
    printf("Rcognize finished\n");*/

    /*std::vector<cv::Rect> faces;
    std::vector<cv::Mat> images;
    detector.SetTargetImage("/home/zda/faces/1/photos/Picture (15).jpg");
    detector.GetFacesFromPhoto(faces);
    detector.GetFaceImages(faces, images);
    cv::imwrite("/home/zda/_face.jpg", images[0]);
    detector.GetNormalizedFaceImages(faces, images);*/

    return 0;
}
