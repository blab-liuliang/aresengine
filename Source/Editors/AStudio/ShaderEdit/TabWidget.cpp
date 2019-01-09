#include <QtGui/QtGui>
#include "TabWidget.h"
#include "SHLogic.h"
#include <Engine/AresRoot.h>
#include "SHMainWindow.h"

namespace Ares
{
	// ���캯��
	CTabWidget::CTabWidget( QWidget* parent/* = NULL*/)
		: QTabWidget( parent)
	{
		//open("Data\\shader\\bloom.fx");
	}

	// ��������
	CTabWidget::~CTabWidget()
	{
		Save();
	}

	// ���ļ�
	void CTabWidget::Open( const char* fileName)
	{
		if( fileName)
		{
			// �ж��ļ�����
			char ext[256];
			_splitpath( fileName, NULL, NULL, NULL, ext);

			EditList::iterator it = m_editList.find( fileName);

			if( it == m_editList.end())
			{
				QFile file( fileName);
				if( file.open( QFile::ReadOnly | QFile::Text))
				{
					SEditGroup  editGroup;

					editGroup.m_pText = new QTextEdit(this);
					editGroup.m_pText->setTabStopWidth( 24);
					editGroup.m_pText->setPlainText( file.readAll());

					if( strcmp( ext, ".fx") == 0)
						editGroup.m_highLighter = new QShaderSyntaxHighLighter(editGroup.m_pText->document());
					else
						editGroup.m_highLighter = new QLuaSyntaxHighLighter(editGroup.m_pText->document());

					m_editList[fileName] = editGroup;

					string nameAndExt = FileUtils::GetNameExt( fileName);

					addTab( editGroup.m_pText, nameAndExt.c_str());
				}
			}
			else
			{
				// ��ʾ��ǰ
				setCurrentIndex( indexOf( it->second.m_pText));
			}
		}
	}

	// ����
	void CTabWidget::Save()
	{
		for ( EditList::iterator it = m_editList.begin(); it != m_editList.end(); it++)
		{
			FILE* fileHandle = fopen( it->first.c_str(), "wt");
			if( fileHandle)
			{
				string plainText = it->second.m_pText->toPlainText().toStdString();
				fwrite( plainText.c_str(), plainText.size(), 1, fileHandle);

				fflush(fileHandle);
				fclose(fileHandle);
			}
		}
	}

	// ����
	bool CTabWidget::Compile()
	{
		// 1.�ȱ���
		Save();

		// 2.����������ʾ
		//UI_ErrorOutput->Clear();

		// 3.�����ǰҳshader
		for ( EditList::iterator it = m_editList.begin(); it != m_editList.end(); it++)
		{
			if( it->second.m_pText == currentWidget())
			{
				RenderMethodPtr method = ARenderDevice->CreateRenderMethod();
				method->Load( it->first.c_str(), ShaderMacros());

				//method->SaveByteCode( "D:\\test.vs", ST_VertexShader);
				//method->SaveByteCode( "D:\\test.ps", ST_PixelShader);
			}
		}



		//QWidget* pWidget = currentWidget();
		//if( pWidget)
		//{
		//	QTextEdit* pTextEdit = dynamic_cast<QTextEdit*>(pWidget);
		//	string plainText = pTextEdit->toPlainText().toStdString();

		//	
		//}

		return false;
	}
}