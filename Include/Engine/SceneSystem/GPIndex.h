#pragma once

#include <Core/AresCore.h>

namespace Ares
{
	//----------------------------------
	// GP���� 2011-08-17  ����
	//----------------------------------
	class CGPIndex
	{
	public:
		static const CGPIndex Global;

	public:
		CGPIndex() {}
		CGPIndex( int x, int y, int width, int height);
		CGPIndex( const CGPIndex& ref);
		~CGPIndex(){}

	public:
		// ����
		void Set(  int x, int y, int width, int height);

		// ����Xλ��
		void SetX( int x) { m_x = x; }

		// ����Yλ��
		void SetY( int y) { m_y = y; }

		// ���ÿ�
		void SetWidth( int width) { m_width = width; }

		// ���ø�
		void SetHeight( int height) { m_height = height; }

	public:
		// ��ȡXλ��
		int GetX() const { return m_x; }

		// ��ȡYλ��
		int GetY() const { return m_y; }

		// ��ȡ��
		int GetWidth() const { return m_width; }

		// ��ȡ��
		int GetHeight() const { return m_height; }

	public:
		// ��ȡ����
		CGPIndex GetIndex( int x, int y);

		// ��ȡXά����ǰ�ĵ�n��GPIndex
		size_t GetPreviousX( int n);

		// ��ȡYά����ǰ�ĵ�n��GPIndex
		size_t GetPreviousY( int n);

		// ��ȡXά�����ĵ�n��GPIndex
		size_t GetNextX( int n);

		// ��ȡYά�����ĵ�n��GPIndex
		size_t GetNextY( int n);

	public:
		// ��ȡά��(��ǰΪ2ά)
		int GetDimensions() { return 2; }

	public:
		// ��������� "<"
		bool operator < (const CGPIndex indexRH) const;

		// ��������� "=="
		bool operator == (const CGPIndex indexRH) const;

		// ��������� ��<=��
		bool operator <= (const CGPIndex indexRH) const;

		// ���л�
		template <typename Archive> void serialize( Archive& ar, const unsigned int version)
		{
			ar & m_x & m_y & m_width & m_height;
		}

	private:
		int		m_x;
		int		m_y;
		int		m_width;
		int		m_height;
	};
}