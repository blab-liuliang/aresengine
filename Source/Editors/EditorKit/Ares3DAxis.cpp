#include "Ares3DAxis.h"
#include <Physics/Intersect.h>
#include <Physics/IntrLine3Box3.h>
#include <Physics/IntrLine3Plane3.h>
#include <Engine/AresRoot.h>

namespace Ares
{
	// ���������н�
	static float AresTwoLineAngle( const Vector3& lineFirst, const Vector3& lineSecond)
	{
		float length = lineFirst.Length() * lineSecond.Length();
		if ( length == 0.0f)
		{
			return 0.0f;
		}

		length = Vector3Dot( lineFirst, lineSecond) / length;
		length = max(-1.0f, length);
		length = min(1.0f,  length);

		return acos(length);
	}

	// �����ƶ�
	static float TranslateOnAxis(const Vector3& rayPos0, const Vector3& rayDir0, const Vector3& rayPos1, const Vector3& rayDir1,
		const Vector3& entityPos, const Vector3& translateAxis)
	{
		// ���
		float result = 0.0f;

		// ���淨��
		Vector3 rayAssistant;
		rayAssistant = Vector3Cross( rayDir0, rayDir1);
		rayAssistant.Normalize();
		float test = Vector3Dot( rayAssistant, translateAxis) / (rayAssistant.Length() * translateAxis.Length());

		// ���صľ�������
		if (  test > 0.3f || test<-0.3f)
		{
			return result;
		}

		rayAssistant = Vector3Cross( rayAssistant, translateAxis);
		rayAssistant.Normalize();

		// ���ƽ��
		if ( !rayAssistant.Length())
		{
			return result;
		}

		// ���ݵ��뷨��ȷ����
		Plane3   axisPlane( entityPos, rayAssistant);
		axisPlane.Normalize();

		// ������������ཻ��
		Line3 line0( rayPos0, rayDir0);
		Line3 line1( rayPos1, rayDir1);
		IntrLine3Plane3 intrLP0( line0, axisPlane);
		IntrLine3Plane3 intrLP1( line1, axisPlane);
		if( !intrLP0.Test() || !intrLP1.Test())
			return result;

		Vector3 pointBegin = intrLP0.m_intrPoint; 
		Vector3 pointEnd   = intrLP1.m_intrPoint; 

		// �����ƶ�����ͶӰ����
		Vector3 rayMove = pointEnd - pointBegin;
		result = Vector3Dot( rayMove, translateAxis) / translateAxis.Length();

		return result;
	}

	// ��ƽ�����ƶ�, ������ƽ�治�ཻ return NULL
	static Vector3* TranslateOnPlane( Vector3* pOut, const Plane3& plane, const Vector3& rayPos0, const Vector3& rayDir0, const Vector3& rayPos1, const Vector3& rayDir1)
	{
		// ������������ཻ��
		Line3 line0( rayPos0, rayDir0);
		Line3 line1( rayPos1, rayDir1);
		IntrLine3Plane3 intrLP0( line0, plane);
		IntrLine3Plane3 intrLP1( line1, plane);
		if( !intrLP0.Test() || !intrLP1.Test())
		{
			*pOut = Vector3::Zero;

			return NULL;
		}

		Vector3 pointBegin = intrLP0.m_intrPoint; 
		Vector3 pointEnd   = intrLP1.m_intrPoint; 

		// �����ƶ�����ͶӰ����
		*pOut = pointEnd - pointBegin; 

		return pOut;
	}

