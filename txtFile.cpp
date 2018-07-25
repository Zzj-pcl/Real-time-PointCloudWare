#include "txtFile.h"

//pcl
#include <pcl/io/pcd_io.h>  
#include <pcl/point_types.h>  

//system
#include <iostream>  
#include <fstream>

txtFile::txtFile()
{

}

txtFile::~txtFile()
{

}

int numofPoints(char* fname)
{
	int n = 0;
	int c = 0;
	FILE *fp;
	fp = fopen(fname, "r");
	do
	{
		c = fgetc(fp);
		if (c == '\n')
		{
			++n;
		}
	} 
	while (c != EOF);
	fclose(fp);
	return n;
}

//�ļ���
void txtFile::txt2pcd()
{
	int n = 0; //n�������ļ��е����      
	
	FILE *fp_1;
	fp_1 = fopen("cat.txt", "r");
	n = numofPoints("cat.txt"); //ʹ��numofPoints���������ļ��е����  
	//std::cout << "there are " << n << " points in the file..." << std::endl;
	
	//�½�һ�������ļ���Ȼ�󽫽ṹ�л�ȡ��xyzֵ���ݵ�����ָ��cloud�С�  
	pcl::PointCloud<pcl::PointXYZ> cloud;
	cloud.width = n;
	cloud.height = 1;
	cloud.is_dense = false;
	cloud.points.resize(cloud.width * cloud.height);
	
	//�����ƶ��벢�����½�����ָ���xyz      
	double x, y, z;
	int i = 0;
	while (3 == fscanf(fp_1, "%lf,%lf,%lf\n", &x, &y, &z))
	{
		//cout << x << " " << y << " " << z << endl;
		cloud.points[i].x = x;
		cloud.points[i].y = y;
		cloud.points[i].z = z;
		++i;
	}

	fclose(fp_1);
	//������ָ��ָ������ݴ���pcd�ļ�  
	pcl::io::savePCDFileASCII(".pcd", cloud);
	//std::cerr << "Saved " << cloud.points.size() << " data points to test_pcd.pcd." << std::endl;
}

//void txtFile::txt2pcd()
//{
//	/////����txt����
//	int number_Txt;
//	FILE *fp_txt;
//	tagPOINT_3D TxtPoint;
//	vector<tagPOINT_3D> m_vTxtPoints;
//	fp_txt = fopen("C:/Users/can/Desktop/PCL test/txt2pcd/test.txt", "r");
//
//	if (fp_txt)
//	{
//		while (fscanf(fp_txt, "%lf %lf %lf", &TxtPoint.x, &TxtPoint.y, &TxtPoint.z) != EOF)
//		{
//			m_vTxtPoints.push_back(TxtPoint);
//		}
//	}
//	else
//		cout << "txt���ݼ���ʧ�ܣ�" << endl;
//	number_Txt = m_vTxtPoints.size();
//	pcl::PointCloud<pcl::PointXYZ> cloud;
//
//	// Fill in the cloud data
//	cloud.width = number_Txt;
//	cloud.height = 1;
//	cloud.is_dense = false;
//	cloud.points.resize(cloud.width * cloud.height);
//
//	for (size_t i = 0; i < cloud.points.size(); ++i)
//	{
//		cloud.points[i].x = m_vTxtPoints[i].x;
//		cloud.points[i].y = m_vTxtPoints[i].y;
//		cloud.points[i].z = m_vTxtPoints[i].z;
//	}
//	pcl::io::savePCDFileASCII("C:/Users/can/Desktop/PCL test/txt2pcd/txt2pcd.pcd", cloud);
//	std::cerr << "Saved " << cloud.points.size() << " data points to txt2pcd.pcd." << std::endl;
//
//	for (size_t i = 0; i < cloud.points.size(); ++i)
//		std::cerr << "    " << cloud.points[i].x << " " << cloud.points[i].y << " " << cloud.points[i].z << std::endl;
//}

void txtFile::pcd2txt()
{	
	pcl::PointCloud<pcl::PointXYZ>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZ>);
	// Fill in the cloud data  
	if (pcl::io::loadPCDFile<pcl::PointXYZ>("", *cloud) == -1)
	{
		PCL_ERROR("Couldn't read file chuli.pcd\n");
		//return (-1);
	}
	//for (size_t i = 0; i < cloud->points.size(); i++)
	//{
		//  std::cout << " " << cloud->points[i].x << " " << cloud->points[i].y
		//  <<" "<< cloud->points[i].z << std::endl;
	//}
	
	int Num = cloud->points.size();
	double *X = new double[Num] {0};
	double *Y = new double[Num] {0};
	double *Z = new double[Num] {0};

	for (size_t i = 0; i < cloud->points.size(); ++i)
	{
		X[i] = cloud->points[i].x;
		Y[i] = cloud->points[i].y;
		Z[i] = cloud->points[i].z;
	}

	std::ofstream zos("");
	for (int i = 0; i<Num; i++)
	{
		zos << X[i] << " " << Y[i] << " " << Z[i];
	}
	std::cin.get();
}