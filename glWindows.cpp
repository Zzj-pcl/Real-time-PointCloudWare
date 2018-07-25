//#include "glWindows.h"
//
////qt
//#include <QtGui>
//#include <QWheelEvent>
//#include <QElapsedTimer>
//#include <QSettings>
//#include <QApplication>
//
//glWindows::glWindows(QWidget *parent,
//	const QGLFormat& format,
//	QGLWidget* shareWidget,
//	bool silentInitialization)
//	: QGLWidget(parent)
//{
//
//}
//
//glWindows::~glWindows()
//{
//
//}
//
//void glWindows::setFontPixelSize(int pixelSize)
//{
//	g_font.setPixelSize(pixelSize);
//}
//
//void glWindows::setFontPointSize(int pointSize)
//{
//	g_font.setPointSize(pointSize);
//}
//
//void glWindows::mousePressEvent(QMouseEvent *event)
//{
//	g_cursorMoved = false;
//
//}
//
//void glWindows::mouseMoveEvent(QMouseEvent *event)
//{
//
//}
//
//void glWindows::mouseReleaseEvent(QMouseEvent *event)
//{
//	bool cursorHasMoved = g_cursorMoved;
//	bool acceptEvent = false;
//
//	//ÖØÖÃ×´Ì¬
//	g_cursorMoved = false;
//	g_lodActivated = false;
//	QApplication::restoreOverrideCursor();
//
//}
//
//void glWindows::wheelEvent(QWheelEvent* event)
//{
//
//}
//
//void glWindows::closeEvent(QCloseEvent *event)
//{
//	if (g_unClosable)
//		event->ignore();
//	else
//		event->accept();
//}
//
//void glWindows::initGL()
//{
//	if (g_initialized)
//		return;
//}
//
//void glWindows::resizeGL(int width, int height)
//{
//	glWidth = width;
//	glHeight = height;
//
//	glViewport(0, 0, width, height);
//	//invalidateViewport();
//	//invalidateVisualization();
//}
//
//void glWindows::paintGL()
//{
//
//}