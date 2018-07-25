#ifndef TXTFILE_H
#define TXTFILE_H

typedef struct tagPOINT_3D
{
	double x;  //mm world coordinate x
	double y;  //mm world coordinate y
	double z;  //mm world coordinate z
	double r;
}POINT_WORLD;

class txtFile
{
public:
	txtFile();
	~txtFile();
	
public:
	void txt2pcd();
	void pcd2txt();
};

#endif // TXTFILE_H
