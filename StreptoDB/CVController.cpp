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


//function reads image from file and returns a 8bit deep, unsigned int type with 3 channels RGB Mat
cv::Mat CVController::readImage(std::string path) {
	cv::Mat matIN = cv::imread(path);
	if (matIN.dims != NULL) {
		cv::Mat matOUT(cv::Size(2752, 2208), CV_16UC3);
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
			cv::Mat matOUT(cv::Size(2752, 2208), CV_16UC3);
			cv::resize(matIN, matOUT, cv::Size(2752, 2208));

			return matOUT;
		}
		else { return cv::Mat();
		}
	}
}


//returns the mean value of the first color channel
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


int CVController::extractScale(std::string path)
{
	/// Source image to display
	Mat img_display;
	cv::Mat img = CVController::readImage(path);
	img.copyTo(img_display);

	/// Create the result matrix
	Mat templ = Mat(7, 100, CV_8UC3, Scalar(255, 255, 255)); //CV_8UC3
	//templ.flags = 1124024336;

	//cv::Mat templ = cv::imread("D:/Images/scale.tif");
	
	int result_cols = img.cols -templ.cols + 1;
	int result_rows = img.rows -templ.rows + 1;
	Mat result;
	result.create(result_rows, result_cols, CV_8UC3); //CV_32FC1

	/// Do the Matching and Normalize
	int match_method = TM_SQDIFF;
	matchTemplate(img, templ, result, match_method);
	normalize(result, result, 0, 1, NORM_MINMAX, -1, Mat());

	/// Localizing the best match with minMaxLoc
	double minVal; double maxVal; Point minLoc; Point maxLoc;
	Point matchLoc;

	minMaxLoc(result, &minVal, &maxVal, &minLoc, &maxLoc, Mat());

	// For SQDIFF and SQDIFF_NORMED, the best matches are lower values. For all the other methods, the higher the better
	if (match_method == TM_SQDIFF || match_method == TM_SQDIFF_NORMED)
	{
		matchLoc = minLoc;
	}
	else
	{
		matchLoc = maxLoc;
	}

	//get the length of the scale
	int length = 0;
	int x = matchLoc.x;
	while (img.at<Vec3b>(Point(x, matchLoc.y)) == Vec3b(255, 255, 255)) {
		//if (img.at<Vec3b>(Point(matchLoc.x, matchLoc.y))[0] == 255) {
		x--;
		length++;
	}
	x = matchLoc.x + 1;
	while (img.at<Vec3b>(Point(x, matchLoc.y)) == Vec3b(255, 255, 255)) {
		x++;
		length++;
	}



	/// Show me what you got
	rectangle(img_display, matchLoc, Point(matchLoc.x + templ.cols, matchLoc.y + templ.rows), Scalar::all(0), 2, 8, 0);
	rectangle(result, matchLoc, Point(matchLoc.x + templ.cols, matchLoc.y + templ.rows), Scalar::all(0), 2, 8, 0);

	char* image_window = "Source Image";
	char* result_window = "Result window";
	//char* test_window = "testing";
	namedWindow(image_window, WINDOW_KEEPRATIO);
	namedWindow(result_window, WINDOW_KEEPRATIO);
	//namedWindow(test_window, WINDOW_KEEPRATIO);
	imshow(image_window, img_display);
	imshow(result_window, result);
	//imshow(test_window, templ);


	return length;
}