	// ��ƽ������ת,���������ת����(��һ���������ؽǶ�,)
	static float RotateOnPlane( const Vector3& planePoint, const Vector3& planeNormal, const Vector3& rayPos0, const Vector3& rayDir0, const Vector3& rayPos1, const Vector3& rayDir1)
	{
		// ���ݵ�������ȷ����
		Plane3   rotatePlane( planePoint, planeNormal);
		Line3 line0( rayPos0, rayDir0);
		Line3 line1( rayPos1, rayDir1);
		IntrLine3Plane3 intrLP0( line0, rotatePlane);
		IntrLine3Plane3 intrLP1( line1, rotatePlane);
		if( !intrLP0.Test() || !intrLP1.Test())
			return 0.f;

		Vector3 pointBegin = intrLP0.m_intrPoint; 
		Vector3 pointEnd   = intrLP1.m_intrPoint; 

		// ����ת�Ƕ�
		Matrix44 pOut;
		float tpAngle = AresTwoLineAngle( pointBegin - planePoint, pointEnd - planePoint);
		Matrix44RotationAxisAngle( pOut, planeNormal, tpAngle);

		// �Ƕ�����
		Vector3 normal;
		normal = Vector3Cross( planePoint - pointBegin, pointEnd - planePoint);
		if ( Vector3Dot( normal, planeNormal) < 0.0f)
		{
			tpAngle = -tpAngle;
		}

		return tpAngle;
	}

	// ���캯��
	CAres3DAxis::CAres3DAxis( VisualShapeMgr& visualShapeMgr)
	{
		m_fScale = 1.f;

		m_editType   = EM_EDIT_TRANSLATE;
		m_rotateType = EM_ROTATE_NULL;
		m_moveType   = EM_MOVE_NULL;
		m_vPosition  = Vector3::Zero;
		m_bVisible = false;

		// ָ��������ĳ���
		m_vAxisDir[0] = Vector3( 1.0f, 0.0f, 0.0f);
		m_vAxisDir[1] = Vector3( 0.0f, 1.0f, 0.0f);
		m_vAxisDir[2] = Vector3( 0.0f, 0.0f, 1.0f);

		for ( int i=0; i<3; i++)
		{
			m_pAxes[i] = visualShapeMgr.CreateSegment( 5);
			m_pPlaneLine[i] = visualShapeMgr.CreateSegment( 5);
			m_pPlaneLine[3+i] = visualShapeMgr.CreateSegment( 5);
			m_pAxes[i]->SetVisible( false);
			m_pPlaneLine[i]->SetVisible( false);
			m_pPlaneLine[3+i]->SetVisible( false);

			//m_pAxes[i]->SetSizeFixed( true);
			//m_pPlaneLine[i]->SetSizeFixed( true);
			//m_pPlaneLine[3+i]->SetSizeFixed( true);
		}


		// ���ò���
		m_pAxes[0]->Set( 0.0f, 0.0f, 0.0f, 1.0f , 0.0f, 0.0f);
		m_pAxes[1]->Set( 0.0f, 0.0f, 0.0f, 0.0f,  1.0f, 0.0f);
		m_pAxes[2]->Set( 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,  1.0f);
		m_pPlaneLine[0]->Set( 0.4f, 0.0f, 0.0f, 0.4f , 0.4f, 0.0f);
		m_pPlaneLine[1]->Set( 0.4f, 0.4f, 0.0f, 0.0f,  0.4f, 0.0f);
		m_pPlaneLine[2]->Set( 0.0f, 0.4f, 0.0f, 0.0f, 0.4f,  0.4f);
		m_pPlaneLine[3]->Set( 0.0f, 0.4f, 0.4f, 0.0f , 0.0f, 0.4f);
		m_pPlaneLine[4]->Set( 0.4f, 0.0f, 0.4f, 0.0f, 0.0f,  0.4f);
		m_pPlaneLine[5]->Set( 0.4f, 0.0f, 0.0f, 0.4f,  0.0f, 0.4f);

		// ������ɫ
		m_pAxes[0]->SetColor( 0xFFFF0000);
		m_pAxes[1]->SetColor( 0xFF00FF00);
		m_pAxes[2]->SetColor( 0xFF0000FF);
		m_pPlaneLine[0]->SetColor( 0xFFFF0000);
		m_pPlaneLine[1]->SetColor( 0xFF00FF00);
		m_pPlaneLine[2]->SetColor( 0xFF00FF00);
		m_pPlaneLine[3]->SetColor( 0xFF0000FF);
		m_pPlaneLine[4]->SetColor( 0xFF0000FF);
		m_pPlaneLine[5]->SetColor( 0xFFFF0000);

		// ����Բ׶
		for ( int i=0; i<3; i++)
		{
			m_pCone[i] = visualShapeMgr.CreateCone( 5);	
			m_pCone[i]->SetRadiusAndHeight( 0.1f, 0.6f);
			m_pCone[i]->SetFace( m_vAxisDir[i]);
			m_pCone[i]->SetVisible( false);
			//m_pCone[i]->SetSizeFixed( true);
		}

		// ������ɫ
		m_pCone[0]->SetColor( 0xFFFF0000);
		m_pCone[1]->SetColor( 0xFF00FF00);
		m_pCone[2]->SetColor( 0xFF0000FF);

		// ����Բ
		for ( int i=0; i<3; i++)
		{
			m_pCycle[i] = visualShapeMgr.CreateCycle( 5);
			m_pCycle[i]->SetRadius( 1.0f);
			m_pCycle[i]->SetFace( m_vAxisDir[i]);
			m_pCycle[i]->SetVisible( false);
			//m_pCycle[i]->SetSizeFixed( true);
		}

		m_pCycle[0]->SetColor( 0xFFFF0000);
		m_pCycle[1]->SetColor( 0xFF00FF00);
		m_pCycle[2]->SetColor( 0xFF0000FF);

		// ����
		m_pScale = visualShapeMgr.CreateVisualShape( 5);
		Vector3 positions[] =
		{
			Vector3( 0.5f, 0.0f, 0.0f),
			Vector3( 0.0f, 0.5f, 0.0f),
			Vector3( 0.0f, 0.0f, 0.5f),
		};

		WORD  indices[] = { 0, 1, 2 };

		m_pScale->Set( RenderLayout::TT_TriangleList, positions, sizeof(positions), indices, sizeof(indices), EF_R16UI);
		m_pScale->SetColor( 0xFF33AAFF);
		m_pScale->SetVisible( false);
		//m_pScale->SetSizeFixed( true);

		// ��ʼ����Ⱦ״̬
		InitRenderState();
	}

