#include "StreptoGUI.h"
#include <QtWidgets/QApplication>
#include <qlabel.h>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	StreptoGUI w;
	w.show();
	return a.exec();
}
