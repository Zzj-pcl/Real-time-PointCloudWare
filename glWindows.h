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
//	void setFontPixelSize(int pixelSize); //�����������ش�С
//	void setFontPointSize(int pointSize); //��������Ϊ20Point�� ��ô��������ش�С�� 90 * 20 / 72 Լ���� 25
//
//	//�����¼�����
//	void mousePressEvent(QMouseEvent *event);
//	void mouseMoveEvent(QMouseEvent *event);
//	void mouseReleaseEvent(QMouseEvent *event);
//	void wheelEvent(QWheelEvent *event);
//	void closeEvent(QCloseEvent *event);
//
//	//��ʼ������
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
