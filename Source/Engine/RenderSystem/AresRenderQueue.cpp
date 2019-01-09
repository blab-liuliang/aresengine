#include <Engine/AresRoot.h>
#include <Engine/RenderSystem/AresRenderQueue.h>

namespace Ares
{
	// ���캯��
	RenderQueue::RenderQueue()
	{

	}

	// ��������
	RenderQueue::~RenderQueue()
	{

	}

	// add renderable
	void RenderQueue::AddRenderable(  RenderLayoutPtr& layout, RenderMaterial* material)
	{
		if( layout && material)
			m_renderables.push_back( make_pair( layout, material));
	}

	//the function is responsive to executing the sorted renderable group
	void RenderQueue::Render( bool sort/*=true*/, bool clear/*=true*/)
	{
		// is exec sort
		if( sort)
			Sort();

		// render
		for ( size_t i=0; i<m_renderables.size(); i++)
		{
			ARenderDevice->Render( m_renderables[i].first.get(), m_renderables[i].second);
		}

		// is clear
		//if( clear)
		//	Clear();
	}

	//// SRenderEntry soring functor 
	//typedef SRenderEntry* LPRenderEntry;
	//struct sort_less
	//{
	//	// ���� "()" �����
	//	bool operator()(const LPRenderEntry& a, const LPRenderEntry& b) const
	//	{
	//		// ��������ֵ A
	//		if( a->sortValueA > b->sortValueA)
	//		{
	//			return false;
	//		}
	//		else if( a->sortValueA < b->sortValueA)
	//		{
	//			return true;
	//		}

	//		// ����ֵ B
	//		if( a->sortValueB > b->sortValueB)
	//		{
	//			return false;
	//		}
	//		else if( a->sortValueB < b->sortValueB)
	//		{
	//			return true;
	//		}

	//		// ����ֵ��C
	//		if( a->sortValueC > b->sortValueC)
	//		{
	//			return false;
	//		}
	//		else if( a->sortValueC < b->sortValueC)
	//		{
	//			return true;
	//		}

	//		return false;
	//	}
	//};


	// ����
	void RenderQueue::Sort()
	{
		// ʹ��ָ���������(����������ʵ�Ķ���)
		//QuickSort( m_pEntryList, m_iActiveEntries, sort_less());
	}
}