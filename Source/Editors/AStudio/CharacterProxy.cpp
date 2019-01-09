#include "CharacterProxy.h"
#include <Physics/Shapes.h>
#include <Engine/RenderSystem/AresRenderSystem.h>
#include <Engine/RenderSystem/AresAnimationController.h>
#include <Engine/AresRoot.h>
#include "SCLogic.h"
#include <vector>

using namespace std;

// �����������ת���� ������ת���� �뾶������������
#define CAMERA_ROTATIONY_SCALAR  0.1f
#define CAMERA_ROTATIONZ_SCALAR  0.3f
#define CAMERA_RADIUS_SCALAR     0.02f


#define  GRAVITY_G	-6.f

namespace Ares
{
	//----------------------------------------
	// ��Ծ  2011-05-06   ��
	//----------------------------------------
	struct SJump
	{
		Vector3 m_startPos;			// ����λ��
		Vector3	m_forward;			// ��Ծ����
		float		m_totalTime;		// ����ʱ��
		float		m_startMoveTime;	// ��ʼ�ƶ�ʱ��
		float		m_endMoveTime;		// �����ƶ�ʱ��
		float		m_jumpVelocity;		// �����ٶ�

		// ����
		void Jump( const Vector3& startPos, const Vector3& forward)
		{
			m_startPos = startPos;
			m_forward  = forward;
			m_totalTime= 0.f;
			m_startMoveTime = 0.f;
			m_endMoveTime= 0.f;
			m_jumpVelocity = 3.f;
		}

		// ������Ծ����
		void SetJumpDir( Vector3& dir)
		{
			if( m_forward == Vector3( 0.f, 0.f, 0.f))
			{
				m_forward = dir;
				m_startMoveTime = m_totalTime;
			}
		}

		// ����ƶ�����
		void ClearMoveDir()
		{
			if( !m_endMoveTime)
				m_endMoveTime  = m_totalTime;
		}

		// ÿ֡����
		Vector3 FrameMove( float fDeltaTime)
		{
			m_totalTime += fDeltaTime;

			// ˮƽ����
			Vector3 nowPos;

			if( m_endMoveTime)
				nowPos = m_startPos + m_forward * ( m_endMoveTime - m_startMoveTime);
			else
				nowPos = m_startPos + m_forward * ( m_totalTime - m_startMoveTime);

			// ���·���
			nowPos.z = m_startPos.z + 0.5f * GRAVITY_G * m_totalTime * m_totalTime + m_jumpVelocity * m_totalTime;

			return nowPos;
		}
	};

	//--------------------------------------
	// ��ɫ�ƶ����Խṹ�� 2011-05-10 
	//--------------------------------------
	struct SProxyInfo
	{
		Vector3			m_pos;					// λ��
		Vector3			m_up;					// �Ϸ���
		Vector3			m_headerPos;			// ͷ��λ��
		Vector3			m_moveDir;				// �ƶ�����
		float			m_radius;				// �뾶
		float			m_height;				// ����߶�
		float			m_velocity;				// �ƶ��ٶ�
		//float			m_downGlideVelocity;	// �»��ٶ�
		float			m_upDownAngle;			// �˽Ƕ�λ������
		float			m_timeLand;				// �ڵ��϶�ÿ����ٴ�����

		float			m_horizonAngle;			// ˮƽ��ת�Ƕ�(˳ʱ��)
		float			m_verticleAngle;		// ��ֱ��ת�Ƕ�(˳ʱ��)

		//float			m_tolerance;			// ��Χ

		// ���캯��
		SProxyInfo()
		{
			m_pos       = Vector3( 0.f, 0.f, 0.f);
			m_moveDir	= Vector3( 0.f, 0.f, 0.f);
			m_height    = 0.95f;
			m_up		= Vector3( 0.f, 0.f, 1.f);
			m_headerPos = m_pos + m_height * m_up;
			m_upDownAngle = PI / 4.f;

			m_radius = 0.2f;
			m_timeLand = 0.3f;
			//m_tolerance = 1e-6f;

			m_horizonAngle = 0.f;
			m_verticleAngle= 0.f;

			m_velocity	= 3.f;
		}

