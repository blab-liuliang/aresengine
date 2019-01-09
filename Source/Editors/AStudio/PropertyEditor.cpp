#include <QtGui/QtGui>
#include "VideoSetting.h"
#include "PropertyEditor.h"
#include "TerrainEdit.h"
#include "LightProperty.h"
#include "SCLogic.h"
#include <QPropertyDelegate.h>
#include <QPropertyModel.h>

using namespace Ares;

namespace QT_UI
{
	// ���캯��
	CPropertyEditor::CPropertyEditor( QWidget* parent/* = 0*/)
		: QDockWidget( parent)
		, m_currFrame( NULL)
	{
		setupUi( this);

		m_frameList["TerrainEdit"]   = new_ TerrainEdit( dockWidgetContents);
		m_frameList["PropertyLight"] = new_ MQLightProperty( dockWidgetContents);

		// ���widget
		for( FrameList::iterator it=m_frameList.begin(); it!=m_frameList.end(); it++)
		{
			verticalLayout_3->insertWidget( 0, it->second);
		}

		HideAllFrame();
	}

	// ����Ϊ���ɼ�
	void CPropertyEditor::HideAllFrame()
	{
		for ( FrameList::iterator it=m_frameList.begin(); it != m_frameList.end(); it++)
		{
			it->second->setVisible( false);
		}
	}

	// �������ֻ�ȡFrame
	QWidget* CPropertyEditor::GetFrame( const char* frame)
	{
		FrameList::iterator it=m_frameList.find( frame);
		if( it != m_frameList.end())
			return it->second;

		return NULL;
	}

	// ��ʾĳFrame
	void CPropertyEditor::ShowFrame( const char* frame)
	{
		if( m_currFrame && m_currName == frame)
		{
			m_currFrame->setVisible( true);
		}
		else
		{
			for ( FrameList::iterator it=m_frameList.begin(); it != m_frameList.end(); it++)
			{
				if( it->first == frame)
				{
					m_currName	= it->first;
					m_currFrame = it->second;
					it->second->setVisible( true);
				}
				else
				{
					it->second->setVisible( false);
				}
			}
		}
	}

	// ��ʾ��ǰѡ���������
	void CPropertyEditor::ShowProperty( Entity* entity)
	{
		// ����ѡ���ʵ������, ��ʾ���Կ���
		if( entity)
		{
			switch(entity->GetTypeDetail())
			{
			case ED_Terrain:
				{
					Terrain* terrain = dynamic_cast<Terrain*>( entity);
					if( terrain)
					{
						TerrainEdit* terrainEdit = dynamic_cast<TerrainEdit*>( m_frameList["TerrainEdit"]);
						if( terrainEdit)
						{
							terrainEdit->SetCurrTerrain( terrain);

							ShowFrame( "TerrainEdit");
						}
					}
				}
				break;
			case ED_LightAmbient:
			case ED_LightPoint:
			case ED_LightDirection:
				{
					Light* light = dynamic_cast<Light*>( entity);
					if( light)
					{
						MQLightProperty* lightProperty = dynamic_cast<MQLightProperty*>( m_frameList["PropertyLight"]);
						if( lightProperty)
						{
							lightProperty->SetCurrLight( light);

							ShowFrame( "PropertyLight");
						}
					}
				}
				break;
			default:
				{
					ShowFrame( "");
				}
				break;
			}
		}
		else
		{
			ShowFrame( "");
		}
	}
}