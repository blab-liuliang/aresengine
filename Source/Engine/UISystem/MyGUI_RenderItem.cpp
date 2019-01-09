/*!
	@file
	@author		Albert Semenov
	@date		02/2008
*/
/*
	This file is part of MyGUI.

	MyGUI is free software: you can redistribute it and/or modify
	it under the terms of the GNU Lesser General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	MyGUI is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU Lesser General Public License for more details.

	You should have received a copy of the GNU Lesser General Public License
	along with MyGUI.  If not, see <http://www.gnu.org/licenses/>.
*/
#include "Engine/UISystem/MyGUI_Precompiled.h"
#include "Engine/UISystem/MyGUI_RenderItem.h"
#include "Engine/UISystem/MyGUI_LayerNode.h"
#include "Engine/UISystem/MyGUI_LayerManager.h"
#include "Engine/UISystem/AresUISystem.h"
#include "Engine/UISystem/MyGUI_RenderManager.h"
#include "Engine/UISystem/MyGUI_DataManager.h"
#include "Engine/UISystem/MyGUI_RenderManager.h"
#include "Engine/AresRoot.h"

namespace MyGUI
{

	RenderItem::RenderItem()
		: Renderable()
		, mTexture(nullptr),
		mNeedVertexCount(0),
		mOutOfDate(false),
		mCountVertex(0),
		mCurrentUpdate(true),
		mCurrentVertex(nullptr),
		mLastVertexCount(0),
		mVertexBuffer(nullptr),
		mRenderTarget(nullptr),
		mCompression(false),
		mManualRender(false)
	{
		mVertexBuffer = RenderManager::GetSingleton().createVertexBuffer();

		// 设置材质
        RenderMethodPtr rMethod = AResSystem.LoadMethod("MyGui.hlsl");
		m_material->SetMethod( rMethod);

		// 设置参数
		m_diffuseSamp = MakeShaderParam();
		m_material->SetParamRef( "ScreenWidthHeight", RenderSystem::SPAB_ScreenWidthHeight);
		m_material->SetParamRef( "DiffuseTex", m_diffuseSamp);

		// 设置状态
		RasterizerStateDesc rDesc;
		rDesc.m_cullMode = CM_None;
		RasterizerStatePtr rasterizerState = ARenderDevice->CreateRasterizerState( rDesc);
		m_material->SetRasterizerState( rasterizerState);

		DepthStencilStateDesc dDesc;
		dDesc.m_depthEnable = false;
		DepthStencilStatePtr depthStencilState = ARenderDevice->CreateDepthStencilState( dDesc);
		m_material->SetDepthStencilState( depthStencilState);

		// 混合状态 
		BlendStateDesc bDesc;
		bDesc.m_blendEnable.assign( true);
		bDesc.m_blendOp.assign( BOP_Add);
		bDesc.m_srcBlend.assign( ABF_SrcAlpha);
		bDesc.m_destBlend.assign( ABF_InvSrcAlpha);
		bDesc.m_blendOpAlpha.assign( BOP_Add);
		bDesc.m_srcBlendAlpha.assign( ABF_One);
		bDesc.m_destBlendAlpha.assign( ABF_Zero);
		bDesc.m_colorWriteMask.assign( ColorRGB::MASK_All);
		BlendStatePtr blendState = ARenderDevice->CreateBlendState( bDesc);
		m_material->SetBlendState( blendState, ColorRGB(0.f,0.f,0.f), 0xffffffff);
	}

	RenderItem::~RenderItem()
	{
		RenderManager::GetSingleton().destroyVertexBuffer(mVertexBuffer);
		mVertexBuffer = nullptr;
	}

	void RenderItem::renderToTarget(IRenderTarget* _target, bool _update)
	{
		if (mTexture == nullptr)
			return;

		mRenderTarget = _target;

		mCurrentUpdate = _update;

		if (mOutOfDate || _update)
		{
			mCountVertex = 0;

            GraphicBufferPtr vertexBuffer = mVertexBuffer->GetBuffer();
			GraphicsBuffer::Modifier modifier( vertexBuffer, BA_WriteOnly);
			Vertex* buffer = modifier.GetPointer<Vertex>();
			//vector<Vertex> bufferData; bufferData.reserve( 4096); 
			for( VectorDrawItem::iterator iter = m_drawItems.begin(); iter != m_drawItems.end(); ++iter)
			{
				// перед вызовом запоминаем позицию в буфере
				mCurrentVertex = buffer;
				mLastVertexCount = 0;

				(*iter).first->doRender();

				// колличество отрисованных вершин
				MYGUI_DEBUG_ASSERT(mLastVertexCount <= (*iter).second, "It is too much vertexes");
				buffer += mLastVertexCount;
				mCountVertex += mLastVertexCount;
			}

			mOutOfDate = false;
		}

		// хоть с 0 не выводиться батч, но все равно не будем дергать стейт и операцию
		if ( mCountVertex)
		{
			// непосредственный рендринг
			if (mManualRender)
			{
				for( VectorDrawItem::iterator iter = m_drawItems.begin(); iter != m_drawItems.end(); ++iter)
					(*iter).first->doManualRender(mVertexBuffer, mTexture, mCountVertex);
			}
			else
			{
				m_layout = mVertexBuffer->GetLayout();

				_target->DoRender( *this);
			}
		}
	}

