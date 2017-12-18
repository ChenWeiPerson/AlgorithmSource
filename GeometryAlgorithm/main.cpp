#include "geometryalgorithm.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	GeometryAlgorithm w;
	w.show();
	return a.exec();
}
