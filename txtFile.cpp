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

//文件流
void txtFile::txt2pcd()
{
	int n = 0; //n用来计文件中点个数      
	
	FILE *fp_1;
	fp_1 = fopen("cat.txt", "r");
	n = numofPoints("cat.txt"); //使用numofPoints函数计算文件中点个数  
	//std::cout << "there are " << n << " points in the file..." << std::endl;
	
	//新建一个点云文件，然后将结构中获取的xyz值传递到点云指针cloud中。  
	pcl::PointCloud<pcl::PointXYZ> cloud;
	cloud.width = n;
	cloud.height = 1;
	cloud.is_dense = false;
	cloud.points.resize(cloud.width * cloud.height);
	
	//将点云读入并赋给新建点云指针的xyz      
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
	//将点云指针指向的内容传给pcd文件  
	pcl::io::savePCDFileASCII(".pcd", cloud);
	//std::cerr << "Saved " << cloud.points.size() << " data points to test_pcd.pcd." << std::endl;
}

//void txtFile::txt2pcd()
//{
//	/////加载txt数据
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
//		cout << "txt数据加载失败！" << endl;
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