#include "CVController.h"

using namespace cv;
//using namespace std;

CVController::CVController()
{
	//Mat imageCV;
	//imageCV = imread(fileName.toStdString, IMREAD_COLOR);


}


CVController::~CVController()
{
}






QImage CVController::Mat2QImage(cv::Mat const& src)
{
	cv::Mat temp; // make the same cv::Mat
	cvtColor(src, temp, cv::COLOR_RGB2BGR); // cvtColor Makes a copt, that what i need
	QImage dest((const uchar*)temp.data, temp.cols, temp.rows, temp.step, QImage::Format_RGB888);
	dest.bits(); // enforce deep copy, see documentation 
	// of QImage::QImage ( const uchar * data, int width, int height, Format format )
	return dest;
}

cv::Mat CVController::QImage2Mat(QImage const& src)
{
	cv::Mat tmp(src.height(), src.width(), CV_8UC3, (uchar*)src.bits(), src.bytesPerLine()); //CV_32FC4
	cv::Mat result; // deep copy just in case (my lack of knowledge with open cv)
	cvtColor(tmp, result, cv::COLOR_RGB2BGR);
	return result;
}


cv::Mat CVController::readImage(std::string path) {
	cv::Mat matIN = cv::imread(path);
	if (matIN.dims != NULL) {
		cv::Mat matOUT(cv::Size(2752, 2208), CV_16FC3);
		cv::resize(matIN, matOUT, cv::Size(2752, 2208));

		return matOUT;
	}
	else {
		QImage image(QString::fromStdString(path));
		if (image.isNull()) {
			return cv::Mat();
		}
		matIN = QImage2Mat(image);
		if (matIN.dims != NULL) {
			cv::Mat matOUT(cv::Size(2752, 2208), CV_16FC3);
			cv::resize(matIN, matOUT, cv::Size(2752, 2208));

			return matOUT;
		}
		else { return cv::Mat();
		}
	}
}


double CVController::mean1(std::string path)
{
	cv::Mat mat = CVController::readImage(path);
	if (mat.dims != NULL) {
		cv::Scalar tempVal = cv::mean(mat);

		return tempVal.val[0];
	}
	else {
		return NULL; 
	}
}