	// ��ʼ����Ⱦ״̬
	void CAres3DAxis::InitRenderState()
	{
		// ���ù�դ��״̬
		DepthStencilStateDesc desc;
		desc.m_depthFun = CF_Always;
		DepthStencilStatePtr depthStencilState = ARenderDevice->CreateDepthStencilState( desc);
		for ( int i=0; i<3; i++)
		{
			m_pAxes[i]->GetMaterial()->SetDepthStencilState( depthStencilState);
			m_pPlaneLine[i]->GetMaterial()->SetDepthStencilState( depthStencilState);
			m_pPlaneLine[3+i]->GetMaterial()->SetDepthStencilState( depthStencilState);
			m_pCone[i]->GetMaterial()->SetDepthStencilState( depthStencilState);
			m_pCycle[i]->GetMaterial()->SetDepthStencilState( depthStencilState);
		}
	}

	// �����ӵ� 
	void CAres3DAxis::CatchEntity( Entity* enity)
	{
		if ( enity)
			m_entityList.push_back( enity);
	}

	// ����VisualShape
	void CAres3DAxis::CatchTransform( Transform* vs)
	{
		if( vs)
			m_transforms.push_back( vs);
	}

	// ����ƶ�
	void CAres3DAxis::OnMouseMove( const Vector3& rayOrig0, const Vector3& rayDir0, const Vector3& rayOrig1, const Vector3& rayDir1 ,POINT* ptPre/*=NULL*/, POINT* ptCurr/*=NULL*/)
	{
		if ( m_bVisible)
		{
			switch( m_editType)
			{
			case EM_EDIT_TRANSLATE:
				{
					// �ƶ�
					float       fDist = 0.0f;
					Vector3 relaTrans;
					switch( m_moveType)
					{
					case EM_MOVE_X:
						{
							fDist = TranslateOnAxis( rayOrig0, rayDir0, rayOrig1, rayDir1, m_vPosition, m_vAxisDir[EM_MOVE_X]);
							relaTrans = fDist * m_vAxisDir[ EM_MOVE_X];
						}
						break;
					case EM_MOVE_Y:
						{
							fDist = TranslateOnAxis( rayOrig0, rayDir0, rayOrig1, rayDir1, m_vPosition, m_vAxisDir[EM_MOVE_Y]);
							relaTrans = fDist * m_vAxisDir[ EM_MOVE_Y];
						}
						break;
					case EM_MOVE_Z:
						{
							fDist = TranslateOnAxis( rayOrig0, rayDir0, rayOrig1, rayDir1, m_vPosition, m_vAxisDir[EM_MOVE_Z]);
							relaTrans = fDist * m_vAxisDir[ EM_MOVE_Z];
						}
						break;
					case EM_MOVE_XYPLANE:
						{
							Plane3 plane( m_vPosition, m_vAxisDir[EM_MOVE_Z]);
							TranslateOnPlane( &relaTrans, plane, rayOrig0, rayDir0, rayOrig1, rayDir1);
						}
						break;
					case EM_MOVE_YZPLANE:
						{
							Plane3 plane( m_vPosition, m_vAxisDir[EM_MOVE_X]);
							TranslateOnPlane( &relaTrans, plane, rayOrig0, rayDir0, rayOrig1, rayDir1);
						}
						break;
					case EM_MOVE_XZPLANE:
						{
							Plane3 plane( m_vPosition, m_vAxisDir[EM_MOVE_Y]);
							TranslateOnPlane( &relaTrans, plane, rayOrig0, rayDir0, rayOrig1, rayDir1);
						}
						break;
					default:
						{
							return;
						}
					}

					Translate( relaTrans);
				}
				break;
			case EM_EDIT_ROTATE:
				{
					float fAngle0 = 0.0f;
					float fAngle1 = 0.0f;
					float fAngle2 = 0.0f;

					switch( m_rotateType)
					{
					case EM_ROTATE_X:
						{
							fAngle0 = RotateOnPlane( m_vPosition, m_vAxisDir[0], rayOrig0, rayDir0, rayOrig1, rayDir1);
						}
						break;
					case EM_ROTATE_Y:
						{
							fAngle1 = RotateOnPlane( m_vPosition, m_vAxisDir[1], rayOrig0, rayDir0, rayOrig1, rayDir1);
						}
						break;
					case EM_ROTATE_Z:
						{
							fAngle2 = RotateOnPlane( m_vPosition, m_vAxisDir[2], rayOrig0, rayDir0, rayOrig1, rayDir1);
						}
						break;
					}

					// ��ת����ģ��
					for ( size_t i=0; i<m_entityList.size(); i++)
					{
						Transform tranform = m_entityList[i]->GetTransform();
						tranform.AddRotation( m_vAxisDir[0], fAngle0);
						tranform.AddRotation( m_vAxisDir[1], fAngle1);
						tranform.AddRotation( m_vAxisDir[2], fAngle2);

						m_entityList[i]->SetTransform( tranform);
					}

					// ��ת����ģ��
					for ( size_t i=0; i<m_transforms.size(); i++)
					{
						m_transforms[i]->AddRotation( m_vAxisDir[0], fAngle0);
						m_transforms[i]->AddRotation( m_vAxisDir[1], fAngle1);
						m_transforms[i]->AddRotation( m_vAxisDir[2], fAngle2);
					}
				}
				break;

			case EM_EDIT_SCALE:
				{
					// ��������ģ��
					for ( size_t i=0; i<m_entityList.size(); i++)
					{
						Transform tranform = m_entityList[i]->GetTransform();
						float scale = tranform.GetScale().x - 0.002f * ( ptPre->y - ptCurr->y);
						tranform.SetScale( scale);

						m_entityList[i]->SetTransform( tranform);
					}

					// ��ת����ģ��
					for ( size_t i=0; i<m_transforms.size(); i++)
					{
						float scale = m_transforms[i]->GetScale().x - 0.002f * ( ptPre->y - ptCurr->y);
						m_transforms[i]->SetScale( scale);
					}
				}
				break;
			}
		}
	}

