#include "AresMap.h"
#include <string>
#include <vector>
#include "Engine/RenderSystem/AresRenderSystem.h"

using namespace std;

namespace Ares
{
	//------------------------------------
	// Quadtree��ͼ 2011-08-16 ����
	//------------------------------------
	class CQtMap : public IMap
	{
		typedef vector<IArea*> AreaList;

	public:
		// ���캯��
		CQtMap();

		// ��������
		~CQtMap();

	public:
		// ����Window(���ĵ�x,y; �뾶radius)
		//virtual void SetNavWindow( float x, float y, float radius);

		// ����
		//virtual void FrameMove( float fTime);

		// ��Ⱦ
		virtual void Render();

		// ��Ⱦ
		void RenderScene();

		// ��Ⱦ��Ӱ��ͼ
		void RenderShadowmap();

		// ��ȡ��ӰͶ�����Χ��
		void SetShadowCastBoundingBox();

	public:
		// ��ȡ��ǰ���ؽ���
		//virtual float GetLoadingProgress();

		// ��ȡ��Χ��
		//virtual const Rect3& GetBoundingBox();

		// ��ȡ��Χ��
		//virtual bool GetBoundingBoxByLayer( Rect3& box, const char* layer, bool update=false);

	public:
		// ��ȡ��ͼ��
		//virtual const char* GetName();

		// ��ȡ��������
		//virtual size_t GetAreaNum() { return m_areaList.size(); }

		// ��ȡ����
		//virtual IArea* GetArea( size_t idx) { return m_areaList[idx]; }

		// ��ȡ����
		//virtual IArea*	GetArea( const char* areaName);

	public:
		// ���õ�ͼ��
		//virtual void SetName( const char* name);

		// ����λ��
		//virtual void SetLocation( const char* location){ m_location = location; }

		// �������
		//virtual bool AddArea( IArea* pArea);

	private:
		// ��Ѱ����,ʹ�ɼ�Renderable����
		void SearchRenderable( const string& search, const Rect3& searchRect, const Frustum3* pOptionalFrustum);

		// ����ɼ�ʵ��
		//void SearchAndTidy( const Rect3& searchRect, const Frustum3* pOptionalFrustum);

	public:
		// ����
		virtual void Load( const char* fileName);

		// ����
		virtual void Save( const char* fileName=0);

	public:
		// ���ذ汾
		void Load0_1( FILE* fileHandle, const char* fileName);

	private:
		int				m_version;			// ��ǰ�汾
		string			m_name;				// ��ͼ��
		string			m_location;			// λ��
		AreaList		m_areaList;			// �����б�
		SNavWindow		m_navWindow;		// ��������
		RenderQueueMgr	m_renderQueueMgr;	// ��Ⱦ���й�����
	};
}