		// ������������capsue
		void  GenerateCapsule(  Vector3& pos, Capsule3& pOut)
		{
			Segment3 segment( pos + Vector3( 0, 0, m_radius), pos + Vector3( 0, 0, m_height - m_radius));

			pOut.Set( segment, m_radius);
		}
	};

	// ���캯��
	CCharacterProxy::CCharacterProxy()
	{
		m_showCapsule = false;

		for ( int i=0; i<MAX_COLL; i++)
		{
			m_lines[i] = SELogic_VisualShape.CreateSegment();
			m_lines[i]->SetColor(0xFFFFF00F);
			m_lines[i]->SetVisible( false);
		}

		m_info = new_ SProxyInfo;
		m_jump = new_ SJump;

		m_capsule   = SELogic_VisualShape.CreateVisualShape();
		m_character = AResSystem.LoadModel( "d_zhuyan.model");
		Scene* pScene = SCLogic_Scene;
		if( pScene)
		{
			pScene->AddEntity( "Character", m_character, false);
		}

		// ������
		Capsule3 capsule( Segment3( Vector3( 5.5f, 5.6f, 0.1f), Vector3( 5.5f, 5.6f, 1.f)), 0.3f);

		m_moveState = EM_FALL;
		m_timeOnLand   = 0.f;

		m_camera = new_ CFollowViewerCamera;
		m_camera->SetBindPos( &m_info->m_headerPos);

		SetStepHZ( 60.f);

		// ��ʾ������
		ShowCapsule( capsule);
	}

	// FrameMove
	void CCharacterProxy::FrameMove( float fDeltaTime)
	{
		// ��ʱ��ֹ���Ժ�,ʱ����̫��
		if( fDeltaTime > 0.2f)
			return;

		m_timeOnLand += fDeltaTime;

		// ����״̬
		SwitchMoveStateBefore();

		Vector3 nextPos;
		if( ResponseInputAndCalcNextPos( nextPos, fDeltaTime))
		{
			AdjustNextPos( nextPos);
		}

		m_camera->FrameMove( fDeltaTime);

		static vector<LandMoveState> stateListener;

		if( stateListener.size() == 0 || (m_moveState != stateListener.back() ||m_moveState==EM_FALL))
			stateListener.push_back( m_moveState);
	}

	// �ı��˶�״̬
	void CCharacterProxy::SwitchMoveStateBefore()
	{
		if( m_moveState == EM_LAND)
		{
			// land to jump
			if( SCLogic_Input->IsKeyDown( OIS::KC_SPACE) && m_timeOnLand > m_info->m_timeLand)
			{
				m_jump->Jump( m_info->m_pos, m_info->m_moveDir * m_info->m_velocity);

				m_moveState = EM_JUMP;	
			}
		}
	}

	// ��Ӧ����
	void CCharacterProxy::RespondInput( float fDeltaTime)
	{
		static float backVelocity = 0.8f;

		if( IsKeyDown( OIS::KC_W) && IsKeyDown( OIS::KC_A))
			m_info->m_moveDir = GetDir( EM_LEFT_FORWARD);

		else if(IsKeyDown( OIS::KC_A) && IsKeyDown( OIS::KC_S))
			m_info->m_moveDir = GetDir( EM_LEFT_BACK) * backVelocity;

		else if(IsKeyDown( OIS::KC_W) && IsKeyDown( OIS::KC_D))
			m_info->m_moveDir = GetDir( EM_RIGHT_FORWARD);

		else if(IsKeyDown( OIS::KC_S) && IsKeyDown( OIS::KC_D))
			m_info->m_moveDir = GetDir( EM_RIGHT_BACK) * backVelocity;

		else if(IsKeyDown(OIS::KC_W))
			m_info->m_moveDir = GetDir( EM_FORWARD);

		else if(IsKeyDown(OIS::KC_S)) 
			m_info->m_moveDir = GetDir( EM_BACK) * backVelocity;

		else if(IsKeyDown(OIS::KC_A)) 
			m_info->m_moveDir = GetDir( EM_LEFT);

		else if(IsKeyDown(OIS::KC_D)) 
			m_info->m_moveDir = GetDir( EM_RIGHT);
		else
			m_info->m_moveDir = Vector3( 0, 0, 0);

		//if( m_characterNode)
			SetDir();
	}