	// ������ײ������λ��
	void CAres3DAxis::UpdateTranslateCollBox()
	{
		m_moveBoxs[EM_MOVE_X].Set( m_vPosition+Vector3( 1.f, 0.f, 0.f), Vector3::XAxis, Vector3::YAxis, Vector3::ZAxis, 0.60f, 0.15f, 0.15f);
		m_moveBoxs[EM_MOVE_Y].Set( m_vPosition+Vector3( 0.f, 1.f, 0.f), Vector3::XAxis, Vector3::YAxis, Vector3::ZAxis, 0.15f, 0.60f, 0.15f);
		m_moveBoxs[EM_MOVE_Z].Set( m_vPosition+Vector3( 0.f, 0.f, 1.f), Vector3::XAxis, Vector3::YAxis, Vector3::ZAxis, 0.15f, 0.15f, 0.60f);
		m_moveBoxs[EM_MOVE_XYPLANE].Set( m_vPosition+Vector3( 0.2f, 0.2f, 0.0f), Vector3::XAxis, Vector3::YAxis, Vector3::ZAxis, 0.2f, 0.2f, 0.05f);
		m_moveBoxs[EM_MOVE_YZPLANE].Set( m_vPosition+Vector3( 0.0f, 0.2f, 0.2f), Vector3::XAxis, Vector3::YAxis, Vector3::ZAxis, 0.05f, 0.2f, 0.2f);
		m_moveBoxs[EM_MOVE_XZPLANE].Set( m_vPosition+Vector3( 0.2f, 0.0f, 0.2f), Vector3::XAxis, Vector3::YAxis, Vector3::ZAxis, 0.2f, 0.05f, 0.2f);
	}

