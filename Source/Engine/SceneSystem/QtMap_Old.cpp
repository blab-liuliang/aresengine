//#include "QtMap_.h"
//#include <Core/AresChar.h>
//#include "AresSceneSystem.h"
//#include "../AresRoot.h"
//#include "../RenderSystem/Light/AresLightEntity.h"
//#include "../CameraSystem/AresCameraCallback.h"
//#include "../RenderSystem/AresRenderSystem.h"
//
//namespace Ares
//{
//	//// ��Ⱦ����
//	//static void RenderShadowMaps( const CRect3D& searchRect, const CFrustum* pOptionalFrustum)
//	//{
//	//	g_pSceneManager->RenderShadowMap( searchRect, pOptionalFrustum);
//	//}
//
//	// ���캯��
//	CQtMap::CQtMap()
//	{
//		m_version = 1;
//	}
//
//	// ��������
//	CQtMap::~CQtMap()
//	{
//		int a = 10;
//	}
//
//	// ��ȡ��ͼ��
//	const char* CQtMap::GetName()
//	{
//		return m_name.c_str();
//	}
//
//	// ����Window(���ĵ�x,y; �뾶radius)
//	//void CQtMap::SetNavWindow( float x, float y, float radius)
//	//{
//	//	m_navWindow.m_x = x;
//	//	m_navWindow.m_y = y;
//
//	//	m_navWindow.m_radius = radius;
//
//	//	// ������������ĵ���������Ϣ
//	//	for( AreaList::iterator it=m_areaList.begin(); it!=m_areaList.end(); it++)
//	//	{
//	//		(*it)->SetNavWindow( m_navWindow);
//	//	}
//	//}
//
//	// ����
//	void CQtMap::FrameMove( float fTime)
//	{
//		for( AreaList::iterator it=m_areaList.begin(); it!=m_areaList.end(); it++)
//		{
//			(*it)->FrameMove( fTime);
//		}
//	}
//
//	// ��ȡ����
//	IArea* CQtMap::GetArea( const char* areaName)
//	{
//		for( AreaList::iterator it=m_areaList.begin(); it!=m_areaList.end(); it++)
//		{
//			if( strcmp( (*it)->GetName(), areaName) == 0)
//				return *it;
//		}
//
//		return NULL;
//	}
//
//	// ���õ�ͼ��
//	//void CQtMap::SetName( const char* name)
//	//{
//	//	m_name = name;
//	//}
//
//	//// �������
//	//bool CQtMap::AddArea( IArea* pArea)
//	//{
//	//	IArea* tArea = GetArea( pArea->GetName());
//
//	//	if( !tArea)
//	//	{
//	//		string tLocation = m_location + pArea->GetName() + "/";
//	//		pArea->SetLocation( tLocation.c_str());
//
//	//		m_areaList.push_back( pArea);
//
//	//		return true;
//	//	}
//
//	//	return false;
//	//}
//
//	//// ��ȡ��ǰ���ؽ���
//	//float CQtMap::GetLoadingProgress()
//	//{
//	//	float progress = 0.f;
//
//	//	// ��������
//	//	if( m_areaList.size())
//	//	{
//	//		for( size_t i=0; i<m_areaList.size(); i++)
//	//			progress += m_areaList[i]->GetLoadingProgress();
//
//	//		progress /= m_areaList.size();
//	//	}
//	//	else
//	//		progress = 1.f;
//
//	//	return progress;
//	//}
//
//	//// ��ȡ��Χ��
//	//const Rect3& CQtMap::GetBoundingBox()
//	//{
//	//	static Rect3 boundingBox( 0.f, 512.f, 0.f, 512.f, 0.f, 20.f);
//
//	//	return boundingBox;
//	//}
//
//	// ��ȡ��Χ��
//	//bool CQtMap::GetBoundingBoxByLayer( Rect3& box, const char* layer, bool update)
//	//{
//	//	// ������������ĵ���������Ϣ
//	//	for( AreaList::iterator it=m_areaList.begin(); it!=m_areaList.end(); it++)
//	//	{
//	//		(*it)->GetBoundingBoxByLayer( box, layer, update);
//	//	}
//
//	//	return true;
//	//}
//
//	// ����
//	void CQtMap::Load( const char* fileName)
//	{
//		FILE* fileHandle = fopen( fileName, "rb");
//		if( fileHandle)
//		{
//			// ����λ��
//			char tLocation[1024];
//			changeNameExt( tLocation, fileName, "");
//			SetLocation( tLocation);
//
//			// ���ذ汾��
//			fread( &m_version, sizeof(m_version), 1, fileHandle);
//
//			switch( m_version)
//			{
//			case 1:
//				Load0_1( fileHandle, fileName);
//				break;
//			}
//
//			fflush( fileHandle);
//			fclose( fileHandle);
//		}
//	}
//
//	// ����
//	void CQtMap::Save( const char* fileName)
//	{
//		string tLocationName;
//		if( !fileName)
//			tLocationName = m_location + m_name;
//		else
//			tLocationName = fileName;
//
//		FILE* fileHandle = fopen( tLocationName.c_str(), "wb");
//		if( fileHandle)
//		{
//			// ����汾��
//			fwrite( &m_version, sizeof(m_version), 1, fileHandle);
//
//			// �����ͼ��
//			fwrites( m_name.c_str(), fileHandle);
//
//			// ��������
//			size_t areaNum = m_areaList.size();
//			fwrite( &areaNum, sizeof( size_t), 1, fileHandle);
//
//			// ����������
//			vector<string> areaLocations;
//			for( size_t i=0; i<m_areaList.size(); i++)
//			{
//				// �������򱣴�λ��
//				char tAreaLocationName[1024];
//				sprintf( tAreaLocationName, "%s/%s.area", m_areaList[i]->GetName(),  m_areaList[i]->GetName());
//				fwrites( tAreaLocationName, fileHandle);
//
//				areaLocations.push_back( tAreaLocationName);
//			}
//
//			fflush( fileHandle);
//			fclose( fileHandle);
//
//			// ��������
//			for( size_t i=0; i<m_areaList.size(); i++)
//			{
//				// ����·��
//				char tAreaFile[1024];
//				changeNameExt( tAreaFile, tLocationName.c_str(), areaLocations[i].c_str());
//
//				m_areaList[i]->Save( tAreaFile);
//				//m_areaList[i]->SaveTerrain( tAreaFile);
//			}
//		}
//	}
//
//	// ���ذ汾
//	void CQtMap::Load0_1( FILE* fileHandle, const char* fileName)
//	{
//		// ���ص�ͼ��
//		freads( m_name, fileHandle);
//
//		// ��������
//		size_t areaNum=0;
//		fread( &areaNum, sizeof( size_t), 1, fileHandle);
//
//		// ����������
//		for( size_t i=0; i<areaNum; i++)
//		{
//			string tAreaName;
//			freads( tAreaName, fileHandle);
//
//			IArea* pArea = Root::GetSceneSystem()->CreateArea();
//			if( pArea)
//			{
//				// ����·��
//				char tAreaFile[512];
//				changeNameExt( tAreaFile, fileName, tAreaName.c_str());
//
//				pArea->Load( tAreaFile);
//				//pArea->LoadTerrain( tAreaFile);
//
//				AddArea( pArea);
//			}
//			else
//			{
//				// error
//				// ���� tAreaName ����ʧ��
//			}
//		}
//	}
//
//	// AABB��Χ��Ͷ��AABB��Χ��
//	static Rect3 AABBCastAABB( const Rect3& cast, const Vector3& castDir, const Rect3& accept)
//	{
//		Rect3 result = cast;
//
//		// ��ȡͶ����İ˸�����
//		//D3DXVECTOR3 tVectors[8];
//		//	cast.GetEightPoints( tVectors);
//
//		for ( int i=0; i<8; i++)
//		{
//
//		}
//
//		return result;
//	}
//
//	// ��Ⱦ
//	void CQtMap::Render()
//	{
//		m_renderQueueMgr.Reset();
//		// ����shadowmap
//		//RenderShadowmap();
//
//		// ��Ⱦ������
//		{
//			SearchRenderable( "main", Root::GetCameraSystem()->GetSearchRect(),  Root::GetCameraSystem()->GetFrustum());
//
//			m_renderQueueMgr.Render( "terrain");
//
//			m_renderQueueMgr.Render( "opacity");
//		}
//	}
//
//	// ��Ⱦ��Ӱ��ͼ
//	void CQtMap::RenderShadowmap()
//	{/*
//		// ��Ӱͼ
//		SetShadowCastBoundingBox();
//
//		Root::GetRenderSystem()->GetLiSPSMManager()->Begin();
//
//		for( AreaList::iterator it=m_areaList.begin(); it!=m_areaList.end(); it++)
//		{
//			Entity* pEntityList = (*it)->BuildSearchResults( Root::GetRenderSystem()->GetLiSPSMManager()->GetLightSearchRect(), NULL);
//
//			//// Render all objects
//			Entity* pFirstMember = pEntityList;
//			while (pFirstMember)
//			{
//				// ֻ��ģ�Ͳ�����Ӱ
//				if ( pFirstMember->GetType() == RenderEntity::EM_ENTITY_RENDER)
//				{				
//					RenderEntity* pRenderMember = (RenderEntity*)pFirstMember;
//					pRenderMember->SubmitRenderable( "shadow");
//					pRenderMember = NULL;
//				}
//
//				pFirstMember = pFirstMember->NextSearchLink();
//			}
//		}
//
//		Root::GetRenderSystem()->ExecRenderQueue("opacity");
//
//		Root::GetRenderSystem()->GetLiSPSMManager()->End();*/
//	}
//
//	// ��Ⱦ
//	void CQtMap::RenderScene()
//	{
//		//ARenderFactory->GetRenderWindow()->Present();
//
//		// ��Ѱ������ɼ�ʵ��
//		//SearchAndTidy( g_mainCamera->GetSearchRect(),  g_mainCamera->GetFrustum());
//
//		//RenderSystem* pRenderSystem = Root::GetRenderSystem();
//		//if( pRenderSystem)
//		//{
//		//	pRenderSystem->ExecRenderQueue("opacity");
//
//		//	//pRenderSystem->GetVisualShapeMgr()->GetRenderQueue()->;
//		//}
//
//		// VisualShape queue
//	}
//
//	// ��Ѱ����,ʹ�ɼ�Renderable����
//	void CQtMap::SearchRenderable( const string& search, const Rect3& searchRect, const Frustum3* pOptionalFrustum)
//	{
//		for( AreaList::iterator it=m_areaList.begin(); it!=m_areaList.end(); it++)
//		{
//			Entity* pEntityList = (*it)->BuildSearchResults( searchRect, pOptionalFrustum);
//
//			// ��Ⱦǰ����
//			Entity* pFirstMember = pEntityList;
//			while ( pFirstMember)
//			{
//				RenderEntity* renderEntity = dynamic_cast<RenderEntity*>( pFirstMember);
//				if( renderEntity)
//				{
//					renderEntity->SubmitRenderable( m_renderQueueMgr, search);
//				}
//
//				pFirstMember = pFirstMember->NextSearchLink();
//			}
//		}
//	}
//
//	// ����ɼ�ʵ��
//	/*void CQtMap::SearchAndTidy( const Rect3& searchRect, const Frustum3* pOptionalFrustum)
//	{
//		ILightManager* lightMgr = Root::GetRenderSystem()->GetLightManager();
//		// ��չ�Դ�����й�Դ
//		lightMgr->ClearActiveLightList();
//
//		for( AreaList::iterator it=m_areaList.begin(); it!=m_areaList.end(); it++)
//		{
//			Entity* pEntityList = (*it)->BuildSearchResults( searchRect, pOptionalFrustum);
//
//			// ��Ⱦǰ����
//			Entity* pFirstMember = pEntityList;
//			while ( pFirstMember)
//			{
//				if ( pFirstMember && pFirstMember->GetType() == Entity::EM_ENTITY_RENDER)
//				{
//					RenderEntity* pRenderMember = (RenderEntity*)pFirstMember;
//					pRenderMember->PrepareForRender();
//					pRenderMember = NULL;
//				}
//
//				pFirstMember = pFirstMember->NextSearchLink();
//			}
//
//			// Render all objects
//			pFirstMember = pEntityList;
//			while (pFirstMember)
//			{
//				// ��ʱ��Ҫ��Ⱦˮ
//				if ( pFirstMember->GetType() == Entity::EM_ENTITY_RENDER)
//				{				
//					RenderEntity* pRenderMember = (RenderEntity*)pFirstMember;
//					pRenderMember->SubmitRenderable( "main");
//				}
//				else if ( pFirstMember->GetType() == Entity::EM_ENTITY_LIGHT)
//				{
//					lightMgr->AddActiveLight( (ILight*)pFirstMember);
//				}
//
//				pFirstMember = pFirstMember->NextSearchLink();
//			}
//		}*/
//	//}
//
//	// ��ȡ��ӰͶ�����Χ��
//	void CQtMap::SetShadowCastBoundingBox()
//	{
//		ILiSPSM* lispsm = Root::GetRenderSystem()->GetLiSPSMManager();
//
//		//CRect3D castBoundingBox;
//		//GetBoundingBoxByLayer( castBoundingBox, "default", true);
//
//		Rect3 castaccept(0.f, 512.f, 0.f, 512.f,  0.f, 5.f);//= AABBCastAABB( castBoundingBox, lispsm->GetLightDir(), GetBoundingBox());
//
//		Root::GetRenderSystem()->GetLiSPSMManager()->SetShadowCastBoundingBox( castaccept);
//	}
//}