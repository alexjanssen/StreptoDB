#ifndef Isolat_HEADER
#define Isolat_HEADER

#include <string>
#include <QtWidgets\QGraphicsPixmapItem>
using namespace std;


class Isolat
{
	
	// Access specifier 
public:
	// Data Members 
	int id;
	int id_intern;
	int id_group;
	int multiple_counter;
	string date;
	string scientific_name;
	string spore_color;
	string genome_link;
	QImage image_preview;
	bool siderophore_bool;
	int broth_id;
	int image_para_id;
	string locality;
};


#endif

