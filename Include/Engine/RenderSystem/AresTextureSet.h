#pragma once

#include <Core/AresMath.h>
#include <Core/AresTRect.hpp>
#include <Core/Graphics/AresTexture.h>
#include "Engine/Foundation/Ares3DEngine_h.h"

namespace Ares
{
	//------------------------------------------------------
	// �����-��С������ɵĴ����� 2012-7-20 ����
	// װ���㷨:
	// http://www.blackpawn.com/texts/lightmaps/default.html
	//-------------------------------------------------------
	class ARES_EXPORT TextureSet
	{
		typedef TRect<int> IRect;
	public:
		// �ӵ�
		struct Node
		{
			int			m_id;				// ID>=0��ʶ�ý����ʹ��
			int			m_child[2];			// ��¼�ӽ��ID
			IRect		m_rc;

			// ���캯��
			Node();

			// �Ƿ�ΪҶ���
			bool IsLeaf() const;
		};

	public:
		// ���캯��
		TextureSet();

		// ���캯��,��������
		TextureSet( TexturePtr& texture);

		// �������� INVALID ��Ч����
		int Insert( TexturePtr& subTex);

		// ��д����
		int OverWrite( int nodeIdx, TexturePtr& subTex);

		// ��ȡ��ǰ��������
		const TexturePtr& GetTexture() const { return m_texture; }

		// ��ȡ������Viewport
		const Vector4 GetViewport( int nodeIdx) const;  

		// ��ȡ�����Ϣ
		const Node& GetNode( int nodeIdx) const { return m_nodes[nodeIdx]; }

		// ��ȡ��
		int GetWidth() const { return m_width; }

		// ��ȡ��
		int GetHeight() const { return m_height; }

		// ����
		void Load( const char* filePath);

		// ����
		void Save( const char* filePath);

	private:
		// ��ʼ��
		void Init( TexturePtr& texture);

		// ��������
		int Insert(  int nodeIdx, const TexturePtr& subTex);

	private:
		int					m_width;			// �����
		int					m_height;			// �����
		TexturePtr			m_texture;			// �����������
		vector<Node>		m_nodes;			// ���ڵ�(����0Ϊ���ڵ�)
	};
}