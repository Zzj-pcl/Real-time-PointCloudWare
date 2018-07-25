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
	std::vector<PointCloud> pcloud_vector;  //�洢����������ΪPointT��һ����̬�������һ��������XYZ���ݵĵ��ƣ�points�ǰ�����Ԫ��Ϊpcl::PointXYZһ��vector�� 

	//���ӻ�(����ָ��)
	boost::shared_ptr<pcl::visualization::PCLVisualizer> pclView;
	pcl::visualization::PCLVisualizerInteractorStyle viewInteractor; //�Զ�����ƿ��ӻ�������ʽ

public:
	std::string getFileName(std::string file_name);

	void ConnectAction();
	void InitpclView();
	void UpadatePointsCloud();
	void ClearPcloud_vector();
	void setPCopacity(unsigned int a); //���õ�����ʾ��͸��

public slots:
	vtkWindows* vtkView();
	void glView();
	void LoadOneFile();
	void LoadManyFile();
	void SaveFile();

	void lasTransformtxt();
	void lasTransformpcd();
	void setActiveSubWindow(QWidget* window);

	virtual void freezeUI(bool state); //ui��ʾ
	void updateMenu(); //���²˵�
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
