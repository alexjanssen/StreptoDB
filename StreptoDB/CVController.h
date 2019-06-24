#pragma once

#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <QtWidgets\QGraphicsPixmapItem>
#include <opencv2/imgproc.hpp>

class CVController
{
public:
	CVController();
	~CVController();
	static QImage Mat2QImage(cv::Mat const&);
	static cv::Mat QImage2Mat(QImage const&);

private:

};

