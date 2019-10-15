#include "CVController.h"
#include <iostream>

using namespace cv;
//using namespace std;

CVController::CVController(){
	//nothing, use the functions.
	//Mat imageCV;
	//imageCV = imread(fileName.toStdString, IMREAD_COLOR);
}


CVController::~CVController(){
	
}






QImage CVController::Mat2QImage(cv::Mat const& src){
	cv::Mat temp; // make the same cv::Mat
	cvtColor(src, temp, cv::COLOR_RGB2BGR); // cvtColor Makes a copt, that what i need
	QImage dest((const uchar*)temp.data, temp.cols, temp.rows, temp.step, QImage::Format_RGB888);
	dest.bits(); // enforce deep copy, see documentation 
	// of QImage::QImage ( const uchar * data, int width, int height, Format format )
	return dest;
}

cv::Mat CVController::QImage2Mat(QImage const& src){
	cv::Mat tmp(src.height(), src.width(), CV_8UC3, (uchar*)src.bits(), src.bytesPerLine()); //CV_32FC4
	cv::Mat result;//(cv::Size(2752, 2208), CV_8UC3); // deep copy just in case (my lack of knowledge with open cv)
	cvtColor(tmp, result, cv::COLOR_RGB2BGR); //RGB2BGR
	//cv::resize
	return result;
}



//function reads image from file and returns a 8bit deep, unsigned int type with 3 channels RGB Mat
//But please, just use 2752x2208 pixel images
cv::Mat CVController::readImage(std::string path) {
	cv::Mat matIN = cv::imread(path);
	if (matIN.dims != NULL) {
		cv::Mat matOUT(cv::Size(2752, 2208), CV_8UC3);
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
			cv::Mat matOUT(cv::Size(2752, 2208), CV_8UC3);
			cv::resize(matIN, matOUT, cv::Size(2752, 2208));

			return matOUT;
		}
		else { return cv::Mat();
		}
	}
}



//returns the mean value of the given color channel
double CVController::mean1(std::string path, int channel){
	cv::Mat mat = CVController::readImage(path);
	if (mat.dims != NULL) {
		cv::Scalar tempVal = cv::mean(mat);

		return tempVal.val[channel];
	}
	else {
		return NULL; 
	}
}



//returns the mean foreground value of the given color channel
double CVController::meanFG(int channel){
	if (foreground_const.dims != NULL) {
		cv::Scalar tempVal = cv::mean(foreground_const, mask_const);

		return tempVal.val[channel];
	}
	else {
		return NULL;
	}
}



//returns the mean background value of the given color channel
double CVController::meanBG(int channel){
	if (foreground_const.dims != NULL) {
		cv::Scalar tempVal = cv::mean(background_const, bgmask_const);

		return tempVal.val[channel];
	}
	else {
		return NULL;
	}
}



//Determines the Size of the Foreground by multiplying 
//the number of non black pixels of cv::Mat foreground_const
//with the scale
double CVController::foregroundSize(double scale) {
	return cv::countNonZero(mask_const)*(scale*scale); //make it square-millimeter!
}