	// ����״̬�����µ�λ��
	bool CCharacterProxy::ResponseInputAndCalcNextPos( Vector3& nextPos, float fDeltaTime)
	{
		// �������Ӧ����
		CameraRespondInput( fDeltaTime);

		// ����nextPos
		nextPos = m_info->m_pos;

		RespondInput( fDeltaTime);

		PlayCharacterAnimation();

		switch( m_moveState)
		{
		case EM_LAND:
			{
				nextPos = m_info->m_pos + m_info->m_moveDir * m_info->m_velocity * fDeltaTime;
			}
			break;

		case EM_JUMP:
			{
				nextPos = m_jump->FrameMove( fDeltaTime);
				m_jump->SetJumpDir( m_info->m_moveDir * m_info->m_velocity);
			}
			break;

		case EM_FALL:
			{
				//nextPos.z -= 5.f * fDeltaTime;
				nextPos.z -= m_info->m_radius - (m_info->m_radius * cos(m_info->m_upDownAngle)) - 0.001f;
			}
			break;
		}

		return nextPos != m_info->m_pos;
	}

	// ���½�ɫ����
	void CCharacterProxy::PlayCharacterAnimation()
	{/*
		if( !m_character->GetAnimationController()->GetAnimation())
			return;

		if( !m_character->GetAnimationController()->GetAnimation()->IsResourceEnabled())
			return;

		// ��ʱ

		IAnimationController::SAnimationDesc* animationDesc = NULL;
		static size_t tIndex = 0;
		static bool tInit = false;
		if( !tInit)
		{
			// 1.�ƶ��ද���ڵ�0��
			if( animationDesc = m_character->GetAnimationController()->GetAnimationDesc( "��"))
				animationDesc->m_loop = true;

			if( animationDesc = m_character->GetAnimationController()->GetAnimationDesc( "����"))
				animationDesc->m_loop = true;

			//if( animationDesc = m_character->GetAnimationController()->GetAnimationDesc( "����"))
			//	animationDesc->m_loop = true;

			if( animationDesc = m_character->GetAnimationController()->GetAnimationDesc( "ս��"))
				animationDesc->m_loop = true;

			// 2.ս���ද���ڵ�1��
			if( animationDesc = m_character->GetAnimationController()->GetAnimationDesc( "��������"))
				animationDesc->m_layer = 1;

			if( animationDesc = m_character->GetAnimationController()->GetAnimationDesc( "˲��"))
				animationDesc->m_layer = 1;

			if( animationDesc = m_character->GetAnimationController()->GetAnimationDesc( "��"))
				animationDesc->m_layer = 1;

			if( animationDesc = m_character->GetAnimationController()->GetAnimationDesc( "����3"))
				animationDesc->m_layer = 2;

			// 3.�������ڵ�2��

			tInit = true;
		}

		switch( m_moveState)
		{
		case EM_LAND:
			{
				if( g_pInput->IsKeyDown( DIK_W))
				{
					if( tIndex !=0)
						m_character->GetAnimationController()->CrossFade( "��");
					
					tIndex = 0;
				}
				else if( g_pInput->IsKeyDown( DIK_S))
				{
					if( tIndex !=1)
						m_character->GetAnimationController()->CrossFade( "����");

					tIndex = 1;
				}
				else if(g_pInput->IsKeyDown( DIK_A) || g_pInput->IsKeyDown( DIK_D))
				{
					if( tIndex !=0)
						m_character->GetAnimationController()->CrossFade( "��");

					tIndex = 0;
				}
				else if( tIndex != 2)
				{
					if( tIndex !=2)
					{
						//m_character->GetAnimationController()->CrossFade( "����");
						m_character->GetAnimationController()->CrossFade( "ս��");
					}

					tIndex = 2;
				}
				
				if( g_pInput->IsKeyDown( DIK_1))
				{
					m_character->GetAnimationController()->CrossFade( "��", 0.15f, IAnimationController::STOP_SAMELAYER_DA);
					tIndex = 3;
				}
				if( g_pInput->IsKeyDown( DIK_2))
				{
					m_character->GetAnimationController()->CrossFade( "˲��", 0.1f, IAnimationController::STOP_SAMELAYER_DA);
					tIndex = 3;
				}
				else if( g_pInput->IsKeyDown( DIK_3))
				{
					m_character->GetAnimationController()->CrossFade( "����3", 0.3f, IAnimationController::STOP_SAMELAYER_DA);
					tIndex = 3;
				}
			}
			break;

		case EM_JUMP:
			{
				if( tIndex != 3)
				{
					//m_character->GetAnimationController()->CrossFade( 3);

					tIndex = 3;
				}
			}
			break;

		case EM_FALL:
			{
				
			}
			break;
		}*/
	}

