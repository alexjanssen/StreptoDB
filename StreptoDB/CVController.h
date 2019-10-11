#pragma once

#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <QtWidgets\QGraphicsPixmapItem>
#include <opencv2/imgproc.hpp>
#include <vector>
//#include <string>

class CVController
{
public:
	CVController();
	~CVController();

	static QImage Mat2QImage(cv::Mat const&);
	static cv::Mat QImage2Mat(QImage const&);

	cv::Mat readImage(std::string path);

	double mean1(std::string path,int channel);
	double meanFG(int channel);
	double meanBG(int channel);
	double foregroundSize(double scale);

	double circFact(double scale, double area);

	int extractScale(std::string path);
	void foregroundExtraction(std::string path);
	void segmentation(std::string path, double, double,double,bool);
	void histo(std::string path);
private:

};

static cv::Mat foreground_const, background_const, mask_const, bgmask_const;