//Calculates the Circularity-Factor (1 = perfect circle)
// = (4*pi*A) / P²	//P=Umfang; A=Flächeninhalt
double CVController::circFact(double scale, double area) {
	Mat image = foreground_const;
	std::vector<std::vector<Point> > contours;
	RNG rng(12345);
	//contours.copySize(mask_const);

	cv::findContours(mask_const, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

	/*Mat drawing = Mat::zeros(image.size(), CV_8UC3);
	for (int i = 0; i < contours.size(); i++)
	{
		Scalar color = (255,255,255);
		drawContours(drawing, contours, i, color, 2, 8);
	}
	char* img_windowC = "Contours";
	namedWindow(img_windowC, WINDOW_KEEPRATIO);
	imshow(img_windowC, drawing);*/

	double Umfang = cv::arcLength(contours[0], true) * scale;

	return (4*CV_PI*area)/(Umfang*Umfang);
}



//returns the number of pixels(length of scale in pixel)
int CVController::extractScale(std::string path){
	/// Source image to display
	Mat img_display;
	cv::Mat img = CVController::readImage(path);
	img.copyTo(img_display);

	/// Create the result matrix
	Mat templ = Mat(7, 100, CV_8UC3, Scalar(255, 255, 255)); //CV_8UC3
	
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
	else{
		matchLoc = maxLoc;
	}

	//get the length of the scale
	int length = 0;
	int x = matchLoc.x;
	while (img.at<Vec3b>(Point(x, matchLoc.y)) == Vec3b(255, 255, 255)) {
		x--;
		length++;
	}
	x = matchLoc.x + 1;
	while (img.at<Vec3b>(Point(x, matchLoc.y)) == Vec3b(255, 255, 255)) {
		x++;
		length++;
	}

	//// Show me what you got
	//rectangle(img_display, matchLoc, Point(matchLoc.x + templ.cols, matchLoc.y + templ.rows), Scalar::all(0), 2, 8, 0);
	//rectangle(result, matchLoc, Point(matchLoc.x + templ.cols, matchLoc.y + templ.rows), Scalar::all(0), 2, 8, 0);

	//char* image_window = "Source Image";
	//char* result_window = "Result window";
	////char* test_window = "testing";
	//namedWindow(image_window, WINDOW_KEEPRATIO);
	//namedWindow(result_window, WINDOW_KEEPRATIO);
	////namedWindow(test_window, WINDOW_KEEPRATIO);
	//imshow(image_window, img_display);
	//imshow(result_window, result);
	////imshow(test_window, templ);

	return length;
}




//Background-Foreground speration with cv::threshold 
void CVController::segmentation(std::string path, double th, double bg, double fg, bool show) {
	//string path;
	//double th = threshold adjustment;
	//double bg = Background circle size;
	//double fg = Foreground dilation iterations count adjust;
	//bool show = show in Window on/off;
	Mat img = CVController::readImage(path);
	Mat gray, dst, opening, sure_bg, fgMat, substract, finalIMG,finalBG;
	//make a gray image;
	cvtColor(img, gray, cv::COLOR_RGB2GRAY);

	//find a proper threshold_value, thats the border to cut everything to black or white
	cv::Scalar meanMid = cv::mean(gray.col(gray.cols / 2));
	cv::Scalar meanLeftEdge = cv::mean(gray.col(20));

	int max_BINARY_value = 255;
	int threshold_value = meanLeftEdge[0] + ((meanMid[0] - meanLeftEdge[0]) * 10 / 9) * (1+th);
	int threshold_type = cv::THRESH_BINARY;

	threshold(gray, dst, threshold_value, max_BINARY_value, threshold_type);
	// noise removal
	Mat kernel = Mat::ones(3, 3, CV_8UC1);
	Point anchor = Point(-1, -1);//-1,-1 deafault for center
	//erosion and dilation
	cv::morphologyEx(dst, opening, MORPH_OPEN, kernel, anchor, 2);

	// sure background area
	cv::dilate(opening, sure_bg, kernel, anchor, 10+fg);
	int erosion_size = 3;
	//Sure foreground area
	Mat element = getStructuringElement(MORPH_ELLIPSE,Size(2 * erosion_size + 1, 2 * erosion_size + 1),Point(erosion_size, erosion_size));
	cv::erode(dst, fgMat, element,cv::Point(-1,-1),2);

	// Finding unknown region
	//Take sure_bg and calculate the radius from original image by finding borders from 4 directions
	//with the radius make a mask and substract that
	double maxBG = (cv::mean(img.row(0))[0] + cv::mean(img.row(0))[1] + cv::mean(img.row(0))[2]);
	double minBG = (cv::mean(img.row(0))[0] + cv::mean(img.row(0))[1] + cv::mean(img.row(0))[2]);
	for (int i = 1; i < 100; i++) {
		if ((cv::mean(img.row(i))[0]+ cv::mean(img.row(i))[1]+ cv::mean(img.row(i))[2]) > maxBG) {
			maxBG = (cv::mean(img.row(i))[0] + cv::mean(img.row(i))[1] + cv::mean(img.row(i))[2]);
		}
		else if ((cv::mean(img.row(i))[0] + cv::mean(img.row(i))[1] + cv::mean(img.row(i))[2]) < minBG) {
			minBG = (cv::mean(img.row(i))[0] + cv::mean(img.row(i))[1] + cv::mean(img.row(i))[2]);
		}
	}
	double EPSILON = (maxBG - minBG);
	int y = 0;
	double avg1 = (cv::mean(img.row(y))[0] + cv::mean(img.row(y))[1] + cv::mean(img.row(y))[2]);
	double avg2 = (cv::mean(img.row(y+20))[0] + cv::mean(img.row(y+20))[1] + cv::mean(img.row(y+20))[2]);
	 
	while ((cv::abs(avg1 - avg2) < EPSILON) && y < img.rows/2) {
		y++;
		avg1 = (cv::mean(img.row(y))[0] + cv::mean(img.row(y))[1] + cv::mean(img.row(y))[2]);
		avg2 = (cv::mean(img.row(y + 30))[0] + cv::mean(img.row(y + 30))[1] + cv::mean(img.row(y + 30))[2]);
	}
	if (y > 800)y = 800;
	//Create Background-circle
	cv::Mat1b mask(img.size(), 255);
	circle(mask, Point(img.cols / 2, img.rows / 2), (img.rows - 2*y)/2 * (1.2 + bg), Scalar(0, 0, 0), FILLED);


	//cut the Background
	cv::subtract(sure_bg, mask, substract);
	
	//Mat negativBG, gbMask;
	//negativBG = 255 - substract;
	//cv::threshold(negativBG, bgMask, 1, 128, THRESH_BINARY);

	cv::bitwise_and(img, img, finalIMG, substract);

	//create Background-IMG
	img.copyTo(finalBG, mask);

	if (show) {
		char* img_window = "Final-Background";
		namedWindow(img_window, WINDOW_KEEPRATIO);
		imshow(img_window, finalBG);

		char* img_window2 = "substract(sure_bg, mask)";
		namedWindow(img_window2, WINDOW_KEEPRATIO);
		imshow(img_window2, substract);

		char* img_window3 = "Background-Mask";
		namedWindow(img_window3, WINDOW_KEEPRATIO);
		imshow(img_window3, mask);

		char* img_window4 = "Final-Foreground";
		namedWindow(img_window4, WINDOW_KEEPRATIO);
		imshow(img_window4, finalIMG);
	}
	foreground_const = finalIMG;
	background_const = finalBG;
	mask_const = substract;
	bgmask_const = mask;
}



//Show Histogram
void CVController::histo(std::string path) {
	Mat src, dst;

	/// Load image
	src = CVController::readImage(path);

	if (!src.data){
		return;
	}

	/// Separate the image in 3 places ( B, G and R )
	std::vector<Mat> bgr_planes;
	split(src, bgr_planes);

	/// Establish the number of bins
	int histSize = 256;

	/// Set the ranges ( for B,G,R) )
	float range[] = { 0, 256 };
	const float* histRange = { range };

	bool uniform = true; bool accumulate = false;

	Mat b_hist, g_hist, r_hist;

	/// Compute the histograms:
	calcHist(&bgr_planes[0], 1, 0, Mat(), b_hist, 1, &histSize, &histRange, uniform, accumulate);
	calcHist(&bgr_planes[1], 1, 0, Mat(), g_hist, 1, &histSize, &histRange, uniform, accumulate);
	calcHist(&bgr_planes[2], 1, 0, Mat(), r_hist, 1, &histSize, &histRange, uniform, accumulate);

	// Draw the histograms for B, G and R
	int hist_w = 512; int hist_h = 400;
	int bin_w = cvRound((double)hist_w / histSize);

	Mat histImage(hist_h, hist_w, CV_8UC3, Scalar(0, 0, 0));

	/// Normalize the result to [ 0, histImage.rows ]
	normalize(b_hist, b_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());
	normalize(g_hist, g_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());
	normalize(r_hist, r_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());

	/// Draw for each channel
	for (int i = 1; i < histSize; i++){
		line(histImage, Point(bin_w * (i - 1), hist_h - cvRound(b_hist.at<float>(i - 1))),
			Point(bin_w * (i), hist_h - cvRound(b_hist.at<float>(i))),
			Scalar(255, 0, 0), 2, 8, 0);
		line(histImage, Point(bin_w * (i - 1), hist_h - cvRound(g_hist.at<float>(i - 1))),
			Point(bin_w * (i), hist_h - cvRound(g_hist.at<float>(i))),
			Scalar(0, 255, 0), 2, 8, 0);
		line(histImage, Point(bin_w * (i - 1), hist_h - cvRound(r_hist.at<float>(i - 1))),
			Point(bin_w * (i), hist_h - cvRound(r_hist.at<float>(i))),
			Scalar(0, 0, 255), 2, 8, 0);
	}

	/// Display
	namedWindow("calcHist Demo", WINDOW_AUTOSIZE);
	imshow("calcHist Demo", histImage);
}


//GrabCut()
void CVController::foregroundExtraction(std::string path) {
	/// Source image to display
	Mat img_display;
	const cv::Mat img = CVController::readImage(path);
	img.copyTo(img_display);
	//cv::Mat img(cv::Size(2752, 2208), CV_8UC1);
	//cv::resize(img_in, img, cv::Size(2752, 2208), CV_8UC1);

	cv::Mat bgd, fgd;
	cv::Mat1b mask(img.rows, img.cols);

	mask.setTo(cv::GC_BGD);
	circle(mask, Point(img.cols / 2, img.rows / 2), img.cols / 5, GC_PR_FGD, FILLED);

	grabCut(img, mask, Rect(), bgd, fgd, 1, GC_INIT_WITH_MASK);

	// let's get all foreground and possible foreground pixels
	cv::Mat1b mask_fgpf = (mask == cv::GC_FGD) | (mask == cv::GC_PR_FGD);
	// and copy all the foreground-pixels to a temporary image
	cv::Mat3b tmp = cv::Mat3b::zeros(img.rows, img.cols);
	cv::Mat3b tmp2 = cv::Mat3b::zeros(img.rows, img.cols);
	img.copyTo(tmp, mask_fgpf);
	img.copyTo(tmp2, ~mask_fgpf);
	// show it
	//cv::imshow("foreground", tmp);

	//char* bgd_window = "Background";
	//char* fgd_window = "Foreground";
	char* img_window = "img_foreground";
	char* img2_window = "img_background";
	//namedWindow(bgd_window, WINDOW_KEEPRATIO);
	//namedWindow(fgd_window, WINDOW_KEEPRATIO);
	namedWindow(img_window, WINDOW_KEEPRATIO);
	namedWindow(img2_window, WINDOW_KEEPRATIO);
	//imshow(bgd_window, bgd);
	//imshow(fgd_window, fgd);
	imshow(img_window, tmp);
	imshow(img2_window, img_display); //tmp2
}