	// ������λ��
	void CCharacterProxy::AdjustNextPos( Vector3 nextPos)
	{
		// ���м��
		CollCheck( nextPos);

		switch( m_moveState)
		{
		case EM_LAND:
			{
				AdjustNextPos_Land( nextPos);
			}
			break;

		case EM_JUMP:
			{
				AdjustNextPos_Jump( nextPos);
			}
			break;

		case EM_FALL:
			{
				AdjustNextPos_Fall( nextPos);
			}
			break;
		}
	}

	// ��ǰλ���Ƿ�Ӧ��Fall
	bool CCharacterProxy::IsShouldFall(Vector3 nextPos)
	{
		if( !m_collNum)
			return true;

		if( m_collNum == m_collFlagNum[EM_BLOCK_SURROUND] && !IsNip(nextPos))
			return true;

		return false;
	}

	// ��ǰ״̬½��
	void CCharacterProxy::AdjustNextPos_Land( Vector3& nextPos)
	{
		// ����ײ
		if( m_collNum)
		{
			// �Ƿ�Ӧ�ñ�Ϊ����״̬
			if( IsShouldFall(nextPos))
			{
				// ���� + ��̽
				Vector3 nnPos = nextPos;
				AdjustPosSurround( nnPos, EM_BLOCK_SURROUND | EM_BLOCK_DOWN, 1.0f);
				nnPos.z -= m_info->m_radius;

				// ���¸�״̬�Ƿ���Ȼ��Fall
				CollCheck( nnPos);
				if( IsShouldFall(nnPos))
				{
					m_moveState = EM_FALL;

					return;
				}
			}

			CollCheck( nextPos);

			// ��½(��֧�ŵ�), ���¸߶�
			AdjustPosSurround(  nextPos, EM_BLOCK_SURROUND);

			if( IsNip(nextPos))
				AdjustPosUpDown( nextPos, EM_BLOCK_DOWN  | EM_BLOCK_SURROUND);
			else
				AdjustPosUpDown( nextPos, EM_BLOCK_DOWN);

			SetPos( nextPos);
		}
		else
		{
			// ��̽
			Vector3 tNextPos = nextPos;
			tNextPos.z -= m_info->m_radius - (m_info->m_radius * cos(m_info->m_upDownAngle)) - 0.001f;

			CollCheck( tNextPos);
			if( m_collNum)
			{
				// ��֧�ŵ�,�����EM_BLOCK_SURROUND, ��ֹ����
				AdjustPosUpDown( tNextPos, EM_BLOCK_DOWN  | EM_BLOCK_SURROUND);

				SetPos( tNextPos); 
			}
			else
			{
				SetPos( nextPos);
				m_moveState = EM_FALL;
			}
		}
	}

