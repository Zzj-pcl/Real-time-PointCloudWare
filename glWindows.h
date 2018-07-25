//#ifndef GLWINDOWS_H
//#define GLWINDOWS_H
//
//#include <QObject>
////gl
//#include <QGLWidget>
////Qt
//#include <QFont>
//#include <QMouseEvent>
////system
//#include <set>
//#include <list>
//
//class glWindows : public QGLWidget
//{
//	Q_OBJECT
//
//public:
//	glWindows(QWidget *parent = 0,
//		const QGLFormat& format = QGLFormat::defaultFormat(),
//		QGLWidget* shareWidget = 0,
//		bool silentInitialization = false);
//	~glWindows();
//
//protected:
//	void setFontPixelSize(int pixelSize); //设置字体像素大小
//	void setFontPointSize(int pointSize); //设置字体为20Point。 那么字体的像素大小是 90 * 20 / 72 约等于 25
//
//	//窗体事件函数
//	void mousePressEvent(QMouseEvent *event);
//	void mouseMoveEvent(QMouseEvent *event);
//	void mouseReleaseEvent(QMouseEvent *event);
//	void wheelEvent(QWheelEvent *event);
//	void closeEvent(QCloseEvent *event);
//
//	//初始化窗体
//	void initGL();
//	void resizeGL(int width, int height);
//	void paintGL();
//
//private:
//	QFont g_font;
//	bool g_cursorMoved;
//	bool g_lodActivated;
//	bool g_unClosable;
//	bool g_initialized;
//	int glWidth;
//	int glHeight;
//};
//
//#endif // GLWINDOWS_H
