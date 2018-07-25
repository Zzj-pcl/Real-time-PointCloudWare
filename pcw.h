#ifndef PCW_H
#define PCW_H

#include <QtWidgets/QMainWindow>
#include "ui_pcw.h"

//Qt
#include <QMainWindow>
#include <QString>
#include <QDialog>
#include <QDir>
#include <QActionGroup>

//system
#include <string>

#include "PointCloud.h"

class QMdiArea;
class QSignalMapper;
class QMdiSubWindow;
class QToolButton;
class QAction;
class vtkWindows;

class PCW : public QMainWindow
{
	Q_OBJECT

public:
	PCW(QWidget *parent = 0);
	~PCW();

	PointCloud Pcloud;
	std::vector<PointCloud> pcloud_vector;  //存储了数据类型为PointT的一个动态数组对于一个包含了XYZ数据的点云，points是包含了元素为pcl::PointXYZ一个vector。 

	//可视化(智能指针)
	boost::shared_ptr<pcl::visualization::PCLVisualizer> pclView;
	pcl::visualization::PCLVisualizerInteractorStyle viewInteractor; //自定义点云可视化交互方式

public:
	std::string getFileName(std::string file_name);

	void ConnectAction();
	void InitpclView();
	void UpadatePointsCloud();
	void ClearPcloud_vector();
	void setPCopacity(unsigned int a); //设置点云显示不透明

public slots:
	vtkWindows* vtkView();
	void glView();
	void LoadOneFile();
	void LoadManyFile();
	void SaveFile();

	void lasTransformtxt();
	void lasTransformpcd();
	void setActiveSubWindow(QWidget* window);

	virtual void freezeUI(bool state); //ui显示
	void updateMenu(); //更新菜单
	void on3DViewActivated(QMdiSubWindow*);

protected:
	/***MDI AREA***/
	QMdiArea* m_mdiArea;
	QSignalMapper* m_windowMapper;
	QMdiSubWindow* getMDISubWindow(vtkWindows* win);

	bool m_uiFrozen;

private:
	Ui::PCWClass ui;
};

#endif // PCW_H
