#ifndef LASFILE_H
#define LASFILE_H

//qt
#include <QWidget>
#include <QDialog>
#include <QString>

//system
#include <string>

class lasFile : public QWidget
{
public:
	lasFile();
	~lasFile();

public:
	void lasRead();
	void lasWrite();
	void las2txt();
	void las2pcd();

private:

};

#endif // LASFILE_H
