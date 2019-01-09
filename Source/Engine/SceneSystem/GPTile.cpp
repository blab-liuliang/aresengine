#include <Engine/SceneSystem/GPTile.h>

namespace Ares
{
	// ���캯��
	CGPTile::CGPTile()
		: m_world( 0),
		  m_state( EM_UNLOADED)
	{

	}

	// ��������
	CGPTile::~CGPTile()
	{
		m_world = 0;
	}

	// ִ�м���
	void CGPTile::DoLoad()
	{
		if( m_state != EM_LOADED && m_state != EM_LOADING)
		{
			m_state = EM_LOADING;

			Load();

			m_state = EM_LOADED;
		}
	}

	// ִ��ж��
	void CGPTile::DoUnload()
	{
		if( m_state != EM_UNLOADED && m_state != EM_UNLOADING)
		{
			m_state = EM_UNLOADING;

			Unload();

			m_state = EM_UNLOADED;
		}
	}
}