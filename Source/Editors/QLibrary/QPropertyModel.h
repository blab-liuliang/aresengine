#pragma once

#include <map>
#include <QtGui/QStandardItem>
#include <QtGui/QStandardItemModel>
#include <Core/AresCore.h>
#include <boost/signals2/signal.hpp>
#include <boost/any.hpp>
#include <Core/3rdParty/TinyXml/tinyxml.h>

using namespace std;

namespace QT_UI
{
	//------------------------------------------
	// ����ר��(��;����) 2010-03-15  ����
	//------------------------------------------
	class QPropertyModel : public QStandardItemModel
	{	
		Q_OBJECT

		typedef map<QString, QVariant> AttribList;
	public:
		// ���캯��
		QPropertyModel( const char* fileName, QObject* parent= 0);
		~QPropertyModel();

		// ��������
		void  setupModelData( TiXmlDocument* cfg);

		// �������Բ�������
		bool findValue( QVariant& value,const QString& propertyName);

		// ��������
		void setValue( const QString& propertyName, QVariant value);

		// ����text����item
		QStandardItem* findItemByText( const char* text);

		// ����ӽ��
		QStandardItem* addChildItem( QStandardItem* parent, const char* text, bool bold, int row, int col, const char* widget, const char* property);

		// �����ӽ��
		void removeChildItem( QStandardItem* parent);

	public:
		// values changed signals
		boost::signals2::signal<void()> Signal_ValueChanged;

	private:
		// ���������ļ�
		void  ParseCfg();

		// �ݹ����
		void  addChildItem( TiXmlElement* pFirstChildElement, QStandardItem* pParentItem);

		// ���wigetMap
		void addWidgetCfg(QStandardItem* item, const char* type);

	private:
		TiXmlDocument*				m_cfg;
		AttribList					m_valueList;
		vector<QStandardItem*>		m_standItems;		// ����
	};
}