	// ��Ծ
	void CCharacterProxy::AdjustNextPos_Jump( Vector3& nextPos)
	{
		// ����ײ
		if( m_collNum)
		{
			if( IsShouldFall( nextPos))
			{
				m_jump->ClearMoveDir();

				// ״̬����, ����
				AdjustPosSurround( nextPos);
				SetPos( nextPos);

				//m_moveState = EM_FALL;
			}
			else
			{
				// ��½, ���¸߶�
				AdjustPosSurround( nextPos, EM_BLOCK_SURROUND);
				AdjustPosUpDown( nextPos, EM_BLOCK_DOWN);

				SetPos( nextPos);

				m_moveState  = EM_LAND;
				m_timeOnLand = 0.f;
			}
		}
		else
		{
			// ����ײ( ֱ�Ӹ���λ��)
			SetPos( nextPos);
		}
	}

	// ����
	void CCharacterProxy::AdjustNextPos_Fall( Vector3& nextPos)
	{
		// ����ײ
		if( m_collNum)
		{
			if( IsShouldFall( nextPos))
			{
				// ״̬����, ����
				AdjustPosSurround( nextPos);
				SetPos( nextPos);
			}
			else
			{
				// ״̬����, ����
				AdjustPosSurround( nextPos);
				AdjustPosUpDown( nextPos, EM_BLOCK_DOWN);

				SetPos( nextPos);

				m_moveState  = EM_LAND;
				m_timeOnLand = 0.f;
			}
		}
		else
		{
			// ����ײ( ֱ�Ӹ���λ��)
			SetPos( nextPos);
		}
	}

	// λ�����µ���
	void CCharacterProxy::AdjustPosUpDown( Vector3& pos, DWORD flag)
	{
		float upgradeHeight = 0.f;
		for ( int i=0; i<m_collNum; i++)
		{
			if( m_collFlag[i] & flag)
			{
				// ����
				upgradeHeight = max( upgradeHeight, m_collInfo[i].m_collNormal.z);
			}
		}

		pos.z += upgradeHeight;
	}

	// λ�����ҵ���(�����³���)
	void CCharacterProxy::AdjustPosSurround(  Vector3& pos, DWORD flag/* = EM_BLOCK_SURROUND*/, float scale/*=1.0f*/)
	{
		float fForward = 0.f;
		float fBack	   = 0.f;	
		float fRight   = 0.f;
		float fLeft	   = 0.f;

		Vector3 vForward = GetDir( EM_FORWARD);
		Vector3 vRight	 = GetDir( EM_RIGHT);

		for ( int i=0; i<m_collNum; i++)
		{
			if( m_collFlag[i] & flag)
			{
				float fbDot = Vector3Dot( m_collInfo[i].m_collNormal, vForward);
				float rlDot = Vector3Dot( m_collInfo[i].m_collNormal, vRight);

				fForward = max( fForward, fbDot);
				fBack    = min( fBack,    fbDot);

				fRight   = max( fRight,   rlDot);
				fLeft    = min( fLeft,    rlDot);
			}	
		}

		// ������
		Vector3 sideVec3 = vForward * (fForward + fBack) + vRight * ( fRight   + fLeft);

		pos += sideVec3 * scale;
	}

	// �Ƿ񱻼�ס
	bool CCharacterProxy::IsNip( Vector3& pos)
	{
		if( !m_collFlagNum[EM_BLOCK_SURROUND])
			return false; 

		float x0 = -1e30f;
		float x1 =  1e30f;

		for ( int i=0; i<m_collNum; i++)
		{
			if( m_collFlag[i] == EM_BLOCK_SURROUND)
			{
				Vector3 normal( m_collInfo[i].m_collNormal.x,  m_collInfo[i].m_collNormal.y, 0.f);
				normal.Normalize();

				x0 = max( x0, normal.x);
				x1 = min( x1, normal.x);
			}	
		}

		float angle = acos( x0) - acos( x1);

		if( abs( angle) > PI * 0.75f)
		{
			return true;
		}

		Vector3 interPos;
		float		dist = 0.f;
		//g_pScene->PickTerrain( pos+D3DXVECTOR3(0.f, 0.f, m_info->m_height), D3DXVECTOR3( 0.f, 0.f, -1.f), 0.f, 1000.f, interPos, &dist);

		if( dist <= (/*m_radius*0.25f+*/m_info->m_height))
			return true;

		return false;
	}

