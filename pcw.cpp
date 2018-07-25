#include "pcw.h"

//QT
#include <QtGui>
#include <QMdiArea>
#include <QSignalMapper>
#include <QMdiSubWindow>
#include <QLCDNumber>
#include <QFileDialog>
#include <QActionGroup>
#include <QProcess>
#include <QSettings>
#include <QMessageBox>
#include <QElapsedTimer>
#include <QInputDialog>
#include <QTextStream>
#include <QColorDialog>

//System
#include <math.h>
#include <assert.h>
#include <cfloat>
#include <string.h>
#include <string>  
#include <io.h>  
#include <fstream>				
#include <iostream> 		
#include <math.h>  
#include <vector>
#include <ctime>
#include <time.h>
#include <vector>
#include <exception>

#include "lasFile.h"
#include "vtkWindows.h"
#include "FileIO.h"


//设置文件对话框的组名
static const QString s_LoadFile					("LoadFile");
static const QString s_SaveFile					("SaveFile");
static const QString s_MainWinGeom				("mainWindowGeometry");
static const QString s_MainWinState				("mainWindowState");
static const QString s_CurrentPath				("currentPath");
static const QString s_SelectedFilter			("selectedFilter");
static const QString s_SelectedFilterCloud		("selectedFilterCloud");
static const QString s_SelectedFilterMesh		("selectedFilterMesh");
static const QString s_DuplicatePointsGroup	    ("duplicatePoints");
static const QString s_DuplicatePointsMinDist	("minDist");

#define VER_NUM "1.0"
#define SUB_VER "" 

int status = -1; //pcl_io加载点云文件的返回值

QString GetVersion(bool full)
{
	QString verStr = QString("%1.%2").arg(VER_NUM).arg(SUB_VER);
//	QString arch = "64 bits";
//#if defined(ENV_64)	
//#endif
//	if (full)
//	{
//		QString platform = "Windows";
//#if defined(WINDOWS)	;
//#endif
//		verStr += QString(" [%1 %2]").arg(platform).arg(arch);
//	}
//	else
//	{
//		verStr += QString(" [%1]").arg(arch);
//	}
	return verStr;
};


PCW::PCW(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	InitpclView();

	QSettings setting;
	restoreGeometry(setting.value(s_MainWinGeom).toByteArray());

	setWindowTitle(QString("PointCloudWare v") + GetVersion(false));

	//MDI Area
	//m_mdiArea = new QMdiArea(this);
	//setCentralWidget(m_mdiArea);
	//connect(m_mdiArea, SIGNAL(subWindowActivated(QMdiSubWindow*)), this, SLOT(updateMenu()));
	//connect(m_mdiArea, SIGNAL(subWindowActivated(QMdiSubWindow*)), this, SLOT(on3DViewActivated(QMdiSubWindow*)));

	//Window Mapper
	m_windowMapper = new QSignalMapper(this);
	connect(m_windowMapper, SIGNAL(mapped(QWidget*)), this, SLOT(setActiveSubWindow(QWidget*)));

	ConnectAction();

	freezeUI(false);

	showMaximized();
	QMainWindow::statusBar()->showMessage(QString("Ready"));
	QMainWindow::statusBar()->showMessage("PointCloudWare started!");

	restoreState(setting.value(s_MainWinState).toByteArray());
}

PCW::~PCW()
{
	assert(m_mdiArea);
	m_mdiArea->disconnect();

	//if (m_mdiArea)
	//{

	//	QList<QMdiSubWindow*> subWindowList = m_mdiArea->subWindowList();
	//	for (int i = 0; i<subWindowList.size(); ++i)
	//		static_cast<vtkWindows*>(subWindowList[i]->widget())->setSceneDB(0);
	//}

	//m_mdiArea->closeAllSubWindows();
}

void PCW::freezeUI(bool state)
{
	ui.mainToolBar->setDisabled(state);

	//ui.Dockable->setDisabled(state);
	//ui.menubar->setDisabled(state);

	if (state)
	{
		//ui.menuEdit->setDisabled(true);
		//ui.menuTools->setDisabled(true);
	}
	else
	{
		//updateMenus();
	}

	m_uiFrozen = state;
}

