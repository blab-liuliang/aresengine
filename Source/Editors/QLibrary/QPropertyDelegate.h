#pragma once

#include <QtGui/QItemDelegate>
#include "QPropertyModel.h"

namespace QT_UI
{
	//------------------------------------------
	// ����ר��(��;����) 2010-03-15  ����
	//------------------------------------------
	class QPropertyDelegate : public QItemDelegate
	{
		Q_OBJECT
	public:
		// ���캯��
		QPropertyDelegate(QPropertyModel* model, QObject *parent = 0);

		// ���ƺ���
		void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;

		// �����༭���ؼ�
		QWidget* createEditor( QWidget* parent, const QStyleOptionViewItem& option, const QModelIndex& index) const;

		// ���ÿؼ�����
		void  setEditorData( QWidget* editor, const QModelIndex& index) const;

		// ����ģ������
		void  setModelData( QWidget* editor, QAbstractItemModel* model, const QModelIndex& index) const;

		// ���ñ༭��Geometry
		void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex& index ) const;

	private:
		// �Ƿ�ӵ���Զ�����Ⱦ
		bool IsSupportCustomPaint( const QString& widgetType) const;

		// �Զ�����Ⱦ
		void ItemDelegatePaint(  QPainter *painter, const QString& widgetType, const QRect& rect, const QVariant& val) const;

	private:
		QPropertyModel*   m_model;	// model
	};
}
