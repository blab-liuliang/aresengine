//#pragma once
//
//namespace Ares
//{
//	class CBufferMgr
//	{
//	public:
//		// ��Ⱦ�ö����ʽ����
//		struct SPRITE_VERTEX
//		{
//			Vector3 m_pos;		// ����λ��	
//			float   m_size;		// λ�úͳߴ�����˻�������
//			DWORD   m_color;	// ������ɫ
//		};
//
//		// ��ȡ�㾫��Buffer
//		static SPtr<IVertexBuffer>& GetSpriteBuffer();
//
//		// ��ȡ�㾫���ø�ʽ
//		static SPtr<IVertexDeclaration>& GetSpritieDeclaration();
//
//	private:
//		static SPtr<IVertexBuffer>      m_spriteBuffer;		// �㾫����Buffer
//		static SPtr<IVertexDeclaration> m_spriteDeclaration;// �㾫���ʽ����
//	};
//
//	#define SPRITE_VERTEX  CBufferMgr::SPRITE_VERTEX
//}