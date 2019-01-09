#pragma once

#include <EditorKit/FollowViewerCamera.h>
#include <Engine/RenderSystem/AresModel.h>
#include <Engine/RenderSystem/AresVisualShape.h>
#include <Engine/SceneSystem/AresEntity.h>

#define  MAX_COLL	256

namespace Ares
{
	// ��ײ��Ϣ
	struct SCapsuleCollInfo
	{
		Vector3  m_triCollPoint;	// ��ײ��
		Vector3  m_collNormal;		// ��ײ����,�������������Ϣ
		Vector3  m_triNormal;		// �����η���
	};

	//--------------------------------------
	// AresProxy for control(β���ӽ������)
	//					201104-29 ����	
	//--------------------------------------
	struct SJump;
	struct SProxyInfo;
	class CCharacterProxy
	{
	public:
		enum MoveDir
		{
			EM_FORWARD = 0,
			EM_RIGHT_FORWARD,
			EM_RIGHT,
			EM_RIGHT_BACK,
			EM_BACK,
			EM_LEFT_BACK,
			EM_LEFT,
			EM_LEFT_FORWARD,
		};

		enum BlockType
		{
			EM_BLOCK_SURROUND = 0x1,
			EM_BLOCK_UP		  = 0x2,		// �Ϸ����谭
			EM_BLOCK_DOWN	  = 0x4,		// �·����谭
			EM_TOTAL,
		};

		enum LandMoveState
		{
			EM_LAND = 0,			// ��½����
			EM_FALL,				// ���� or �»�
			EM_JUMP,				// ��Ծ
		};
	public:
		// ���캯��
		CCharacterProxy();

		// ����
		void Active();

		// �ر�
		void Decative();

		// FrameMove
		void FrameMove( float fDeltaTime);

		// �ı��˶�״̬
		void SwitchMoveStateBefore();

		// ����״̬����Ҳ��������µ�λ��
		bool ResponseInputAndCalcNextPos(  Vector3& nextPos, float fDeltaTime);

		// ������λ��
		void AdjustNextPos( Vector3 nextPos);

		// ��ǰλ���Ƿ�Ӧ��Fall
		bool IsShouldFall( Vector3 nextPos);

		// �����Ƿ���ʾ����
		void SetCapsuleVisible( bool visible) { m_showCapsule = visible; }

	private:
		// ����nextPos ��״̬�ı�
		void AdjustNextPos_Land( Vector3& nextPos);
		void AdjustNextPos_Jump( Vector3& nextPos);
		void AdjustNextPos_Fall( Vector3& nextPos);

		// λ�����µ���
		void AdjustPosUpDown( Vector3& pos, DWORD flag);

		// λ�����ҵ���(�����³���)
		void AdjustPosSurround( Vector3& pos, DWORD flag = EM_BLOCK_SURROUND, float scale=1.0f);

		// �Ƿ񱻼�ס
		bool IsNip( Vector3& pos);

		// �ƶ���غ���
	public:
		// ��Ӧ����
		void RespondInput( float fDeltaTime);

		// �������Ӧ����
		void CameraRespondInput( float fDeltaTime);

		// ����ģ��Ƶ��
		void SetStepHZ( float hz=60.f);

		// ��ײ���
		int CollCheck( Vector3& newPos);

		// ������ײ��Ϣ
		void TidyCollInfo();

		// ����λ��
		void SetPos( const Vector3& newPos);

		// ���ó���
		void SetDir();

		// ����״̬
		void SetState( LandMoveState state) { m_moveState = state; }

	private:
		// ����,��ʾcapsule()
		void ShowCapsule( Capsule3& capsule);

		// ���½�ɫ����
		void PlayCharacterAnimation();

		// ��ȡ����
		Vector3 GetDir( MoveDir dir);

	public:
		// ��ȡ��ɫλ��
		Vector3 GetCharacterPos();

	private:
		ModelPtr				 m_character;			// ��ɫ

		CFollowViewerCamera*	m_camera;				// �������ǵ������	

		int						 m_collNum;				// ��ײ����
		vector<SCapsuleCollInfo> m_collInfo;			// ��ײ��Ϣ
		char					 m_collFlag[MAX_COLL];	// 0����Χ�谭,    1, ���谭,    2, ���谭
		int						 m_collFlagNum[EM_TOTAL];// 0����Χ�谭���� 1, ���谭���� 2, ���谭����

		SProxyInfo*				 m_info;				// �ƶ���Ϣ

		LandMoveState			 m_moveState;			// �ƶ�״̬
		float					 m_timeOnLand;			// ��½���ϵ�ʱ��

		float					 m_stepDeltaTime;		// ����ʱ��(1.f / hz)

		SJump*					 m_jump;				// ��Ծ����

		// ������ʾ
		VisualSegment3*			 m_lines[MAX_COLL];
		VisualShape*			 m_capsule;
		bool					 m_showCapsule;			// �Ƿ���ʾ����
	};
}