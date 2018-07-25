#include "pcw.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	PCW w;
	w.show();
	return a.exec();
}
