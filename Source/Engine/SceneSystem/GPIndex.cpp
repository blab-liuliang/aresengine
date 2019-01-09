#include <Engine/SceneSystem/GPIndex.h>
#include <Core/AresCore.h>

namespace Ares
{
	const CGPIndex CGPIndex::Global = CGPIndex( -65535, -65535, INVALID, INVALID);

	// ���캯��
	CGPIndex::CGPIndex( int x, int y, int width, int height)
		: m_x( x),
		  m_y( y),
		  m_width(  width),
		  m_height( height)
	{

	}

	// ���캯��
	CGPIndex::CGPIndex( const CGPIndex& ref)
		: m_x( ref.m_x),
		  m_y( ref.m_y),
		  m_width(  ref.m_width),
		  m_height( ref.m_height)
	{
		
	}

	// ����
	void CGPIndex::Set(  int x, int y, int width, int height)
	{
		m_x = x;
		m_y = y;

		m_width  = width;
		m_height = height;
	}

	// ��ȡ����
	CGPIndex CGPIndex::GetIndex( int x, int y)
	{
		CGPIndex tGPIndex( x, y, m_width, m_height);

		return tGPIndex;
	}

	// ��ȡXά����ǰ�ĵ�n��GPIndex
	size_t CGPIndex::GetPreviousX( int n)
	{
		return m_x - n;
	}

	// ��ȡYά����ǰ�ĵ�n��GPIndex
	size_t CGPIndex::GetPreviousY( int n)
	{
		return m_y - n;
	}

	// ��ȡXά�����ĵ�n��GPIndex
	size_t CGPIndex::GetNextX( int n)
	{
		return m_x + n;
	}

	// ��ȡYά�����ĵ�n��GPIndex
	size_t CGPIndex::GetNextY( int n)
	{
		return m_y + n;
	}

	// ��������� "<"
	bool CGPIndex::operator < (const CGPIndex indexRH) const
	{
		if( m_y < indexRH.m_y)
		{
			return true;
		}
		else if( m_y == indexRH.m_y)
		{
			if( m_x < indexRH.m_x)
				return true;

			return false;
		}

		return false;
	}

	// ��������� "=="
	bool CGPIndex::operator == (const CGPIndex indexRH) const
	{
		if( m_x == indexRH.m_x && m_y == indexRH.m_y)
			return true;

		return false;
	}

	// ��������� ��<=��
	bool CGPIndex::operator <= (const CGPIndex indexRH) const
	{
		if( (*this) == indexRH || (*this) < indexRH)
			return true;

		return false;
	}
}