	void RenderItem::removeDrawItem(ISubWidget* _item)
	{
		for (VectorDrawItem::iterator iter = m_drawItems.begin(); iter != m_drawItems.end(); ++iter)
		{
			if ((*iter).first == _item)
			{
				mNeedVertexCount -= (*iter).second;
				m_drawItems.erase(iter);
				mOutOfDate = true;

				mVertexBuffer->setVertexCount(mNeedVertexCount);

				// если все отдетачились, расскажем отцу
				if (m_drawItems.empty())
				{
					mTexture = nullptr;
					mCompression = true;
				}

				return;
			}
		}
		MYGUI_EXCEPT("DrawItem not found");
	}

	void RenderItem::AddDrawItem( ISubWidget* _item, size_t _count)
	{
		// 检测该渲染项是否已存在
#if MYGUI_DEBUG_MODE == 1
		for (VectorDrawItem::iterator iter = m_drawItems.begin(); iter != m_drawItems.end(); ++iter)
		{
			MYGUI_ASSERT((*iter).first != _item, "DrawItem exist");
		}
#endif

		m_drawItems.push_back(DrawItemInfo(_item, _count));
		mNeedVertexCount += _count;
		mOutOfDate = true;

		mVertexBuffer->setVertexCount(mNeedVertexCount);
	}

	void RenderItem::reallockDrawItem(ISubWidget* _item, size_t _count)
	{
		for (VectorDrawItem::iterator iter = m_drawItems.begin(); iter != m_drawItems.end(); ++iter)
		{
			if ((*iter).first == _item)
			{
				// если нужно меньше, то ниче не делаем
				if ((*iter).second < _count)
				{
					mNeedVertexCount -= (*iter).second;
					mNeedVertexCount += _count;
					(*iter).second = _count;
					mOutOfDate = true;

					mVertexBuffer->setVertexCount(mNeedVertexCount);
				}
				return;
			}
		}
		MYGUI_EXCEPT("DrawItem not found");
	}

	// 设置漫反射纹理
	void RenderItem::setTexture(ITexture* _value)
	{
		if (mTexture == _value)
			return;

		MYGUI_DEBUG_ASSERT(mNeedVertexCount == 0, "change texture only empty buffer");

		mTexture = _value;

		// 更新纹理参数到Shader
		*m_diffuseSamp = mTexture->GetTexture();
		//m_diffuseSamp->SetSamplerState( ARenderDevice->CreateSamplerState( SamplerStateDesc()));
	}

	ITexture* RenderItem::getTexture()
	{
		return mTexture;
	}

	bool RenderItem::getCompression()
	{
		bool result = mCompression;
		mCompression = false;
		return result;
	}

	void RenderItem::setManualRender(bool _value)
	{
		mManualRender = _value;
	}

	bool RenderItem::getManualRender() const
	{
		return mManualRender;
	}

	void RenderItem::outOfDate()
	{
		mOutOfDate = true;
	}

	bool RenderItem::isOutOfDate() const
	{
		return mOutOfDate;
	}

	size_t RenderItem::getNeedVertexCount() const
	{
		return mNeedVertexCount;
	}

	size_t RenderItem::getVertexCount() const
	{
		return mCountVertex;
	}

	bool RenderItem::getCurrentUpdate() const
	{
		return mCurrentUpdate;
	}

	Vertex* RenderItem::getCurrentVertexBuffer() const
	{
		return mCurrentVertex;
	}

	void RenderItem::setLastVertexCount(size_t _count)
	{
		mLastVertexCount = _count;
	}

	IRenderTarget* RenderItem::getRenderTarget()
	{
		return mRenderTarget;
	}

} // namespace MyGUI