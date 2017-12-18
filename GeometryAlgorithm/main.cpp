#include "geometryalgorithm.h"
#include <QtWidgets/QApplication>
#include "Algorithm.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	Line2d line1 = PointToLine(Vector2D(0,0), Vector2D(3,2));
	Line2d line2 = PointToLine(Vector2D(6, 9), Vector2D(34, 90));
	Vector2D acoss;
	bool val = LineAcrossPoint(&acoss, line1, line2);
	GeometryAlgorithm w;
	w.show();
	return a.exec();
}