	// ����ģ��Ƶ��
	void CCharacterProxy::SetStepHZ( float hz/*=60.f*/)
	{
		if( hz < 0.1f)
			return;

		m_stepDeltaTime = 1.f / hz;
	}

	// ��ȡ����
	Vector3 CCharacterProxy::GetDir( MoveDir dir)
	{
		float angle = m_info->m_horizonAngle + dir * PI / 4.f;

		return Vector3( cos( angle), sin( angle), 0.f);
	}

	// ������ײ��Ϣ
	void CCharacterProxy::TidyCollInfo()
	{
		// ��ʼ��
		m_collFlagNum[EM_BLOCK_DOWN]	 = 0;
		m_collFlagNum[EM_BLOCK_UP]		 = 0;
		m_collFlagNum[EM_BLOCK_SURROUND] = 0;

		// ������ײ��Ϣ
		for ( int i=0; i<m_collNum; i++)
		{
			// �����Ϸ���ĽǶ�
			float angle = acos( Vector3Dot( m_collInfo[i].m_collNormal, m_info->m_up));

			if( angle >= 0 && angle < m_info->m_upDownAngle)
			{
				// down block
				m_collFlag[i] = EM_BLOCK_DOWN;
				m_collFlagNum[EM_BLOCK_DOWN]++;
			}
			else if( angle <= PI && angle > PI - m_info->m_upDownAngle)
			{
				// up block
				m_collFlag[i] = EM_BLOCK_UP;
				m_collFlagNum[EM_BLOCK_UP]++;
			}
			else
			{
				// surround block
				m_collFlag[i] = EM_BLOCK_SURROUND;
				m_collFlagNum[EM_BLOCK_SURROUND]++;
			}
		}
	}

	// ����λ��
	void CCharacterProxy::SetPos( const Vector3& newPos)
	{	
		m_info->m_pos = newPos;
		static Vector3 virtualPos = newPos;
		Vector3 xPos = m_info->m_pos - virtualPos;
		float length = xPos.Length();
		//if( length <= 0.1f)
		//	return;

		if( IsKeyDown(OIS::KC_R))
		{
			m_info->m_pos = virtualPos = Vector3( 0.f, 0.f, 0.f);
		}

		virtualPos += ( m_info->m_pos - virtualPos) *(( length - 0.1f)/length);
		m_info->m_headerPos = virtualPos + m_info->m_height * m_info->m_up;

		Transform transform = m_character->GetTransform();
		transform.SetTrans( virtualPos);
		m_character->SetTransform( transform);

		//if( D3DXVec3LengthSq( &m_info->m_moveDir) > 1e-6f)
		//	m_characterNode->SetRotation( D3DXVECTOR3( 0, 1, 0), m_info->m_moveDir);
		if( m_showCapsule)
		{/*
			Capsule3 capsule;
			m_info->GenerateCapsule( virtualPos, capsule);

			ShowCapsule( capsule);

			// ������ʾ
			for ( int i=0; i<m_collNum; i++)
			{
				if( m_collFlag[i] == EM_BLOCK_DOWN)
				{
					m_lines[i]->SetColor( 0x00FF);

				}
				else if( m_collFlag[i] == EM_BLOCK_SURROUND)
				{
					m_lines[i]->SetColor( 0x00FF00);
				}

				m_lines[i]->SetVisible( true);
				m_lines[i]->SetParam( m_collInfo[i].m_triCollPoint, m_collInfo[i].m_triCollPoint + m_collInfo[i].m_collNormal);
			}

			for( int i=m_collNum; i<MAX_COLL; i++)
			{
				m_lines[i]->SetVisible( false);
			}*/
		}
		else
		{
			m_capsule->SetVisible( false);
		}
	}

