#ifndef GEOMETRYALGORITHM_H
#define GEOMETRYALGORITHM_H

#include <QtWidgets/QMainWindow>
#include "ui_geometryalgorithm.h"

class GeometryAlgorithm : public QMainWindow
{
	Q_OBJECT

public:
	GeometryAlgorithm(QWidget *parent = 0);
	~GeometryAlgorithm();

private:
	Ui::GeometryAlgorithmClass ui;
};

#endif // GEOMETRYALGORITHM_H