	// ��ѡȡ
	bool CAres3DAxis::OnMouseDown( const Vector3& rayOrig, const Vector3& rayDir)
	{
		if ( m_bVisible)
		{
			switch( m_editType)
			{
			case EM_EDIT_TRANSLATE:
				{
					m_moveType = EM_MOVE_NULL;
					Line3 line( rayOrig, rayDir);
					for( int i=EM_MOVE_X; i<=EM_MOVE_XZPLANE; i++)
					{
						IntrLine3Box3 intrLB( line, m_moveBoxs[i]);
						if( intrLB.Test())
						{
							m_moveType = EMoveType(i);
							break;
						}
					}

					// ������ʾ
					switch( m_moveType)
					{
					case EM_MOVE_X:
						{
							m_pAxes[0]->SetColor( 0xFFFFFFFF);
							m_pCone[0]->SetColor( 0xFFFFFFFF);
						}
						break;
					case EM_MOVE_Y:
						{
							m_pAxes[1]->SetColor( 0xFFFFFFFF);
							m_pCone[1]->SetColor( 0xFFFFFFFF);
						}
						break;
					case EM_MOVE_Z:
						{
							m_pAxes[2]->SetColor( 0xFFFFFFFF);
							m_pCone[2]->SetColor( 0xFFFFFFFF);
						}
						break;
					case EM_MOVE_XYPLANE:
						{
							m_pPlaneLine[0]->SetColor( 0xFFFFFFFF);
							m_pPlaneLine[1]->SetColor( 0xFFFFFFFF);
						}
						break;
					case EM_MOVE_YZPLANE:
						{
							m_pPlaneLine[2]->SetColor( 0xFFFFFFFF);
							m_pPlaneLine[3]->SetColor( 0xFFFFFFFF);
						}
						break;
					case EM_MOVE_XZPLANE:
						{
							m_pPlaneLine[4]->SetColor( 0xFFFFFFFF);
							m_pPlaneLine[5]->SetColor( 0xFFFFFFFF);
						}
						break;
					}
				}
				break;
			case EM_EDIT_ROTATE:
				{
					float fLastDist = 1e30f;
					float fDist;
					Vector3 intersectPos;
					Plane3 plane;
					m_rotateType = EM_ROTATE_NULL;

					// ѡ��
					for ( int i=0; i<3; i++)
					{
						Line3 ray( rayOrig, rayDir);
						Plane3 plane( m_vPosition, m_vAxisDir[i]);
						IntrLine3Plane3 intrLP(ray, plane );
						if ( intrLP.Test())
						{
							fDist		 = intrLP.m_distance;
							intersectPos = intrLP.m_intrPoint;
							if ( ( intersectPos-m_vPosition).Length() > 0.8f*m_fScale && ( intersectPos-m_vPosition).Length() < 1.2f*m_fScale )
							{
								if ( i==0) m_rotateType = EM_ROTATE_X;
								if ( i==1) m_rotateType = EM_ROTATE_Y;
								if ( i==2) m_rotateType = EM_ROTATE_Z;

								fLastDist = fDist;

								break;
							}
						}
					}

					// ��ʾ
					switch( m_rotateType)
					{
					case EM_ROTATE_X:
						m_pCycle[0]->SetColor( 0xFFFFFFFF);
						break;
					case EM_ROTATE_Y:
						m_pCycle[1]->SetColor( 0xFFFFFFFF);
						break;
					case EM_ROTATE_Z:
						m_pCycle[2]->SetColor( 0xFFFFFFFF);
						break;
					}
				}
				break;
			case EM_EDIT_SCALE:
				{
					Triangle3 triangle( m_vPosition, m_vPosition, m_vPosition);
					triangle.m_v[0].x += 0.5f*m_fScale; triangle.m_v[1].y += 0.5f*m_fScale; triangle.m_v[2].z += 0.5f*m_fScale;
					Line3 line3( rayOrig, rayDir);
					float fdist;

					if ( Intersect( line3, triangle, fdist))
					{
						m_pScale->SetColor( 0xFFFFFFFF);
					}
				}
				break;
			}
		}

		return false;
	}