	// ��ײ���
	int CCharacterProxy::CollCheck( Vector3& newPos)
	{
		Capsule3 capsule;
		m_info->GenerateCapsule( newPos, capsule);

		//m_collNum = SCLogic_Map->GetScene()->GetCollMap().CheckCapsuleColl( capsule, m_collInfo);

		if( m_collNum)
		{
			// ����
			TidyCollInfo();
		}

		return m_collNum;
	}

	// ����,��ʾcapsule()
	void CCharacterProxy::ShowCapsule( Capsule3& capsule)
	{/*
		Vector3 vertexData[142];

		// ��Բ��
		for ( int i=0; i<20; i++)
		{
			float radius = i * 0.1 * D3DX_PI;

			Vector3 circleDir = Vector3( cos( radius), sin(radius), 0.f) * capsule.m_radius;

			vertexData[i]    = circleDir + capsule.m_segment.m_orig;
			vertexData[i+20] = circleDir + capsule.m_segment.GetNegEnd();
			vertexData[i+40] = circleDir + capsule.m_segment.GetPosEnd();

			vertexData[i+60] = circleDir * 0.5  + capsule.m_segment.m_orig + capsule.m_segment.m_dir * ( capsule.m_segment.m_extent + capsule.m_radius * 0.86); 
			vertexData[i+80] = circleDir * 0.5  + capsule.m_segment.m_orig - capsule.m_segment.m_dir * ( capsule.m_segment.m_extent + capsule.m_radius * 0.86); 
			vertexData[i+100]= circleDir * 0.86 + capsule.m_segment.m_orig + capsule.m_segment.m_dir * ( capsule.m_segment.m_extent + capsule.m_radius * 0.5); 
			vertexData[i+120]= circleDir * 0.86 + capsule.m_segment.m_orig - capsule.m_segment.m_dir * ( capsule.m_segment.m_extent + capsule.m_radius * 0.5); 
		}

		vertexData[140] = capsule.m_segment.GetNegEnd();
		vertexData[141] = capsule.m_segment.GetPosEnd();

		// ׼����������
		WORD indexData[282];

		for ( int i=0, j=19; i<20; j=i++)
		{
			indexData[i*2]   = i;
			indexData[i*2+1] = j;

			indexData[i*2+40]   = i+20;
			indexData[i*2+40+1] = j+20;

			indexData[i*2+80]   = i+40;
			indexData[i*2+80+1] = j+40;

			indexData[i*2+120] = i+60; 
			indexData[i*2+121] = j+60; 

			indexData[i*2+160] = i+80; 
			indexData[i*2+161] = j+80; 

			indexData[i*2+200] = i+100; 
			indexData[i*2+201] = j+100;

			indexData[i*2+240] = i+120; 
			indexData[i*2+241] = j+120; 
		}

		indexData[280] = 140;
		indexData[281] = 141;

		m_capsule->SetVisible( true);
		m_capsule->SetParam( 142, vertexData, D3DPT_LINELIST, 282, indexData);
		*/
	}

	// ���ó���
	void CCharacterProxy::SetDir()
	{
		if( m_info->m_moveDir == Vector3(0, 0, 0))
		{
			Transform transform = m_character->GetTransform();
			transform.SetRotation( Vector3( 0.f, 1.f, 0.f), GetDir(EM_FORWARD));
			m_character->SetTransform( transform);

			return;
		}

		Vector3 tDir = m_info->m_moveDir;

		if( IsKeyDown( OIS::KC_A) && IsKeyDown( OIS::KC_S))
			tDir = -tDir;

		else if( IsKeyDown( OIS::KC_S) && IsKeyDown( OIS::KC_D))
			tDir = -tDir;

		else if( IsKeyDown(OIS::KC_S)) 
			tDir = -tDir;

		Transform transform = m_character->GetTransform();
		transform.SetRotation( Vector3( 0.f, 1.f, 0.f), tDir);
		m_character->SetTransform( transform);
	}

