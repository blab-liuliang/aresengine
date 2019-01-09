#include <QApplication>
#include <QtGui/QSplashScreen>
#include "MainWindow.h"
#include "SCMainWindow.h"
#include "ModelEdit/MOMainWindow.h"
#include "CMDLine.h"
#include <Windows.h>
#include <QTextCodec>
#include <Physics/ConvexHull2D.h>
#include <boost/regex.hpp>

#ifdef ARES_PLATFORM_WINDOWS
//#include <vld.h>
#endif

using namespace Ares;
using namespace QT_UI;

extern "C"
{
	_declspec(dllexport) DWORD NvOptimusEnablement = 0x00000001;
}

//-----------------------------------
// �������( ��׼main����)
//-----------------------------------
int main( int argc, char* argv[])
{
	QApplication app( argc, argv);

	// ���ñ��뷽ʽ
	QTextCodec *codec = QTextCodec::codecForName("GB2312");  

	QTextCodec::setCodecForLocale(codec);  
	QTextCodec::setCodecForCStrings(codec);  
	QTextCodec::setCodecForTr(codec);  

	// QSplashScreen
	QSplashScreen* pSplash = new QSplashScreen;
	pSplash->setPixmap( QPixmap("Icon/Logo.png"));
	pSplash->show();

	//pSplash->showMessage( QObject::tr("ս�񿪷����߰�(32-λ, DX11) \n Copyright @ 2009-2012 ����"),  Qt::AlignLeft | Qt::AlignBottom, Qt::white);

	if( !CMDLine::Parser( argc, argv))
	{
		// �����ڳ�ʼ��
		MainWindow* mainWindow = new_ MainWindow();
		mainWindow->showMaximized();
		mainWindow->BeginRender();

		pSplash->finish( mainWindow);
		SAFE_DELETE( pSplash);

		mainWindow->SetEditorType( "Scene");

		app.exec();

		SAFE_DELETE( mainWindow);
	}
	else
	{
		QWidget* widget = new QWidget;
		pSplash->finish( widget);

		SAFE_DELETE( pSplash);
		SAFE_DELETE( widget);
	}
}