void PCW::updateMenu()
{

}

void PCW::on3DViewActivated(QMdiSubWindow* mdiWin)
{
	vtkWindows* win = mdiWin ? static_cast<vtkWindows*>(mdiWin->widget()) : 0;
	if (win)
	{
		//updateViewModePopUpMenu(win);
		//updatePivotVisibilityPopUpMenu(win);
	}
}

void PCW::ConnectAction()
{
	/*** MAIN MENU  主界面***/
	//文件
	connect(ui.actionOpenOne, SIGNAL(triggered()), this, SLOT(LoadOneFile()));

	/***	窗口	 ***/
	connect(ui.action_newVTK, SIGNAL(triggered()), this, SLOT(vtkView()));
	//connect(ui.action_newGL, SIGNAL(triggered()), this, SLOT(glWindow()))

	//**************数据管理*****************/
	//格式转换
	connect(ui.action_las2txt, SIGNAL(triggered()), this, SLOT(lasopenFile()));
	connect(ui.action_las2pcd, SIGNAL(triggered()), this, SLOT(lasTransformpcd()));
}

void PCW::setActiveSubWindow(QWidget* window)
{
	if (!window || !m_mdiArea)
		return;
	m_mdiArea->setActiveSubWindow(qobject_cast<QMdiSubWindow *>(window));
}

//选择并加载点云文件
void PCW::LoadOneFile()
{
	QSettings settings;
	settings.beginGroup(s_LoadFile);
	QString currentPath = settings.value(s_CurrentPath, QApplication::applicationDirPath()).toString();
	int currentOpenDlgFilter = settings.value(s_SelectedFilter, "LAS").toInt();
	
	QString filters;
	filters.append(QString(FILE_TYPE_FILTERS[UNKNOWN_FILE]) + ";;");
	filters.append(QString(FILE_TYPE_FILTERS[LAS]) + ";;");
	filters.append(QString(FILE_TYPE_FILTERS[DXF]) + ";;");
	filters.append(QString(FILE_TYPE_FILTERS[OBJ]) + ";;");
	filters.append(QString(FILE_TYPE_FILTERS[TXT]) + ";;");
	filters.append(QString(FILE_TYPE_FILTERS[ASCII]) + ";;");
	filters.append(QString(FILE_TYPE_FILTERS[DGN]) + ";;");
	filters.append(QString(FILE_TYPE_FILTERS[PDS]) + ";;");
	filters.append(QString(FILE_TYPE_FILTERS[PDMS]) + ";;");
	filters.append(QString(FILE_TYPE_FILTERS[PCD]) + ";;");

	QString selectFilter = FILE_TYPE_FILTERS[currentOpenDlgFilter];

	QStringList selectFiles = QFileDialog::getOpenFileNames(this,
		QString::fromLocal8Bit("选择文件"),
		currentPath,
		filters,
		&selectFilter, 
		QFileDialog::DontUseNativeDialog
//#ifdef _RELEASE	
//#endif
		);

	if (selectFiles.isEmpty())
	{
		QMessageBox message(QMessageBox::Warning, "Title", QString::fromLocal8Bit("未选择文件！"));
		return;
	}

	FILE_TYPES Type = UNKNOWN_FILE;
	for (unsigned i = 0; i < static_cast<unsigned>(FILE_TYPES_COUNT); ++i)
	{
		if (selectFilter == QString(FILE_TYPE_FILTERS[i]))
		{
			Type = FILE_TYPES_ENUMS[i];
			break;
		}
	}


	for (int i = 0; i != selectFiles.size(); i++)
	{
		Pcloud.cloudT.reset(new PointCloudT);
		QString filename = selectFiles[i];
		std::string file_name = filename.toStdString();
	
		if (filename.endsWith(".pcd", Qt::CaseInsensitive))
		{
			status = pcl::io::loadPCDFile(filename.toStdString(), *(Pcloud.cloudT));
		}
		else
			if (filename.endsWith(".ply"), Qt::CaseInsensitive)
		{
			status=pcl::io::loadPLYFile(file_name, *(Pcloud.cloudT));
		}
		else
			if (filename.endsWith(".obj"), Qt::CaseInsensitive)
		{
			status=pcl::io::loadOBJFile(file_name, *(Pcloud.cloudT));
		}
		
		if (status != 0)
		{
			QMessageBox::critical(this, tr("error"), tr("error"));
			return;
		}
		setPCopacity(255);
		pcloud_vector.push_back(Pcloud); //将点云导入点云容器
		long total_points = 0;
		total_points += Pcloud.cloudT->points.size();
	}

	UpadatePointsCloud();

	currentPath = QFileInfo(selectFiles[0]).absolutePath();
	settings.setValue(s_CurrentPath, currentPath);
	settings.setValue(s_SelectedFilter, currentOpenDlgFilter);
	settings.endGroup();
}