	// ȡ��ѡ��
	void CAres3DAxis::OnMouseUp()
	{
		if ( m_bVisible)
		{
			switch( m_editType)
			{
			case EM_EDIT_TRANSLATE:
				{
					// ������ʾ
					switch( m_moveType)
					{
					case EM_MOVE_X:
						{
							m_pAxes[0]->SetColor( 0xFFFF0000);
							m_pCone[0]->SetColor( 0xFFFF0000);
						}
						break;
					case EM_MOVE_Y:
						{
							m_pAxes[1]->SetColor( 0xFF00FF00);
							m_pCone[1]->SetColor( 0xFF00FF00);
						}
						break;
					case EM_MOVE_Z:
						{
							m_pAxes[2]->SetColor( 0xFF0000FF);
							m_pCone[2]->SetColor( 0xFF0000FF);
						}
						break;
					case EM_MOVE_XYPLANE:
						{
							m_pPlaneLine[0]->SetColor( 0xFFFF0000);
							m_pPlaneLine[1]->SetColor( 0xFF00FF00);
						}
						break;
					case EM_MOVE_YZPLANE:
						{
							m_pPlaneLine[2]->SetColor( 0xFF00FF00);
							m_pPlaneLine[3]->SetColor( 0xFF0000FF);
						}
						break;
					case EM_MOVE_XZPLANE:
						{
							m_pPlaneLine[4]->SetColor( 0xFF0000FF);
							m_pPlaneLine[5]->SetColor( 0xFFFF0000);
						}
						break;
					}
				}
				break;
			case EM_EDIT_ROTATE:
				{
					m_pCycle[0]->SetColor( 0xFFFF0000);
					m_pCycle[1]->SetColor( 0xFF00FF00);
					m_pCycle[2]->SetColor( 0xFF0000FF);
				}
				break;
			case EM_EDIT_SCALE:
				{
					m_pScale->SetColor( 0xFF33AAFF);
				}
				break;
			}
		}

		m_moveType   = EM_MOVE_NULL;
		m_rotateType = EM_ROTATE_NULL;
	}

	// ����λ��
	void CAres3DAxis::SetPosition( float _posX, float _posY, float _posZ)
	{
		m_vPosition.x = _posX;
		m_vPosition.y = _posY;
		m_vPosition.z = _posZ;

		for ( int i=0; i<3; i++)
		{
			m_pAxes[i]->GetTransform()->SetTrans( _posX, _posY, _posZ);
			m_pPlaneLine[i]->GetTransform()->SetTrans( _posX, _posY, _posZ);
			m_pPlaneLine[i+3]->GetTransform()->SetTrans( _posX, _posY, _posZ);
			m_pCycle[i]->GetTransform()->SetTrans( _posX, _posY, _posZ);
		}

		// ����λ��
		m_pCone[0]->GetTransform()->SetTrans( m_fScale + m_vPosition.x, m_vPosition.y, m_vPosition.z);
		m_pCone[1]->GetTransform()->SetTrans( m_vPosition.x, m_fScale + m_vPosition.y, m_vPosition.z);
		m_pCone[2]->GetTransform()->SetTrans( m_vPosition.x, m_vPosition.y, m_fScale + m_vPosition.z);

		m_pScale->GetTransform()->SetTrans( _posX, _posY, _posZ);

		// ������ײ������λ��
		UpdateTranslateCollBox();
	}

