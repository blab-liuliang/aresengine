#include <QApplication>
#include <Windows.h>
#include <QTextCodec>
#include "MainWindow.h"

using namespace Ares;

//-----------------------------------
// �������( ��׼main����)
//-----------------------------------
int main( int argc, char* argv[])
{
	float* a = new float;

	QApplication app( argc, argv);

	// ���ñ��뷽ʽ
	//QTextCodec *codec = QTextCodec::codecForName("gb2312");  

	//QTextCodec::setCodecForLocale(codec);  
	//QTextCodec::setCodecForCStrings(codec);  
	//QTextCodec::setCodecForTr(codec);  

	MainWindow mainWindow;

	mainWindow.show();

	app.exec();
}