void PCW::ClearPcloud_vector()
{
	pcloud_vector.clear();
}

void PCW::setPCopacity(unsigned int a)
{
	for (size_t i = 0; i < Pcloud.cloudT->size(); i++)
	{
		Pcloud.cloudT->points[i].a= a;
	}
}

void PCW::UpadatePointsCloud()
{
	for (int i = 0; i != pcloud_vector.size(); i++)
	{
		pclView->addPointCloud(pcloud_vector[i].cloudT, "cloud" + QString::number(i).toStdString());
		pclView->updatePointCloud(pcloud_vector[i].cloudT, "cloud" + QString::number(i).toStdString());
	}
	pclView->resetCamera();
}

//提取全路径中的文件名（带后缀）
std::string getFileName(std::string file_name)
{
	std::string subname;
	for (auto i = file_name.end() - 1; *i != '/'; i--)
	{
		subname.insert(subname.begin(), *i);
	}
	return subname;
}

void PCW::LoadManyFile()
{

}

void PCW::glView()
{
	

}

QMdiSubWindow* PCW::getMDISubWindow(vtkWindows* win)
{
	QList<QMdiSubWindow*> subWindowList = m_mdiArea->subWindowList();
	for (int i = 0; i<subWindowList.size(); ++i)
		if (static_cast<vtkWindows*>(subWindowList[i]->widget()) == win)
			return subWindowList[i];
	return 0;
}

//初始化pclView的有关事件
void PCW::InitpclView()
{	
	Pcloud.cloudT.reset(new PointCloudT); 
	pclView.reset(new pcl::visualization::PCLVisualizer("vtkView", false)); 
	pcl::visualization::PointCloudColorHandlerCustom<pcl::PointXYZ> cloud_color(Pcloud.cloudxyz.makeShared(), 255, 255, 255);
	pclView->setBackgroundColor(0, 0, 0);
	pclView->addCoordinateSystem(0.1);
	pclView->resetCamera();
}

vtkWindows* PCW::vtkView()
{
	//assert(m_mdiArea);

	//MDI Area
	m_mdiArea = new QMdiArea(this);
	setCentralWidget(m_mdiArea);
	connect(m_mdiArea, SIGNAL(subWindowActivated(QMdiSubWindow*)), this, SLOT(updateMenus()));
	connect(m_mdiArea, SIGNAL(subWindowActivated(QMdiSubWindow*)), this, SLOT(on3DViewActivated(QMdiSubWindow*)));

	QList<QMdiSubWindow*> subWindowList = m_mdiArea->subWindowList();
	vtkWindows* otherWin = 0;
	if (!subWindowList.isEmpty())
	{
		otherWin = static_cast<vtkWindows*>(subWindowList[0]->widget());
	}

	vtkWindows *View3D = new vtkWindows(this,otherWin);
	View3D->setMinimumSize(400, 300);
	View3D->resize(400, 300);

	View3D->SetRenderWindow(pclView->getRenderWindow());	
	pclView->setupInteractor(View3D->GetInteractor(), View3D->GetRenderWindow());
	View3D->update();
	View3D->setAttribute(Qt::WA_DeleteOnClose);
	m_mdiArea->addSubWindow(View3D);

	QMainWindow::statusBar()->showMessage(QString("vtk 3D View"), 2000);

	View3D->showMaximized();
	return View3D;
}

