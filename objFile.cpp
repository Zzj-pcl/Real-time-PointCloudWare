#include "objFile.h"

//pcl
#include <pcl/io/io.h>
#include <pcl/io/pcd_io.h>
#include <pcl/io/obj_io.h>
#include <pcl/PolygonMesh.h>
#include <pcl/point_cloud.h>
#include <pcl/io/vtk_lib_io.h> //loadPolygonFileOBJ����ͷ�ļ���

objFile::objFile()
{

}

objFile::~objFile()
{

}

void objFile::obj2pcd()
{
	pcl::PolygonMesh mesh;
	pcl::io::loadPolygonFileOBJ("", mesh);
	pcl::PointCloud<pcl::PointXYZ>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZ>);
	pcl::fromPCLPointCloud2(mesh.cloud, *cloud);
	pcl::io::savePCDFileASCII("", *cloud);
}