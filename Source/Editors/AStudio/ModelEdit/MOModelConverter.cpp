#include <QtGui/QtGui>
#include "MOModelConverter.h"
#include "MOYNDMeshToAres.h"
#include <Core/AresFileUtils.h>

using namespace Ares;

namespace QT_UI
{
	// ���캯��
	MOModelConverter::MOModelConverter( QWidget* parent/* = 0*/)
		: QDialog( parent)
	{
		setupUi( this);

		// ������Ϣ
		connect( m_browserYND,			SIGNAL( clicked()), this, SLOT( SelectYNDLocation()));
		connect( m_browserAres,			SIGNAL( clicked()), this, SLOT( SelectAresLocation()));
		connect( m_yndToAresConverter,	SIGNAL( clicked()), this, SLOT( ConvertexFromYNDToAres()));
	}

	// ѡ��YND��Դ·��
	void MOModelConverter::SelectYNDLocation()
	{
		QString qFileDir = QFileDialog::getExistingDirectory( this, tr("Choose YND directory"), "", QFileDialog::ShowDirsOnly);

		QDir dir( QDir::currentPath());
		qFileDir = dir.relativeFilePath( qFileDir);

		if( !qFileDir.isEmpty())
		{
			if( qFileDir.length()>0 && qFileDir[qFileDir.length()-1]!='/')
				qFileDir += "/";

			m_yndsLocation->setText( qFileDir);
		}
	}

	// ѡ��Ares�洢·��
	void MOModelConverter::SelectAresLocation()
	{
		QString qFileDir = QFileDialog::getExistingDirectory( this, tr("Choose Ares directory"), "", QFileDialog::ShowDirsOnly);

		QDir dir( QDir::currentPath());
		qFileDir = dir.relativeFilePath( qFileDir);

		if( !qFileDir.isEmpty())
		{
			if( qFileDir.length()>0 && qFileDir[qFileDir.length()-1]!='/')
				qFileDir += "/";

			m_aresLocation->setText( qFileDir);
		}
	}

	// ת��
	void MOModelConverter::ConvertexFromYNDToAres()
	{
		string yndRootLocation = m_yndsLocation->text().toStdString();
		string aresSaveLocation= m_aresLocation->text().toStdString();
		bool isReplaceExistAres= m_isReplaceExistFile->isChecked();

		// �ݹ���������ļ�
		FileUtils fileUtils;
		fileUtils.AddSearchPathRecursive( yndRootLocation.c_str());

		// ȷ������Ҫת����ģ��
		vector<string> yndFiles;
		fileUtils.SearchFilesByExt( yndFiles, yndRootLocation.c_str(), ".GMe");

		// ִ��ת��
		for( size_t i=0; i<yndFiles.size(); i++)
		{
			ModelConverter::YNDToAres( yndFiles[i].c_str(), aresSaveLocation.c_str(), fileUtils, isReplaceExistAres);
		}

	}
}