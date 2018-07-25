#ifndef FILEIO_H
#define FILEIO_H

//Qt
#include <QString>

enum FILE_TYPES {
	UNKNOWN_FILE = 0,	
	LAS,
	DXF,
	TXT,
	ASCII,
	DGN,
	PDS,
	PDMS,
	IGS,
	STL,
	OBJ,
	WRL,
	PLY,			
	VTK,		
	PCD,						
	FILE_TYPES_COUNT,		
};

const FILE_TYPES FILE_TYPES_ENUMS[] = {
	UNKNOWN_FILE,
	LAS,
	DXF,
	TXT,
	ASCII,
	DGN,
	PDS,
	PDMS,
	IGS,
	STL,
	OBJ,
	WRL,
	PLY,
	VTK,
	PCD,
};

const char FILE_TYPE_FILTERS[][64] = {
	"All (*.*)",
	"LAS (*.las *.laz)",
	"DXF (*.dxf)",
	"OBJ (*.obj)",
	"TXT (*txt)",
	"ASCII (*.asc)",
	"DGN (*.dgn)",
	"PDS (*.pds)",	
	"PDMS (*.pdms)",
	"IGS (*.igs)",
	"STL (*.stl)",
	"WRL,(*.wrl)",
	"PLY (*.ply)",
	"VTK (*.vtk)",
	"PCD (*.pcd)"
};

const char FILE_TYPE_EXTENSION[][8] = {
	"",
	"asc",
	"dxf", 
	"obj",
	"txt",
	"asc",
	"dgn",
	"pds",
	"pdms",
	"igs",
	"stl",
	"wrl",
	"vtk",
	"ply",
	"pcd",
};

class FileIO
{
public:
	FileIO();
	~FileIO();

private:
	
};

#endif // FILEIO_H
