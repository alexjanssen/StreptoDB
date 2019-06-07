#ifndef Image_HEADER
#define Image_HEADER

#include <string>
#include <QtWidgets\QGraphicsPixmapItem>
using namespace std;


class Image
{
	
	// Access specifier 
public:
	// Data Members 
	int image_id;
	QImage image_preview;
	string date;
	double imagesize;
	double resolution;
	int broth_id;
	int group_id;
	string filePath;

	
};


#endif

