#include "vtkWindows.h"

//QT
#include <QtGui>
#include <QWheelEvent>
#include <QElapsedTimer>
#include <QSettings>
#include <QApplication>

//System
#include <string.h>
#include <math.h>
#include <algorithm>

static int v_WindowNumber = 0;

vtkWindows::vtkWindows(QWidget *parent,
	QVTKWidget* shareWidget,
	bool silentInitialization)
	: QVTKWidget(parent)
	//, v_uniqueID(v_WindowNumber)
	, v_Width(0)
	, v_Height(0)
	, v_silentInitialization(silentInitialization)
{
	setWindowTitle(QString("vtk 3D View").arg(v_uniqueID));

}

vtkWindows::~vtkWindows()
{

}