	// ����λ��
	void CAres3DAxis::SetPosition( const Vector3& pos)
	{
		this->SetPosition( pos.x, pos.y, pos.z);
	}

	// �����Ƿ�ɼ�
	void CAres3DAxis::SetVisible(bool visible)
	{
		// ���ؼ�¼
		m_bVisible = visible;

		switch( m_editType)
		{
		case EM_EDIT_TRANSLATE:
			{
				for (int i=0; i<3; i++)
				{
					m_pAxes[i]->SetVisible( visible);
					m_pPlaneLine[i]->SetVisible( visible);
					m_pPlaneLine[3+i]->SetVisible( visible);
					m_pCone[i]->SetVisible( visible);
				}
			}
			break;
		case EM_EDIT_ROTATE:
			{
				for ( int i=0; i<3; i++)
				{
					m_pCycle[i]->SetVisible( visible);
				}
			}
			break;
		case EM_EDIT_SCALE:
			{
				for (int i=0; i<3; i++)
				{
					m_pAxes[i]->SetVisible( visible);
					m_pCone[i]->SetVisible( visible);
					m_pScale->SetVisible( visible);
				}
			}
			break;
		}
	}

	// �ƶ�
	void  CAres3DAxis::Translate( const Vector3& trans)
	{
		if( trans!=Vector3::Zero)
		{
			Vector3 pos = m_vPosition + trans;

			// ��������λ��
			this->SetPosition( pos);

			// ��������ģ��λ��
			for ( size_t i=0; i<m_entityList.size(); i++)
			{
				Transform transform = m_entityList[i]->GetTransform();
				Vector3 newPosition = transform.GetTrans() + trans;
				//newPosition.x = (int)(newPosition.x * 50) * 0.02f;
				//newPosition.y = (int)(newPosition.y * 50) * 0.02f;
				//newPosition.z = (int)(newPosition.z * 50) * 0.02f;
				transform.SetTrans( newPosition);
				m_entityList[i]->SetTransform( transform);
			}

			for( size_t i=0; i<m_transforms.size(); i++)
			{
				Vector3 newPosition = m_transforms[i]->GetTrans() + trans;
				m_transforms[i]->SetTrans( newPosition);
			}
		}
	}

	// ��Ⱦ
	void CAres3DAxis::SetEditType( EditType type) 
	{
		this->SetVisible( false);
		m_editType = type; 
		this->SetVisible( true);
	}

	// ��������
	void  CAres3DAxis::SetScale( float fScale)
	{
		m_fScale = fScale;
		for ( int i=0; i<3; i++)
		{
			/*m_pAxes[i]->GetTransform()->SetScale( fScale);
			m_pPlaneLine[i]->GetTransform()->SetScale( fScale);
			m_pPlaneLine[3+i]->GetTransform()->SetScale( fScale);
			m_pCone[i]->GetTransform()->SetScale( fScale);
			m_pCycle[i]->GetTransform()->SetScale( fScale);*/
		}

		// ����λ��
		m_pCone[0]->GetTransform()->SetTrans( m_fScale + m_vPosition.x, m_vPosition.y, m_vPosition.z);
		m_pCone[1]->GetTransform()->SetTrans( m_vPosition.x, m_fScale + m_vPosition.y, m_vPosition.z);
		m_pCone[2]->GetTransform()->SetTrans( m_vPosition.x, m_vPosition.y, m_fScale + m_vPosition.z);
	}

	// �Ƿ�����
	bool CAres3DAxis::IsWorking() 
	{ 
		return m_moveType!=EM_MOVE_NULL || m_rotateType!=EM_ROTATE_NULL; 
	}
}