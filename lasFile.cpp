#include "lasFile.h"

//laslib
#include <liblas/liblas.hpp>
#include <liblas/point.hpp>
#include <liblas/reader.hpp>
#include <liblas/writer.hpp>
#include <liblas/factory.hpp>

//pcl
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>

//system
#include <string.h>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <vector>
#include <ios>

//qt
#include <QFileDialog>
#include <QSettings>
#include <QMessageBox>
#include <QApplication>
#include <QFileInfo>
#include <QSharedPointer>

using namespace std;
static const QString s_CurrentPath("currentPath");
QSettings settings;

lasFile::lasFile()
{

}

lasFile::~lasFile()
{

}

void lasFile::lasRead()
{
	QString filename;
	std::ifstream ifs;
	ifs.open(filename.toStdString(), std::ios::in | std::ios::binary);
	if (ifs.fail())
		return;
	liblas::Reader reader(liblas::ReaderFactory().CreateWithStream(ifs));
	unsigned numberOfPoints = 0;
	std::vector<std::string> dimensions; //las���ƵĹ�ģ

	try
	{
		liblas::Header const& header = reader.GetHeader();
		//QMessageBox::about(QString("[LAS] % -signature: $2").arg(filename).arg(header.GetFileSignature).c_str(),tr(""),tr(""));
		
		const liblas::Schema& schema = header.GetSchema(); //ͼ��
		
		{
			liblas::IndexMap const& map = schema.GetDimensions();
			liblas::index_by_position const& position_index = map.get<liblas::position>();
			liblas::index_by_position::const_iterator it = position_index.begin();
			while (it != position_index.end())
			{
				dimensions.push_back(it->GetName());
				it++;
			}
		}
		numberOfPoints = header.GetPointRecordsCount(); //��ȡ�ܵ�����
	}

	catch (...)
	{
		ifs.close();
		return;
	}

	if (numberOfPoints == 0)
	{
		ifs.close();
		return;
	}
}

