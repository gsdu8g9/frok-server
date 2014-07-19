#ifndef EIGENDETECTOR_H
#define EIGENDETECTOR_H
#include <cv.h>
#include <highgui.h>

#include <opencv2/legacy/legacy.hpp>
#include <opencv2/contrib/contrib.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <opencv2/nonfree/nonfree.hpp>
#include <opencv2/nonfree/features2d.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/objdetect/objdetect.hpp>

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include "string.h"

#include <vector>
#include <string>
#include <stdio.h>
#include <iostream>
#include <dirent.h>
#include <sys/stat.h>
#include <cstring>
#include <semaphore.h>
#include <errno.h>

/**
* \file EigenDetector.h
* \brief This file defines class for face detection recognision
*
* In this class we use EigenDetector algorythm. For more information google "Eigen detection algorythm".
*
*/

/** \addtogroup EigenDetector
*  \brief Face recognision subsystem:
*  \{
*/

/** \class EigenDetector
* \brief face recognizer class.
*
* This class is used to generate faces base (.yml) from image base on your PC.
* You can recognize people by id on target photo and see likeness of any faces found on target picture from face base.
* Eigen Detector algorythm is used for recognision.
*
*/

class EigenDetector
{
public:

    /**
    * \brief Training Eigen detection algorythm on recognized faces.
    *
    * Training Eigen detection algorythm on faces we've got in our faces database.
    *
    * \param[in]    idPath        Direction to folder with faces with specified id.
    *
    * <b>Usage example:</b>
    *
    * \code
    *
    * if (!eigenDetector->train((((string)ID_PATH).append(psContext->arrIds[i].ToString())).c_str()))
    * {
    * delete eigenDetector;
    * continue;
    * }
    *
    * \endcode
    */

    bool train(const char* idPath);

    /**
    * \brief Recognizes faces from \a model on \a image and places likeness and faces' frames on \a resultImage
    *
    * Recognizes faces from \a model on \a image and places likeness and faces' frames on \a resultImage
    * *.yml file should be created before function call.
    *
    * \param[in]    &models        Pair of id and *.yml file (*.yml file is created by \a learn learn function);
    * \param[in]    psDataJson    Array of id's which are more suit for faces program has found;
    * \param[in]    image        target cv image file;
    *
    * <b>Usage example:</b>
    *
    * \code
    *
    *    IplImage *dest = cvCreateImage(cvSize(158, 190), face_img->depth, face_img->nChannels);
    *        cvResize(face_img, dest, 1);
    *        eigenDetector->recognize(models, &dataJson, dest);
    *        dataJson.p1s.push_back(points.p1);
    *        dataJson.p2s.push_back(points.p2);
    *
    * \endcode
    */

    void recognize(const map < string, Ptr<FaceRecognizer> > &models, DataJson *psDataJson, IplImage* image);

    /**
    * \brief Imposition mask.
    *
    * Imposition mask on recognized face.
    *
    * \return Returns the picture with mask on it.
    *
    * \param[in]    *img        Recognized face.
    *
    * <b>Usage example:</b>
    *
    * \code
    *
    * psParams->pThis->face_img = psParams->pThis->imposeMask(points.p1);
    * psParams->pThis->face_img = cvCloneImage(&(IplImage)eigenDetector->MaskFace(psParams->pThis->face_img));
    *
    * \endcode
    */

    Mat  MaskFace(IplImage *img);

private:

    /**
    * \brief Fills \a images and \a labels vectors with faces from \a dir directory.
    *
    * Fills \a images with matrixes of faces in \a dir folder and \a labels vector with \a id
    *
    * \param[in]    facesPath    folder that contains face's that will be used for training
    * \param[out]    *images        vector of matrixes of images in \a dir directory
    * \param[out]    *labels        vector of ids.
    * \param[in]    id            id that would be stored in \a *labels vector
    *
    * \code
    *
    * vector<Mat> images;
    * vector<int> labels;
    * Ptr<FaceRecognizer> model = createEigenFaceRecognizer();
    * try
    * {
    *    loadBaseFace(facesPath.c_str(), &images, &labels, 0);
    * }
    * catch (...)
    *
    * \endcode
    */

    void loadBaseFace(const char* facesPath, vector<Mat> * images, vector<int>* labels, int id);

    /**
    * \brief This function finds similarity of two pictures by comparing eigenvectors.
    *
    * This function finds difference between two eigenvectors and
    * returns probability of similarity of two pictures.
    *
    * \return probability of similarity of two pictures;
    *
    * \param[in] &image_mat                 first picture matrix;
    * \param[in] &reconstructedFace     second picture matrix.
    *
    * <b>Usage example:</b>
    *
    * \code
    *
    * double prob2 = getSimilarity2(reconstructedFace, image_mat);
    * double prob1 = getSimilarity(reconstructedFace, image_mat);
    *
    * \endcode
    */

    double getSimilarity(const Mat *image_mat, const Mat *reconstructedFace);

    /**
    * \brief This function finds similarity of two pictures by comparing matrix.
    *
    * This function finds difference between two matrix and
    * returns probability of similarity of two pictures.
    *
    * \return probability of similarity of two pictures;
    *
    * \param[in]    &projected_mat            first picture matrix;
    * \param[in]    &face_mat                second picture matrix.
    *
    * <b>Usage example:</b>
    *
    * \code
    *
    * double prob2 = getSimilarity2(reconstructedFace, image_mat);
    * double prob1 = getSimilarity(reconstructedFace, image_mat);
    *
    * \endcode
    */

    double getSimilarity2(const Mat *projected_mat, const Mat *face_mat);

    /**
    * \brief This function finds similarity of two pictures by getting L2 error.
    *
    * This function compares two images by getting the L2 error (square-root of sum of squared error).
    *
    * \return probability of similarity of two pictures;
    *
    * \param[in]    &projected_mat            first picture matrix;
    * \param[in]    &face_mat                second picture matrix.
    *
    * <b>Usage example:</b>
    *
    * \code
    *
    * double prob2 = getSimilarity2(reconstructedFace, image_mat);
    * double prob1 = getSimilarity(reconstructedFace, image_mat);
    *
    * \endcode
    */

    double getSimilarity3(const Mat *projected_mat, const Mat *face_mat);
};
/** \} */
#endif //EIGENDETECTOR_H
