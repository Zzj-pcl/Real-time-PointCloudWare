#ifndef POINTCLOUD_H
#define POINTCLOUD_H

//pcl
#include <pcl/io/io.h>
#include <pcl/io/pcd_io.h>
#include <pcl/io/ascii_io.h>
#include <pcl/io/ply_io.h>
#include <pcl/io/obj_io.h>
#include <pcl/io/vtk_io.h>
#include <pcl/io/vtk_lib_io.h>
#include <pcl/point_types.h>
#include <pcl/point_cloud.h>        //点类型定义头文件
#include <pcl/kdtree/kdtree_flann.h> //kdtree类定义头文件
#include <pcl/point_cloud.h>
#include <pcl/PCLPointCloud2.h>
#include <pcl/visualization/pcl_visualizer.h>
#include <pcl/visualization/cloud_viewer.h>
#include <boost/shared_ptr.hpp>
#include <pcl/PolygonMesh.h>
#include <pcl/kdtree/kdtree_flann.h>
#include <pcl/filters/passthrough.h>
#include <pcl/features/normal_3d.h> //特征提取
#include <pcl/features/normal_3d_omp.h>
#include <pcl/features/shot_omp.h> 
#include <pcl/surface/gp3.h> //重构
#include <pcl/surface/poisson.h>
#include <pcl/common/transforms.h> //转换矩阵
#include <pcl/console/parse.h>

typedef pcl::PointXYZRGBA PointT;
typedef pcl::PointXYZ PointxyzT;
typedef pcl::PointCloud<PointT> PointCloudT;

class PointCloud
{
public:
	PointCloud();
	~PointCloud();

	//点云结构体
	pcl::PointXYZ Pxyz;

	//点云指针
	PointCloudT::Ptr cloudT;

	pcl::PointCloud<pcl::PointXY>::Ptr Cxy;
	pcl::PointCloud<pcl::PointXYZ>::Ptr Cxyz;
	pcl::PointCloud<pcl::PointXYZRGB>::Ptr Cxyzrgb;
	pcl::PointCloud<pcl::PointXYZRGBA>::Ptr Cxyzrgba;

	//点云数据存储容器
	pcl::PointCloud<pcl::PointXY> cloudxy;
	pcl::PointCloud<pcl::PointXYZ> cloudxyz;
	pcl::PointCloud<pcl::PointXYZRGB> cloudxyzrgb;
	pcl::PointCloud<pcl::PointXYZRGBA> cloudxyzrgba;

private:
	
};

#endif // POINTCLOUD_H
