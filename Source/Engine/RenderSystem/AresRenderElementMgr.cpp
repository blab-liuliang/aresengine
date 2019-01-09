#include <Engine/RenderSystem/AresRenderElementMgr.h>
#include <Core/AresNumericTools.h>

namespace Ares
{
	// ��պ���
	void RenderElementMgr::Reset()
	{
		for( int i=0; i<RQ_Max; i++)
			m_rendrQueues[i].Reset();

		m_lights.clear();
		m_dominantLight.reset();
	}

	// ִ�ж�����Ⱦ
	void RenderElementMgr::Render(  RenderQueueFlag flag)
	{
		int lbit = LowestBitSet( flag);

		m_rendrQueues[lbit].Render();
	}

	// ��ӵ���Ⱦ����
	void RenderElementMgr::AddRenderable( RenderLayoutPtr& layout, RenderMaterial* material)
	{
		if( material)
		{
			BITFIELD queue = material->GetRenderQueue();
			for( int i=0; i<RQ_Max; i++)
			{
				if( queue & (1<<i))
					m_rendrQueues[i].AddRenderable( layout, material);
			}
		}
	}

	// �����Ƿ�Ϊ��
	bool RenderElementMgr::IsEmpty( RenderQueueFlag flag)
	{
		int lbit = LowestBitSet( flag);

		return m_rendrQueues[lbit].IsEmpty();
	}
}