void lasFile::las2txt()
{
	QString currentPath = settings.value(s_CurrentPath, QApplication::applicationDirPath()).toString();
	QString FileName = QFileDialog::getOpenFileName(this,
		QString::fromLocal8Bit("ѡ��las�ļ�"),
		currentPath,
		tr("LAS lidar (*.Las *.Laz);;"));

	if (FileName.isEmpty())
	{
		return;
	}

	std::string inFileName = FileName.toStdString();
	std::ifstream ifs;
	ifs.open(inFileName, std::ios::in | std::ios::binary);
	if (ifs.fail())
	{
		QMessageBox::critical(NULL, "error", QString::fromLocal8Bit("�޷��򿪴�las�ļ�"), QMessageBox::Ok);
		return;
	}

	liblas::ReaderFactory f;
	liblas::Reader reader = f.CreateWithStream(ifs);                                                //
	liblas::Header const& header = reader.GetHeader();                                              //las�ļ�ͷ���ݿ���Ϣ

	header.GetPointRecordsCount(); //��¼�ĵ�����Ϣ,�������Ϣ�Ƚ���Ҫ�����г����ˣ�������˼Ҳ�ȽϺ����
	header.GetFileSignature();

	std::setiosflags(std::ios::fixed); //������ʾС�����9λС����
	std::setprecision(9); 
	header.GetScaleX();
	header.GetScaleY();
	header.GetScaleZ();
	header.GetOffsetX();
	header.GetOffsetY();
	header.GetOffsetZ();
	header.GetMaxX();
	header.GetMaxY();
	header.GetMaxZ();
	header.GetMinX();
	header.GetMinY();
	header.GetMinZ();

	reader.ReadPointAt(0);                                                                          //�㼯��¼���е���Ϣ
	liblas::Point const& p = reader.GetPoint();
	liblas::Color const& rgb = p.GetColor();
	rgb.GetRed();
	rgb.GetGreen();
	rgb.GetBlue();

	p.GetX();
	p.GetY();
	p.GetZ();
	p.GetIntensity();
	p.GetReturnNumber();
	p.GetNumberOfReturns();
	p.GetClassification();
	p.GetScanDirection();
	p.GetFlightLineEdge();
    p.GetScanAngleRank();
	p.GetPointSourceID();
	p.GetTime();

	char path_buffer[_MAX_PATH];                                                                    //��ȡ�ļ�·��
	char drive[_MAX_DRIVE];
	char dir[_MAX_DIR];
	char fname[_MAX_FNAME];
	char ext[_MAX_EXT];
	_splitpath(inFileName.c_str(), drive, dir, fname, ext);
	std::string driveStr(drive), dirStr(dir);
	std::string outFilePath(driveStr + dirStr);

	std::string currentFileName(FileName.toStdString());
	std::ofstream ofile;
	ofile.open(outFilePath + currentFileName);
	
	int num(0), count(0);
	reader.Seek(0);
	while (reader.ReadNextPoint())   //ÿ��1000������ݽ���һ�α���
	{
		liblas::Point const& p = reader.GetPoint();

		ofile << std::setiosflags(std::ios::fixed);
		ofile << std::setprecision(9) 
			<< rgb.GetRed()
			<< rgb.GetGreen() 
			<< rgb.GetBlue()
			<< p.GetX() << " " 
			<< p.GetY() << " "
			<< p.GetZ() << " "
			<< p.GetIntensity() << " "
			<< p.GetReturnNumber()<< " "
			<< p.GetNumberOfReturns() << " "
			<< p.GetClassification() << " "
			<< p.GetScanDirection() << " " 
			<< p.GetFlightLineEdge() << " " 
			<< p.GetScanAngleRank() << " "
			<< p.GetPointSourceID() << " " 
			<< p.GetTime() 
			<< std::endl;

		if (++num % 10000000 == 0)
		{
			++count;
			ofile.close();
			std::stringstream ss;
			std::string currentFileName;
			ss << count;
			ss >> currentFileName;
			ofile.open(outFilePath + currentFileName + ".txt");
		}
	}
	ofile.close();
	QMessageBox::about(this, QString::fromLocal8Bit("��ʾ��Ϣ"), QString::fromLocal8Bit("ת���ɹ�"));
}

void lasFile::las2pcd()
{	
	QString currentPath = settings.value(s_CurrentPath, QApplication::applicationDirPath()).toString();
	QString FileName = QFileDialog::getOpenFileName(this,
		QString::fromLocal8Bit("ѡ��las�ļ�"),
		currentPath,
		tr("LAS lidar (*.Las *.Laz);;"));

	if (FileName.isEmpty())
	{
		return;
	}

	const char* lasfile;
	QByteArray lasExchange = FileName.toLocal8Bit();
	char* p1 = lasExchange.data();
	const char* pcdfile;
	QByteArray pcdExchange = FileName.toLocal8Bit();
	char* p2 = pcdExchange.data();

	std::ifstream ifs;
	ifs.open(p1, std::ios::in | std::ios::binary);

	liblas::ReaderFactory f;
	liblas::Reader reader = f.CreateWithStream(ifs);
	liblas::Header const& header = reader.GetHeader();

	pcl::PointCloud<pcl::PointXYZ>::Ptr pointCloudPtr(new pcl::PointCloud<pcl::PointXYZ>);
	int count = header.GetPointRecordsCount();
	pointCloudPtr->resize(count);
	pointCloudPtr->width = 1;
	pointCloudPtr->height = count;
	pointCloudPtr->is_dense = false;

	int i = 0;
	while (reader.ReadNextPoint())
	{
		liblas::Point const& p = reader.GetPoint();
		pointCloudPtr->points[i].x = p.GetX();
		pointCloudPtr->points[i].y = p.GetY();
		pointCloudPtr->points[i].z = p.GetZ();
		++i;
	}
	pcl::io::savePCDFileASCII(p2, *pointCloudPtr);
}