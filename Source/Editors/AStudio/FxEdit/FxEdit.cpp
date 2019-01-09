#include "FxLogic.h"
#include <boost/array.hpp>
#include <Engine/AresRoot.h>
#include <boost/lexical_cast.hpp>
#include "../ModelEdit/MOLogic.h"

namespace Ares
{
	// ���캯��
	FxEdit::FxEdit()
	{
	}

	// ����FxEntity
	void FxEdit::ResetFxEntity()
	{
		if( m_fxEntity)
		{
			EntityEdit_Scene->DelEntity( m_fxEntity->GetName());
			m_fxEntity.reset();
		}
	}

	// �½�Ч��
	void FxEdit::New()
	{
		ResetFxEntity();

		m_fxEntity = MakeSharePtr( new_ FxEntity);
		if( m_fxEntity)
		{
			EntityEdit_Scene->AddEntity( "FxEntity", m_fxEntity);
		}
	}

	// ����
	void FxEdit::FrameMove( float elapsedTime)
	{
		if( m_fxEntity)
			m_fxEntity->FrameMove( elapsedTime);
	}

	// ִ��
	void FxEdit::SubmitToRenderQueue()
	{
		//if( m_fxEntity)
		//{
		//	m_fxEntity->SubmitRenderElements();
		//}
	}

	// ��Ч��
	void FxEdit::OpenAfx( const char* file)
	{
		ResetFxEntity();

		m_afxPath = file;

		FxEntity* fxEntity = NULL;
		Serialization::UnSerializeFromBinaryFile( file, fxEntity);

		m_fxEntity = MakeSharePtr( fxEntity);
		if( m_fxEntity)
			EntityEdit_Scene->AddEntity( "FxEntity", m_fxEntity);
	}

	// ����Ч��
	void FxEdit::SaveAfx(  const char* filePath)
	{
		m_afxPath = filePath;

		Serialization::SerializeToBinaryFile( filePath, m_fxEntity.get());
	}

	// ���Ч������
	void FxEdit::AddObject( FxObjectType type)
	{
		if( !m_fxEntity)
			New();

		// ����������Ӷ���
		switch( type)
		{
		case FOT_3DPatch:
			{
				Fx3DPatch* patch3D = new_ Fx3DPatch;
				patch3D->SetName( GetUniqueName().c_str());
				patch3D->GetRenderable()->SetTexture( "cloth.dds");
				m_fxEntity->AddObject( patch3D);
			}
			break;

		case FOT_ParticleSystem:
			{
				FxModel* model = new_ FxModel( FxModel::FLAG_RED | FxModel::FLAG_GREEN | FxModel::FLAG_BLUE | FxModel::FLAG_ALPHA, FxModel::FLAG_RED | FxModel::FLAG_GREEN | FxModel::FLAG_BLUE | FxModel::FLAG_ALPHA);
				if( model)
				{
					model->SetParam( FxModel::PARAM_RED,   1.f,   1.f);
					model->SetParam( FxModel::PARAM_GREEN, 1.f,   0.f);
					model->SetParam( FxModel::PARAM_BLUE,  0.31f ,0.f);
					model->SetParam( FxModel::PARAM_ALPHA, 1.f, 0.f);

					model->SetLifeTime( 8.f, 8.f);
				}

				FxSphericEmitter* particleEmitter = new FxSphericEmitter( Vector3( 0.f, 0.f, 1.f), 0.1f*PI, 0.1f*PI);
				if( particleEmitter)
				{		
					FxBox3Zone* tZone = new_ FxBox3Zone( Box3( Vector3::Zero, Vector3::XAxis, Vector3::YAxis, Vector3::ZAxis, .05f, .05f, .06f));

					particleEmitter->SetZone( tZone);
					particleEmitter->SetFlow( 4);
					particleEmitter->SetForce( 0.006f, 0.015f);
				}

				FxPlaneZone* groundPlane  = new_ FxPlaneZone;
				FxObstacle* modifier	  = new_ FxObstacle( groundPlane, FxModifier::INTERSECT_ZONE, 0.6f, 1.f);

				// Group
				FxParticleSystem* particleSystem = new_ FxParticleSystem( model, 2100);
				particleSystem->SetName( GetUniqueName().c_str());
				particleSystem->AddEmitter( particleEmitter);
				particleSystem->AddModifier( modifier);
				particleSystem->SetGravity(  Vector3( 0.f, 0.f, 0.f));

				particleSystem->GetRenderable()->SetTexture( "��11_td.dds");

				// ǿ�����ð�Χ��
				Rect3 boundingBox( Vector3( -125.f, -125.f, -125.f), Vector3( 125.f, -125.f, 125.f));
				particleSystem->SetBoundingBox( boundingBox);

				//m_test = model;

				m_fxEntity->AddObject( particleSystem);
			}
			break;
		}	
	}

	// ����Ψһ����
	string FxEdit::GetUniqueName()
	{
		if( m_fxEntity)
		{
			for( int i=0; i<100000; i++)
			{
				string result = string("Unnamed") + boost::lexical_cast<string>(i);
				if( !m_fxEntity->GetObjectByName( result.c_str()))
				{
					return result;
				}
			}
		}

		A_ASSERT( FALSE);

		return "";
	}

	// ����ѡ��
	void FxEdit::SetSelected( int idx)
	{
		if( idx >= m_fxEntity->GetNumObjects())
			return;

		m_selectedIdx = idx;

		// ��ʾTransformAxis
		//Logic_Transform->SetSelected( m_fxEntity->GetObjectByIndex( m_selectedIdx)->GetTransform());
	}

	// ɾ��ѡ��
	void FxEdit::DeleteSelected( int idx)
	{
		if( m_fxEntity)
			m_fxEntity->DeleteObjectByIndex( idx);
	}
}