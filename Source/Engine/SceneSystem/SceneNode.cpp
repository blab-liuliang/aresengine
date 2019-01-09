//#include <Engine/SceneSystem/SceneNode.h>
//#include <Engine/SceneSystem/AresEntity.h>
//#include <Physics/Shapes/Algorithm/Intersect.h>
//
//namespace Ares
//{
//	// ���캯��
//	SceneNode::SceneNode()
//	{
//		// ����λ��
//		m_matWorld.SetIdentity();
//		m_matRotation.SetIdentity();
//
//		m_iEntityNum   = 0;
//		m_pEntityFirst = NULL;
//		m_pEntityLast  = NULL;
//
//		m_pSibling = NULL;
//		m_pChild   = NULL;
//
//		m_inheritance        = EM_INHERITANCE_ALL;
//
//		m_objectFlags        = 0;
//	}
//
//	// ��������
//	SceneNode::~SceneNode()
//	{
//		const s_ptr<SceneNode>& tParent = GetParent();
//		if( tParent)
//			tParent->DetachChild( this);
//
//		// ȥ�����Ĳ�����
//		//DetachFromQuadTree();
//	}
//
//	// �����ӽ��
//	s_ptr<SceneNode> SceneNode::CreateChildSceneNode()
//	{
//		s_ptr<SceneNode> pSceneNode = s_ptr<SceneNode>( new_ SceneNode);
//
//		this->AttachChild( pSceneNode.get());
//
//		return pSceneNode;
//	}
//
//	// ����ֵܽ��
//	void SceneNode::AddSibling( SceneNode* pSceneNode)
//	{
//		if( pSceneNode)
//		{
//			SceneNode* tNode = (SceneNode*)pSceneNode;
//
//			SceneNode* pLastSibling = tNode;
//			SceneNode* pSibling     = (SceneNode*)tNode->GetSibling();
//			while( pSibling)
//			{
//				pLastSibling = pSibling;
//				pSibling     = (SceneNode*)pSibling->GetSibling();
//			}
//
//			pLastSibling->SetSibling( m_pSibling);
//
//			m_pSibling = tNode; 
//		}
//	}
//
//	// ���ø����
//	void  SceneNode::SetParent( SceneNode* pParent) 
//	{ 
//		m_pParent = s_ptr<SceneNode>(pParent); 
//	}
//
//	// �����ӽ��
//	bool SceneNode::AttachChild(SceneNode* pChild)
//	{
//		if (pChild)
//		{
//			// �и����,ԭ�������ɾ���˽��
//			if (pChild->GetParent())
//			{
//				return false;
//			}
//
//			SceneNode* tChild = (SceneNode*)pChild;
//			// �ӽ���뵱ǰ�������ͬһ���� 
//			tChild->SetSibling(m_pChild);
//
//			m_pChild = pChild;
//			tChild->SetParent( this);
//		}
//
//		return true;
//	}
//
//	// �Ͽ��ӽ��
//	void SceneNode::DetachChild(SceneNode* pChild)
//	{
//		if (m_pChild && pChild)
//		{
//			SceneNode* tChild = (SceneNode*)pChild;
//
//			if (m_pChild == pChild)
//			{
//				m_pChild = tChild->GetSibling();
//
//				// �ֵܽ�㸸�����ΪNULL
//				tChild->SetSibling(NULL);		
//				tChild->SetParent(NULL);
//			}
//			
//			SceneNode* pTempNode = m_pChild;
//
//			// Ŀǰ��ζһ����; ��������������(��������������Ϊ������OGRE��Map����������)
//			while ( pTempNode && pTempNode->GetSibling() != tChild)
//			{
//				pTempNode = (SceneNode*)pTempNode->GetSibling();
//			}
//
//			// ��Ѱ���ӽ��
//			if (pTempNode)
//			{
//				pTempNode->SetSibling(tChild->GetSibling());
//
//				tChild->SetSibling(NULL);
//				tChild->SetParent(NULL);
//			}
//		}
//	}
//
//	// ����
//	void SceneNode::Update()
//	{
//		if ( !m_updateFlags.test( EM_IGNORE_ORIENTATION))
//		{
//			// has the orientation changed?
//			//if ( m_transform.IsLocalMatrixNew( /*m_localMatrix*/))
//			{
//				m_updateFlags.set( EM_NEW_LOCAL_MATRIX);
//			}
//		}
//
//		// derived classes update the local matrix then call this base function to complete the update
//		RecalcWorldMatrix();
//
//		RecalcWorldBounds();
//		//RefreshQuadTreeMembership();
//	}
//
//	// �ݹ����
//	void SceneNode::RecursiveUpdate()
//	{
//		// update my self
//		Update();
//
//		// update my sibling
//		SceneNode* pSibling = GetSibling();
//		if ( pSibling)
//		{
//			pSibling->RecursiveUpdate();
//		}
//
//		// update my child
//		SceneNode* pChild = GetChild();
//		if ( pChild)
//		{
//			pChild->RecursiveUpdate();
//		}
//
//		// clear the flags from the previous update
//		PrepareForUpdate();
//	}
//
//	// �����������
//	void SceneNode::RecalcWorldMatrix()
//	{
//		bool parentMoved = m_pParent && m_pParent->IsWorldMatrixNew();
//		BOOL weMoved     = m_updateFlags.test( EM_NEW_LOCAL_MATRIX);
//
//		if ( weMoved || parentMoved)
//		{
//			// multiply our local matrix by our parent
//			if ( m_pParent)
//			{
//				if ( m_inheritance = EM_INHERITANCE_ALL)
//				{
//					m_matWorld = m_transform.GetMatrix() * m_pParent->GetWorldMatrix();
//
//					// ������ת����
//					//m_matRotation = m_transform.m_matRotation * m_pParent->GetRotationMatrix();
//				}
//
//				//// ���̳и�����λ��
//				//else if ( m_inheritance == EM_INHERITANCE_POSITION_ONLY)
//				//{
//				//	const Matrix44& pMat = m_pParent->GetWorldMatrix();
//
//				//	Matrix44 parentMatrix;
//				//	parentMatrix.SetIdentity();
//
//				//	parentMatrix._41 = pMat._41;
//				//	parentMatrix._42 = pMat._42;
//				//	parentMatrix._43 = pMat._43;
//
//				//	m_matWorld = m_transform.Matrix() * parentMatrix;
//				//}
//
//				//// ���̳и������������ת
//				//else if ( m_inheritance == EM_INHERITANCE_ROTSCALE_ONLY)
//				//{
//				//	Matrix44 parentMatrix( m_pParent->GetWorldMatrix());
//				//	parentMatrix._41 = 0.0f;
//				//	parentMatrix._42 = 0.0f;
//				//	parentMatrix._43 = 0.0f;
//
//				//	m_matWorld = m_transform.Matrix() * parentMatrix;
//
//				//	// ������ת����
//				//	m_matRotation = m_transform.m_matRotation * m_pParent->GetRotationMatrix();
//				//}
//			}
//			else
//			{
//				m_matWorld = m_transform.GetMatrix();
//			}
//
//			// ����λ���
//			m_updateFlags.set( EM_NEW_WORLD_MATRIX);
//
//			// and it's inverse & vectors are out of data
//			m_updateFlags.set( EM_REBUILD_INVERSE_WORLD_MATRIX);
//			m_updateFlags.set( EM_REBUILD_WORLD_VECTORS);
//		}
//	}
//
//	// ���ñ��ذ�Χ��
//	void SceneNode::SetLocalBounds(Rect3& localBounds)
//	{
//		m_objectFlags.set(EM_NEW_LOCAL_BOUNDS);
//
//		m_localBounds = localBounds;
//	}
//
//	// ��ԭ�����ϸ��°�Χ�� 
//	void SceneNode::UnionLocalBounds( Rect3& unionBounds)
//	{
//		Rect3::Merge( m_localBounds, m_localBounds, unionBounds);
//	}
//
//	// ����ʵ��
//	void SceneNode::AttachObject(Entity* entity)
//	{
//		if ( entity)
//		{		
//			// �����Χ��
//			Rect3 newEntityRect = entity->GetLocalBounds();
//
//			// �Ӻ������ʵ��
//			if ( m_pEntityLast)
//			{
//				m_pEntityLast->SetRearSearchLink( entity);
//				entity->SetForwardSearchLink( m_pEntityLast);
//				m_pEntityLast = entity;
//				m_iEntityNum++;
//
//				m_localBounds.UnionPoint( newEntityRect.GetMinPoint());
//				m_localBounds.UnionPoint( newEntityRect.GetMaxPoint());
//			}
//			else
//			{
//				m_localBounds = newEntityRect;
//
//				m_pEntityFirst = entity;
//				m_pEntityLast  = entity;
//				m_iEntityNum   = 1;
//			}
//		}
//
//		m_objectFlags.set( EM_NEW_LOCAL_BOUNDS);
//
//		// �������������Χ��
//		RecalcWorldBounds();
//	}
//
//	// ɾ��ʵ��
//	void SceneNode::DetachObject( Entity* pEntity)
//	{
//		// ��ǰδ�����ʵ�����
//		m_iEntityNum--;
//
//		//if ( m_iEntityNum == 0)
//		//{
//		//	// �����Ĳ�������
//		//	DetachFromQuadTree();
//
//		//	// ��������
//		//	DetachParent();
//
//		//	// ɾ���Լ�
//		//	delete this;
//		//}	
//	}
//
//	// ׼������
//	void SceneNode::PrepareForUpdate()
//	{
//		m_updateFlags.reset();
//		m_objectFlags.reset();
//	}
//
//	// ��ȡ��Χ��
//	const Rect3& SceneNode::GetWorldBounds() 
//	{ 
//		RecalcWorldBounds(); 
//		
//		return m_worldBounds; 
//	}
//
//	// ���¼����Χ��
//	void SceneNode::RecalcWorldBounds()
//	{
//		// nodes only get their bounds updated as nessesary
//		if ( m_objectFlags.test(EM_NEW_LOCAL_BOUNDS) || IsWorldMatrixNew())
//		{
//			m_worldBounds = m_localBounds;
//
//			m_worldBounds.Transform( &GetWorldMatrix());
//
//			m_objectFlags.set( EM_NEW_WORLD_BOUNDS);
//		}
//	}
//}