	// �������Ӧ����
	void CCharacterProxy::CameraRespondInput( float fDeltaTime)
	{
		if( IsMRBDown() || IsMLBDown())		// ����ƶ����Ҽ�����
		{
			m_camera->UpdateCameraDir( SCLogic_Input->GetMouseState().Y.rel * CAMERA_RADIUS_SCALAR, SCLogic_Input->GetMouseState().X.rel * CAMERA_ROTATIONZ_SCALAR * CAMERA_ROTATIONY_SCALAR);
		}

		// ������뾶 "��Զ" "����"
		static long oldlz = 0;
		long          tLZ = SCLogic_Input->GetMouseState().Z.rel;
		if( long tZ = tLZ - oldlz)
		{
		//	m_camera->ChangeDefaultRadius( tZ * -0.004f);

			oldlz = tLZ;
		}

		// ƥ�� "���ﳯ��" �� "���������"
		if( IsMRBDown())
		{
			// ����Ҽ�����,���ﳯ�������������ƥ��
			m_info->m_horizonAngle = m_camera->GetHorizonAngle();
		}
		else if( IsMLBDown())
		{

		}
		else
		{
			// ���Ҽ���δ����, �����������������һ��,������λ���������ͬ��
			float cameraAngle = m_camera->GetHorizonAngle();

			if( cameraAngle != m_info->m_horizonAngle)
			{
				m_info->m_horizonAngle += ( cameraAngle - m_info->m_horizonAngle) * fDeltaTime;

				if( abs( cameraAngle - m_info->m_horizonAngle) < 0.01f)
					m_info->m_horizonAngle = cameraAngle;
			}
		}

		// ������谭
		if( m_camera)
		{
			static float currRadius = m_camera->GetCurRadius();
			float defaultRadius = m_camera->GetDefaultRadius();
			currRadius += ( defaultRadius - currRadius) * fDeltaTime * 0.005f;

			if( abs( currRadius - defaultRadius) < 1e-4f)
			{
				currRadius = defaultRadius;
			}

			Vector3 dir = -m_camera->GetDirection();
			dir.Normalize();

			//D3DXVECTOR3 tt = /*m_camera->GetLookAt() + */dir * currRadius;
			//float length = D3DXVec3Length( &tt)/* - m_camera->GetNear()*/;

			float length = currRadius;

			Vector3 tt = m_camera->GetLookAt()- m_camera->GetPosition();
			float lll  = tt.Length() - m_camera->GetNear();

			Vector3 v0 = m_camera->GetFrustem().GetVertexs()[0] - dir * lll;
			Vector3 v1 = m_camera->GetFrustem().GetVertexs()[1] - dir * lll;
			Vector3 v2 = m_camera->GetFrustem().GetVertexs()[2] - dir * lll;
			Vector3 v3 = m_camera->GetFrustem().GetVertexs()[3] - dir * lll;
			
			int collNum = 0;//SCLogic_Map->GetScene()->GetCollMap().CheckOBBColl( v0, v1, v2, v3, dir, length);

			if( collNum)
			{
				m_camera->SetCurRadius( length);
			}
			else
			{
				m_camera->SetCurRadius( currRadius);
			}
		}
	}

	// ��ȡ��ɫλ��
	Vector3 CCharacterProxy::GetCharacterPos()
	{
		if( m_character)
			return m_character->GetTransform().GetTrans();

		return Vector3( -1024.f, -1024.f, -1024.f);
	}

	// ����
	void CCharacterProxy::Active()
	{
		SCLogic_Camera->SetCamera( m_camera);

		SetState( CCharacterProxy::EM_FALL);
	}

	// �ر�
	void CCharacterProxy::Decative()
	{
		Scene* pScene = SCLogic_Scene;
		if( pScene)
			pScene->DelEntity( "Character");
	}
}