void PCW::SaveFile()
{
//	size_t selNum = m_selectedEntities.size();
//	if (selNum == 0)
//		return;
//
//	QSettings settings;
//	settings.beginGroup(s_SaveFile);
//	QString currentPath = settings.value(s_CurrentPath, QApplication::applicationDirPath()).toString();
//	int currentCloudSaveDlgFilter = settings.value(s_SelectedFilterCloud, BIN).toInt();
//	int currentMeshSaveDlgFilter = settings.value(s_SelectedFilterMesh, PLY).toInt();
//
//	ccHObject clouds("clouds");
//	ccHObject meshes("meshes");
//	ccHObject images("images");
//	ccHObject polylines("polylines");
//	ccHObject other("other");
//	ccHObject otherSerializable("serializable");
//	ccHObject::Container entitiesToSave;
//	entitiesToSave.insert(entitiesToSave.begin(), m_selectedEntities.begin(), m_selectedEntities.end());
//	while (!entitiesToSave.empty())
//	{
//		ccHObject* child = entitiesToSave.back();
//		entitiesToSave.pop_back();
//
//		if (child->isA(CC_TYPES::HIERARCHY_OBJECT))
//		{
//			for (unsigned j = 0; j<child->getChildrenNumber(); ++j)
//				entitiesToSave.push_back(child->getChild(j));
//		}
//		else
//		{
//			//we put entity in the container corresponding to its type
//			ccHObject* dest = 0;
//			if (child->isA(CC_TYPES::POINT_CLOUD))
//				dest = &clouds;
//			else if (child->isKindOf(CC_TYPES::MESH))
//				dest = &meshes;
//			else if (child->isKindOf(CC_TYPES::IMAGE))
//				dest = &images;
//			else if (child->isKindOf(CC_TYPES::POLY_LINE))
//				dest = &polylines;
//			else if (child->isSerializable())
//				dest = &otherSerializable;
//			else
//				dest = &other;
//
//			assert(dest);
//
//			//we don't want double insertions if the user has clicked both the father and child
//			if (!dest->find(child->getUniqueID()))
//				dest->addChild(child, ccHObject::DP_NONE);
//		}
//	}
//
//	bool hasCloud = (clouds.getChildrenNumber() != 0);
//	bool hasMesh = (meshes.getChildrenNumber() != 0);
//	bool hasImage = (images.getChildrenNumber() != 0);
//	bool hasPolylines = (polylines.getChildrenNumber() != 0);
//	bool hasSerializable = (otherSerializable.getChildrenNumber() != 0);
//	bool hasOther = (other.getChildrenNumber() != 0);
//
//	int stdSaveTypes = static_cast<int>(hasCloud)
//		+static_cast<int>(hasMesh)
//		+static_cast<int>(hasImage)
//		+static_cast<int>(hasPolylines)
//		+static_cast<int>(hasSerializable);
//	if (stdSaveTypes == 0)
//	{
//		ccConsole::Error("Can't save selected entity(ies) this way!");
//		return;
//	}
//
//	//we set up the right file filters, depending on the selected
//	//entities shared type (cloud, mesh, etc.).
//	QString filters;
//
//	//From now on, BIN format handles about anyhting!
//	filters.append(QString(CC_FILE_TYPE_FILTERS[BIN]) + ";;");
//
//	ccHObject* toSave = 0;
//	QString selectedFilter = CC_FILE_TYPE_FILTERS[BIN];
//
//	//if we only have one type of entity selected, then we can let the user choose specific formats
//	if (stdSaveTypes == 1)
//	{
//		if (hasCloud)
//		{
//			toSave = &clouds;
//			selectedFilter = CC_FILE_TYPE_FILTERS[currentCloudSaveDlgFilter];
//
//			//add cloud output file filters
//			filters.append(QString(CC_FILE_TYPE_FILTERS[ASCII]) + ";;");
//#ifdef CC_E57_SUPPORT
//			filters.append(QString(CC_FILE_TYPE_FILTERS[E57]) + ";;");
//#endif
//			if (clouds.getChildrenNumber() == 1)
//			{
//				filters.append(QString(CC_FILE_TYPE_FILTERS[PLY]) + ";;");
//				filters.append(QString(CC_FILE_TYPE_FILTERS[VTK]) + ";;");
//#ifdef CC_LAS_SUPPORT
//				filters.append(QString(CC_FILE_TYPE_FILTERS[LAS]) + ";;");
//#endif
//				filters.append(QString(CC_FILE_TYPE_FILTERS[PN]) + ";;");
//				filters.append(QString(CC_FILE_TYPE_FILTERS[PV]) + ";;");
//			}
//			//TODO: POV files handling!
//			//filters.append(CC_FILE_TYPE_FILTERS[POV]);
//			//filters.append("\n");
//		}
//		else if (hasMesh)
//		{
//			if (meshes.getChildrenNumber() == 1)
//			{
//				toSave = &meshes;
//				selectedFilter = CC_FILE_TYPE_FILTERS[currentMeshSaveDlgFilter];
//
//				//add meshes output file filters
//				filters.append(QString(CC_FILE_TYPE_FILTERS[OBJ]) + ";;");
//				filters.append(QString(CC_FILE_TYPE_FILTERS[PLY]) + ";;");
//				filters.append(QString(CC_FILE_TYPE_FILTERS[VTK]) + ";;");
//				filters.append(QString(CC_FILE_TYPE_FILTERS[STL]) + ";;");
//				filters.append(QString(CC_FILE_TYPE_FILTERS[OFF]) + ";;");
//#ifdef CC_X3D_SUPPORT
//				filters.append(QString(CC_FILE_TYPE_FILTERS[X3D]) + ";;");
//#endif
//				filters.append(QString(CC_FILE_TYPE_FILTERS[MA]) + ";;");
//			}
//#ifdef CC_FBX_SUPPORT
//			filters.append(QString(CC_FILE_TYPE_FILTERS[FBX]) + ";;");
//#endif
//		}
//		else if (hasPolylines)
//		{
//#ifdef CC_DXF_SUPPORT
//			filters.append(QString(CC_FILE_TYPE_FILTERS[DXF]) + ";;");
//#endif
//			toSave = &polylines;
//		}
//		else if (hasImage)
//		{
//			if (images.getChildrenNumber()>1)
//			{
//				ccConsole::Warning("[MainWindow::saveFile] Only BIN format is able to store multiple images at once");
//			}
//			else
//			{
//				toSave = &images;
//
//				//add images output file filters
//				//we grab the list of supported image file formats (writing)
//				QList<QByteArray> formats = QImageWriter::supportedImageFormats();
//				//we convert this list into a proper "filters" string
//				for (int i = 0; i<formats.size(); ++i)
//					filters.append(QString("%1 image (*.%2);;").arg(QString(formats[i].data()).toUpper()).arg(formats[i].data()));
//			}
//		}
//	}
//
//	QString dir = currentPath + QString("/");
//	if (selNum == 1)
//	{
//		//hierarchy objects have generally as name: 'filename.ext (fullpath)'
//		//so we must only take the first part! (otherwise this type of name
//		//with a path inside perturbs the QFileDialog a lot ;))
//		QString defaultFileName(m_selectedEntities[0]->getName());
//		if (m_selectedEntities[0]->isA(CC_TYPES::HIERARCHY_OBJECT))
//		{
//			QStringList parts = defaultFileName.split(' ', QString::SkipEmptyParts);
//			if (parts.size() > 0)
//				defaultFileName = parts[0];
//		}
//
//		if (!QFileInfo(defaultFileName).suffix().isEmpty()) //we remove extension
//			defaultFileName = QFileInfo(defaultFileName).baseName();
//
//		if (!IsValidFileName(defaultFileName))
//		{
//			ccLog::Warning("[MainWindow::saveFile] First entity's name would make an invalid filename! Can't use it...");
//			defaultFileName = "project";
//		}
//
//		dir += defaultFileName;
//	}
//
//	QString selectedFilename = QFileDialog::getSaveFileName(this,
//		tr("Save file"),
//		dir,
//		filters,
//		&selectedFilter);
//
//	if (selectedFilename.isEmpty())
//		return;
//
//	//ignored items
//	if (hasOther)
//	{
//		ccConsole::Warning("[MainWindow::saveFile] The following selected entites won't be saved:");
//		for (unsigned i = 0; i<other.getChildrenNumber(); ++i)
//			ccConsole::Warning(QString("\t- %1s").arg(other.getChild(i)->getName()));
//	}
//
//	CC_FILE_ERROR result = CC_FERR_NO_ERROR;
//	//bin format
//	if (selectedFilter == QString(CC_FILE_TYPE_FILTERS[BIN]))
//	{
//		if (selNum == 1)
//			result = FileIOFilter::SaveToFile(m_selectedEntities[0], qPrintable(selectedFilename), BIN);
//		else
//		{
//			ccHObject::Container tempContainer;
//			RemoveSiblings(m_selectedEntities, tempContainer);
//
//			if (tempContainer.size())
//			{
//				ccHObject root;
//				for (size_t i = 0; i<tempContainer.size(); ++i)
//					root.addChild(tempContainer[i], ccHObject::DP_NONE);
//				result = FileIOFilter::SaveToFile(&root, qPrintable(selectedFilename), BIN);
//			}
//			else
//			{
//				ccLog::Warning("[MainWindow::saveFile] No selected entity could be saved!");
//				result = CC_FERR_NO_SAVE;
//			}
//		}
//
//		currentCloudSaveDlgFilter = BIN;
//	}
//	else if (toSave)
//	{
//		//ignored items
//		if (hasSerializable)
//		{
//			if (!hasOther)
//				ccConsole::Warning("[MainWindow::saveFile] The following selected entites won't be saved:"); //display this warning only if not already done
//			for (unsigned i = 0; i<otherSerializable.getChildrenNumber(); ++i)
//				ccConsole::Warning(QString("\t- %1").arg(otherSerializable.getChild(i)->getName()));
//		}
//
//		if (hasCloud || hasMesh)
//		{
//			CC_FILE_TYPES fType = UNKNOWN_FILE;
//			for (unsigned i = 0; i<static_cast<unsigned>(FILE_TYPES_COUNT); ++i)
//			{
//				if (selectedFilter == QString(CC_FILE_TYPE_FILTERS[i]))
//				{
//					fType = CC_FILE_TYPES_ENUMS[i];
//					break;
//				}
//			}
//
//			if (hasCloud)
//				currentCloudSaveDlgFilter = fType;
//			else if (hasMesh)
//				currentMeshSaveDlgFilter = fType;
//
//			result = FileIOFilter::SaveToFile(toSave->getChildrenNumber() > 1 ? toSave : toSave->getChild(0),
//				qPrintable(selectedFilename),
//				fType);
//		}
//		else if (hasPolylines)
//		{
//#ifdef CC_DXF_SUPPORT
//			result = FileIOFilter::SaveToFile(toSave,
//				qPrintable(selectedFilename),
//				DXF);
//#endif
//		}
//		else if (hasImage)
//		{
//			assert(images.getChildrenNumber() == 1);
//			ccImage* image = static_cast<ccImage*>(images.getChild(0));
//			if (!image->data().save(selectedFilename))
//				result = CC_FERR_WRITING;
//		}
//	}
//
//	if (result != CC_FERR_NO_ERROR)
//	{
//		FileIOFilter::DisplayErrorMessage(result, "saving", selectedFilename);
//	}
//	else
//	{
//		ccLog::Print(QString("[I/O] File '%1' saved successfully").arg(selectedFilename));
//	}
//
//	//we update current file path
//	currentPath = QFileInfo(selectedFilename).absolutePath();
//
//	settings.setValue(s_psCurrentPath, currentPath);
//	settings.setValue(s_psSelectedFilterCloud, static_cast<int>(currentCloudSaveDlgFilter));
//	settings.setValue(s_psSelectedFilterMesh, static_cast<int>(currentMeshSaveDlgFilter));
//	settings.endGroup();
//}
//
//void MainWindow::on3DViewActivated(QMdiSubWindow* mdiWin)
//{
//	ccGLWindow* win = mdiWin ? static_cast<ccGLWindow*>(mdiWin->widget()) : 0;
//	if (win)
//	{
//		updateViewModePopUpMenu(win);
//		updatePivotVisibilityPopUpMenu(win);
//	}
}

void PCW::lasTransformtxt()
{
	
}

void PCW::lasTransformpcd()
{
	
}

