//#include "QtGPWorld.h"
//#include "SceneTile.h"
//#include "Engine/AresRoot.h"
//
//namespace Ares
//{
//	// ���캯��
//	CQtGPWorld::CQtGPWorld()
//		: CGPWorld()
//	{
//		//m_terrain = NULL;
//	}
//
//	//// ���÷�Χ
//	//void  CQtGPWorld::SetWorldLimits( const Scene::SSize& size, const CGPIndex& gpIdx)
//	//{
//	//	m_mainGPIdx = gpIdx;
//
//	//	m_xTiles = size.m_width / gpIdx.GetWidth();
//	//	m_yTiles = size.m_height/ gpIdx.GetHeight();
//
//	//	m_size	 = size;
//
//	//	//Rect3 boundingBox;
//	//	//boundingBox.x0 = (float)size.m_posX;
//	//	//boundingBox.x1 = (float)(size.m_posX + size.m_width);
//	//	//boundingBox.y0 = (float)size.m_posY;
//	//	//boundingBox.y1 = (float)(size.m_posY + size.m_height);
//	//	//boundingBox.z0 = -1024.f;
//	//	//boundingBox.z1 =  1024.f;
//
//	//	//m_collMap.SetBoundingBox( boundingBox);
//	//}
//
//	// �������ڵ�
//	//void CQtGPWorld::SetRootNode( const s_ptr<SceneNode>& rootNode) 
//	//{	
//	//	m_rootNode = rootNode; 
//
//	//	// ѭ��30֡ÿ��
//	//	//Start( 10);
//	//}
//
//	//// ���ʵ��
//	//bool CQtGPWorld::AddEntity( const char* uniqueName, s_ptr<Entity> pEntity)
//	//{
//	//	if( !pEntity)
//	//		return false;
//
//	//	// ��ӵ�������
//	//	const Rect3& worldbounds = pEntity->GetSceneNode()->GetWorldBounds();
//
//	//	int minX  = ((int)worldbounds.x0 - m_size.m_posX) / m_mainGPIdx.GetWidth();
//	//	int maxX = ((int)worldbounds.x1 - m_size.m_posX) / m_mainGPIdx.GetWidth();
//	//	int minY  = ((int)worldbounds.y0 - m_size.m_posY) / m_mainGPIdx.GetHeight();
//	//	int maxY = ((int)worldbounds.y1 - m_size.m_posY) / m_mainGPIdx.GetHeight();
//
//	//	ENTER_CRITICAL_SECTION( tHoder, m_qtCritication);
//	//	m_entiys[uniqueName] = pEntity;
//	//	pEntity->SetName( uniqueName);
//
//	//	for ( int i=minX; i<=maxX; i++)
//	//	{
//	//		for( int j=minY; j<=maxY; j++)
//	//		{
//	//			CGPIndex tIdx = m_mainGPIdx.GetIndex( i, j);
//	//			SceneTile* pTile = (SceneTile*)this->GetTile( tIdx);
//
//	//			if( pTile)
//	//			{
//	//				pTile->AddEntity( uniqueName, pEntity);
//	//			}
//	//		}
//	//	}
//
//	//	return true;
//	//}
//
//	//// ���ʵ��
//	//bool CQtGPWorld::AddEntityToWorldOnly( const char* uniqueName, s_ptr<Entity> pEntity)
//	//{
//	//	ENTER_CRITICAL_SECTION( tHoder, m_qtCritication);
//	//	pEntity->SetName( uniqueName);
//	//	m_entiys[uniqueName] = pEntity;
//
//	//	return true;
//	//}
//
//	// �����ײ����ײͼ��
//	//void CQtGPWorld::AddCollMesh( const char* uniqueName, BvhTriangleMesh* mesh)
//	//{
//		//CCollMap& collmap = m_scene->GetCollMap();
//
//		//ENTER_CRITICAL_SECTION( tHoder, m_qtCritication);
//
//		//collmap.AddCollMesh( uniqueName, mesh); 
//	//}
//
//	//// ����ʵ������ȡʵ��
//	//s_ptr<Entity> CQtGPWorld::GetEntity( const char* uniqueName)
//	//{
//	//	ENTER_CRITICAL_SECTION( tHoder, m_qtCritication);
//
//	//	EntityList::const_iterator it = m_entiys.find( uniqueName);
//	//	if( it != m_entiys.end())
//	//	{
//	//		return it->second;
//	//	}
//
//	//	return s_ptr<Entity>();
//	//}
//
//	//// ��Ӧ�����������Ƿ����
//	//bool CQtGPWorld::IsValidIndex( const CGPIndex& index)
//	//{
//	//	if( index.GetX() < m_xTiles && index.GetY() < m_yTiles)
//	//		return true;
//
//	//	return false;
//	//}
//
//	//// ����Tile
//	//CGPTile* CQtGPWorld::BuildTile( const CGPIndex& index)
//	//{
//	//	if( !IsValidIndex( index))
//	//		return 0;
//
//	//	// tile�ļ����·��
//	//	char tileLocation[256];
//	//	sprintf( tileLocation,"%s%d_%d.tile", m_location.c_str(), index.GetX(), index.GetY());
//
//	//	SceneTile* pTile = new_ SceneTile( tileLocation);
//
//	//	return pTile;
//	//}
//
//	//// ����Tile
//	//void  CQtGPWorld::DestroyTile( const CGPIndex& index)
//	//{
//	//	CGPWorld::DestroyTile( index);
//
//	//	ENTER_CRITICAL_SECTION( tHoder, m_qtCritication);
//
//	//	// ������ü���Ϊ1��ʵ��
//	//	for( EntityList::const_iterator it=m_entiys.begin(); it!=m_entiys.end(); )
//	//	{
//	//		// �����������
//	//		if( m_terrain)
//	//		{
//	//			s_ptr<TerrainTile> tile = boost::dynamic_pointer_cast<TerrainTile>( it->second);
//	//			if( tile)
//	//				m_terrain->DestroyTile( tile);
//	//		}
//
//	//		// ���ʵ��
//	//		if( it->second.unique())
//	//			it = m_entiys.erase(it);
//	//		else
//	//			++it;
//	//	}
//	//}
//
//	//// ��ȡ��Χ��
//	//bool CQtGPWorld::GetBoundingBoxByLayer( Rect3& box, const char* layer, bool update)
//	//{
//	//	if( !update)
//	//	{
//	//		int a = 10;
//	//	}
//	//	else
//	//	{
//	//		for( GPTileMap::const_iterator it=m_tilesMap.begin(); it!=m_tilesMap.end(); it++)
//	//		{
//	//			SceneTile* qtGPTile = (SceneTile*)it->second;
//
//	//			qtGPTile->GetBoundingBoxByLayer( box, layer, update);
//	//		}
//	//	}
//
//	//	return true;
//	//}
//
//	//// ����
//	//void CQtGPWorld::Save()
//	//{
//	//	for( GPTileMap::const_iterator it=m_tilesMap.begin(); it!=m_tilesMap.end(); it++)
//	//	{
//	//		SceneTile* qtGPTile = (SceneTile*)it->second;
//	//		
//	//		qtGPTile->Save();
//	//	}
//	//}
//
//	// ����ʵ��
//	//void CQtGPWorld::FrameMove( float elapsedTime)
//	//{
//	//	for( EntityList::iterator it = m_entiys.begin(); it!=m_entiys.end(); it++)
//	//	{
//	//		it->second->FrameMove( elapsedTime);
//	//	}
//	//}
//
//	// �鷽��,������ʵ��
//	//void CQtGPWorld::Loop()
//	//{
//		//CGPWorld::Loop();
//
//		//ENTER_CRITICAL_SECTION( tHoder, m_rtCritication);
//		//m_rootNode->RecursiveUpdate();
//	//}
//
//	//// ���õ���
//	//void CQtGPWorld::SetTerrain( Terrain* terrain) 
//	//{ 
//	//	m_terrain = terrain; 
//
//	//	if( m_terrain)
//	//		m_terrain->SetRootNode( m_rootNode);
//
//	//	//m_collMap.SetHeightField( &m_terrain->GetHeightField());
//	//}
//
//
//	//// �����������
//	//void CQtGPWorld::SaveTerrain( const char* terLocation)
//	//{
//	//	char tTerLocation[512];
//	//	changeExt( tTerLocation, terLocation, ".ter");
//	//	if( m_terrain)
//	//	{
//	//		m_terrain->Save( tTerLocation);
//	//	}
//	//}
//
//	//// ���ص�������
//	//void  CQtGPWorld::LoadTerrain( const char* terLocation)
//	//{
//	//	char tTerLocation[512];
//	//	changeExt( tTerLocation, terLocation, ".ter");
//	//	if( INVALID_FILE_ATTRIBUTES != GetFileAttributesA( tTerLocation))
//	//	{
//	//		// ���ڵ���
//	//		Terrain*  pTerrain = AResSystem.MakeTerrain();
//	//		if( pTerrain)
//	//		{
//	//			SetTerrain( pTerrain);
//
//	//			pTerrain->Load( tTerLocation);
//	//		}
//	//	}
//	//}
//}