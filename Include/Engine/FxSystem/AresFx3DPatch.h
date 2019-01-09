#pragma once

#include <string>
#include "AresFxObject.h"
#include "AresFxRenderable.h"
#include <Core/AresSerialization.h>
#include <Core/Graphics/AresTexture.h>
#include <Core/Graphics/AresRenderlayout.h>

using namespace std;

namespace Ares
{
	//------------------------------------
	// ��Ƭ 2012-8-25 ����
	//------------------------------------
	class Fx3DPatch : public FxObject
	{
	public:
		Fx3DPatch();
		virtual ~Fx3DPatch();

		// ������ɫ
		void SetColor( const ColorRGB& color);

		// ��ȡ3DƬ��ɫ
		const ColorRGB& GetColor() const { return m_color; }

		// ��ȡת��
		Transform& GetTransform() { return m_transform; }

		// ��ȡRenderable
		FxRenderablePtr& GetRenderable() { return m_renderable; }

		// ����
		virtual void FrameMove( float elpasedTime,  FxEntity* fxEntity);

		// ִ��
		virtual void SubmitRenderElements( RenderElementMgr& renderElementMgr);

		// ���л�
		BOOST_SERIALIZATION_SPLIT_MEMBER()
		template<typename Archive> void save( Archive& ar, const unsigned int version) const
		{
			FxRenderable* renderable = m_renderable.get();

			ar & boost::serialization::base_object<FxObject>(*this);
			ar & m_color;
			ar & renderable;
		}
		template<typename Archive> void load( Archive& ar, const unsigned int version)
		{
			string			texture;
			FxRenderable*	renderable;

			ar & boost::serialization::base_object<FxObject>(*this);
			ar & m_color;
			ar & renderable;

			m_renderable = MakeSharePtr( renderable);

			UpdateBuffer();
		}

	private:
		// ����Buffer
		void UpdateBuffer();

	private:
		ColorRGB			m_color;			// ��ɫ
		FxRenderablePtr		m_renderable;		// 3DPatch����
	};
}