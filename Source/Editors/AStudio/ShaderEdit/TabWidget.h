#ifndef SHADER_TAB_WIDGET_H
#define SHADER_TAB_WIDGET_H

#include <QtGui/QTextEdit>
#include <QShaderSyntaxHighLighter.h>
#include <QLuaSyntaxHighLighter.h>
#include <QtGui/QTabWidget>
#include <map>

using namespace std;
using namespace Qt_Ares;

namespace Ares
{
	//-----------------------------------
	// Dx9MdiArea dx��ʾ����
	//-----------------------------------
	class CTabWidget : public QTabWidget
	{
		Q_OBJECT

	public:
		struct SEditGroup
		{
			QTextEdit*					m_pText;
			QSyntaxHighlighter*			m_highLighter;// ����
		};

		typedef map< string, SEditGroup>  EditList;

	public:
		// ���캯��
		CTabWidget( QWidget* parent = NULL);

		// ��������
		~CTabWidget();

		// ���ļ�
		void Open( const char* fileName);

		// ����
		void Save();

	public: signals:
		// Error
		void Error( const char* err);

	private slots:
		// ����
		bool Compile();

	private:
		EditList     m_editList;		// �༭�б�
	};
}

#endif