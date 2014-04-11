#include "stdafx.h"
#include "EigenDetector_v2.h"
#include <stdlib.h>
#include <io.h>
#include <Math.h>

#include "opencv2/contrib/contrib.hpp"


/*
	�������� ����������� � ������
	dir - ./faces, �� ������� ������� ����������� � ����� ��� ��������
	*/
void EigenDetector_v2::loadBaseFace(char* dir, vector<Mat> * images, vector<int>* labels, int id){

	_finddata_t result;
	char name[1024];
	long done;
	IplImage *base_face = 0;

	sprintf(name, "%s\\*.jpg", dir);
	memset(&result, 0, sizeof(result));
	done = _findfirst(name, &result);
	int count = 0;
	int max_p = 0;

	if (done != -1)
	{
		int res = 0;
		while (res == 0){
			//cout << result.name << endl;
			sprintf(name, "%s\\%s", dir, result.name);
			IplImage *dist = cvLoadImage(name, CV_LOAD_IMAGE_GRAYSCALE);
			IplImage *resize = cvCreateImage(cvSize(158, 214), dist->depth, dist->nChannels);
			cvResize(dist, resize, 1);

			images->push_back(Mat(resize, true));
			labels->push_back(id);

			cout << name << endl;
			count++;
			res = _findnext(done, &result);
		}
	}
	_findclose(done);
	cvReleaseImage(&base_face);
}

/*
	�������� FaceRecognizer �� ����
	model - ������ FaceRecognizer, ����������� ����� �������� � yml
	path - ���� �� ���� �����(����� ��� ������� �������� ��������� ��� id, �������� � ���� ./faces � ./photos)
	*/
Ptr<FaceRecognizer> EigenDetector_v2::learn(char* path, Ptr<FaceRecognizer> model){
	vector<Mat> images;
	vector<int> labels;
	char path_id[1024];
	WIN32_FIND_DATA FindFileData;
	HANDLE hf;

	sprintf(path_id, "%s//*", path);
	hf = FindFirstFile(path_id, &FindFileData);
	if (hf != INVALID_HANDLE_VALUE){
		while (FindNextFile(hf, &FindFileData) != 0){
			char* name = FindFileData.cFileName;
			if (strcmp(name, "..")){
				char path_face[1024];
				sprintf(path_face, "%s\\%s\\faces\\", path, name);
				loadBaseFace(path_face, &images, &labels, atoi(name));
			}

		}
		FindClose(hf);
	}
	model->train(images, labels);
	return model;
}

double EigenDetector_v2::getSimilarity(const Mat A, const Mat B) {

	Mat dif = abs(A - B);
	int koef = 0;
	double err = 0;
	for (int y(0); y < dif.rows; ++y){
		for (int x(0); x < dif.cols; ++x){
			int d = dif.at<unsigned char>(y, x);
			if (d >= 10 && d <= 200)
				koef += d - 10;
		}
	}

	err = (double)koef/ (dif.cols*dif.rows* 20);

	cout << err << " " << koef << endl;
	if (err > 1) err = 1;
	return (1 - err);
}

void EigenDetector_v2::recognize(Ptr<FaceRecognizer> model, IplImage* image, IplImage* resultImage, CvPoint p){
	int predicted_Eigen = 0, koef = 0;
	double prob = 0, err = 0;
	Mat image_mat = Mat(image, true);


	predicted_Eigen = model->predict(image_mat);

	// Get some required data from the FaceRecognizer model.
	Mat eigenvectors = model->get<Mat>("eigenvectors");
	Mat averageFaceRow = model->get<Mat>("mean");
	// Project the input image onto the eigenspace.
	Mat projection = subspaceProject(eigenvectors, averageFaceRow, image_mat.reshape(1, 1));
	// Generate the reconstructed face back from the eigenspace.
	Mat reconstructionRow = subspaceReconstruct(eigenvectors, averageFaceRow, projection);
	// Make it a rectangular shaped image instead of a single row.
	Mat reconstructionMat = reconstructionRow.reshape(1, image->height);
	// Convert the floating-point pixels to regular 8-bit uchar.
	Mat reconstructedFace = Mat(reconstructionMat.size(), CV_8U);
	reconstructionMat.convertTo(reconstructedFace, CV_8U, 1, 0);

	char dig[1024];

	sprintf(dig, "repr %d", p.x + p.y);

	//imshow(dig, reconstructedFace);
	sprintf(dig, "face %d", p.x + p.y);
	imshow(dig, image_mat);

	sprintf(dig, "diff %d", p.x + p.y);
	Mat dif = abs(image_mat - reconstructedFace);
	//imshow(dig, dif);

	prob = getSimilarity(image_mat, reconstructedFace);
	//predicted_Eigen = model->predict(reconstructedFace);

	CvScalar textColor = CV_RGB(0, 230, 255);	// light blue text
	CvFont font;
	cvInitFont(&font, CV_FONT_HERSHEY_PLAIN, 1.0, 1.0, 0, 1, CV_AA);
	char text[256];
	if (prob > 0 && predicted_Eigen >= 0)
		sprintf(text, "id: %d (%.2f%%)", predicted_Eigen, prob * 100);
	else
		sprintf(text, "id: ?");
	cvPutText(resultImage, text, cvPoint(p.x, p.y - 12), &font, textColor);

}