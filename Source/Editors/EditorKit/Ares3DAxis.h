#pragma once

#include <vector>
#include <Engine/RenderSystem/AresVisualShape.h>
#include <Engine/SceneSystem/AresEntity.h>
#include <boost/array.hpp>

using namespace std;

namespace Ares
{
	//----------------------------------------
	// 3D������ϵ 2010-07-11 ����
	//----------------------------------------
	class  CAres3DAxis
	{
	public:
		enum EditType
		{
			EM_EDIT_TRANSLATE,		// �ƶ�
			EM_EDIT_ROTATE,			// ��ת
			EM_EDIT_SCALE,			// ����
		};

		// �ƶ�����
		enum EMoveType
		{
			EM_MOVE_NULL = -1,  // Ĭ������,���ƶ�
			EM_MOVE_X,			// ��X�������ƶ�
			EM_MOVE_Y,			// ��Y�������ƶ�
			EM_MOVE_Z,			// ��Z�������ƶ�
			EM_MOVE_XYPLANE,	// ��xyƽ�����ƶ�
			EM_MOVE_YZPLANE,	// ��YZƽ�����ƶ�
			EM_MOVE_XZPLANE,	// ��XZƽ�����ƶ�
 		};

		// ��ת����
		enum ERotateType
		{
			EM_ROTATE_NULL,
			EM_ROTATE_X,	// ��X����ת
			EM_ROTATE_Y,	// ��Y����ת
			EM_ROTATE_Z,	// ��Z����ת
		};

		// ���캯��
		CAres3DAxis( VisualShapeMgr& visualShapeMgr);

		// �����ӵ�
		void CatchEntity( Entity* enity);

		// ����VisualShape
		void CatchTransform( Transform* vs);

		// ������ŵĳ������
		void Clear() { m_entityList.clear(); m_transforms.clear(); }

		// ����ƶ�
		void OnMouseMove( const Vector3& rayOrig0, const Vector3& rayDir0, const Vector3& rayOrig1, const Vector3& rayDir1, POINT* ptPre=NULL, POINT* ptCurr=NULL);

		// ��ѡȡ
		bool OnMouseDown( const Vector3& rayOrig, const Vector3& rayDir);

		// ȡ��ѡ��
		void OnMouseUp();

		// ����λ��
		void SetPosition( float _posX, float _posY, float _posZ);

		// ����λ��
		void SetPosition( const Vector3& pos);

		// �����Ƿ�ɼ�
		void SetVisible( bool visible);

		// ��Ⱦ
		void SetEditType( EditType type);

		// �ƶ�
		void  Translate( const Vector3& trans);

		// ��������
		void  SetScale( float fScale);

		// �Ƿ�����
		bool IsWorking();

	private:
		// ��ʼ����Ⱦ״̬
		void InitRenderState();

		// ������ײ������λ��
		void UpdateTranslateCollBox();

	private:
		VisualSegment3*	m_pAxes[3];			// x, y, z ����
		VisualSegment3* m_pPlaneLine[6];	// ��ʾ���6����
		VisualCone3*	m_pCone[3];			// Բ׶��
		Vector3			m_vPosition;		// 3D��λ��
		Vector3			m_vAxisDir[3];		// ������ĳ���	
		VisualCycle3*   m_pCycle[3];
		VisualShape*    m_pScale;			// ����
		EditType        m_editType;			// �༭����
		EMoveType       m_moveType;			// �ƶ�����
		ERotateType     m_rotateType;		// ��ת����
		bool            m_bVisible;			// �Ƿ�ɼ�
		float           m_fScale;
		boost::array<Box3,6> m_moveBoxs;			// �ƶ�ʱ����
		vector<Entity*> m_entityList;		// ʵ���б�
		vector<Transform*>m_transforms;		// VisualShape�б�
	};
}