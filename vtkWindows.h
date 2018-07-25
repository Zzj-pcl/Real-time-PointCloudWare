#ifndef VTKWINDOWS_H
#define VTKWINDOWS_H

#include <vtkAutoInit.h>
VTK_MODULE_INIT(vtkRenderingOpenGL2);
VTK_MODULE_INIT(vtkInteractionStyle);
#include <vtkRenderWindow.h>
//Qt
#include <QVTKWidget.h>
//#include <QObject>
//VTK
#pragma once
#include <vtkActorCollection.h>
#include <vtkActor2DCollection.h>
#include <vtkAppendPolyData.h>
#include <vtkAppendFilter.h>
#include <vtkCameraActor.h>
#include <vtkCellArray.h>
#include <vtkCellData.h>
#include <vtkCommand.h>
#include <vtkConeSource.h>
#include <vtkCubeSource.h>
#include <vtkDataSetMapper.h>
#include <vtkHull.h>
#include <vtkInformation.h>
#include <vtkInformationStringKey.h>
#include <vtkInteractorStyleTrackballCamera.h>
#include <vtkLODActor.h>
#include <vtkMath.h>
#include <vtkMatrix4x4.h>
#include <vtkMutexLock.h>
//#include <vtkObjectFactory.h>
#include <vtkTextActor.h>
#include <vtkRectilinearGrid.h>
#include <vtkUnsignedCharArray.h>
#include <vtkInteractorStyleRubberBand3D.h>
#include <vtkParallelCoordinatesInteractorStyle.h>
#include <vtkLight.h>
#include <vtkImageData.h>  
#include <vtkInteractorStyleImage.h>  
#include <vtkTIFFWriter.h>  
#include <vtkSmartPointer.h>  
#include <vtkImageCanvasSource2D.h>  
#include <vtkRenderWindowInteractor.h>   
#include <vtkImageActor.h>  
#include <vtkImageMapper3D.h>  
#include <vtkOrientationMarkerWidget.h>
#include <vtkTIFFReader.h>  
#include <vtkPolyDataMapper.h> 
#include <vtkPolyData.h>
#include <vtkSphereSource.h>
#include <vtkAxesActor.h>
#include <vtkCamera.h>
#include <vtkCoordinate.h>
#include <vtkViewport.h>
#include <vtkSmartPointer.h>
#include <vtkPropAssembly.h>
#include <vtkActor.h>
#include <vtkActor2D.h>
#include <vtkProperty2D.h> 
#include <vtkDelaunay2D.h>
#include <vtkCaptionActor2D.h> 
#include <vtkRenderer.h>
#include <vtkProperty.h>
#include <vtkTransform.h>
//system
#include <set>
#include <list>

class vtkWindows : public QVTKWidget
{
	Q_OBJECT

public:
	vtkWindows(QWidget *parent = 0,
		QVTKWidget* shareWidget = 0,
		bool silentInitialization = false);
	 ~vtkWindows();

protected:
	int v_uniqueID;
	int v_Width;
	int v_Height;
	bool v_silentInitialization;
};

#endif // VTKWINDOWS_H
