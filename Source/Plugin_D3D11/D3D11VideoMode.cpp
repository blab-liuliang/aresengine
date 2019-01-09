#include "D3D11VideoMode.h"

namespace Ares
{
	// ���캯��
	D3D11VideoMode::D3D11VideoMode()
		: m_width( 0),
		  m_height( 0),
		  m_format( DXGI_FORMAT_UNKNOWN)
	{

	}

	// ���캯��
	D3D11VideoMode::D3D11VideoMode( UINT width, UINT height, DXGI_FORMAT format)
		: m_width( width),
		  m_height( height),
		  m_format( format)
	{

	}

	// ���ز����� "<"
	BOOL operator < ( const D3D11VideoMode& first, const D3D11VideoMode& second)
	{
		if( first.GetWidth() < second.GetWidth())
		{
			return TRUE;
		}
		else if( first.GetWidth() == second. GetWidth())
		{
			if( first.GetHeight() < second.GetHeight())
			{
				return TRUE;
			}
			else if( first.GetHeight() == second.GetHeight())
			{
				if( first.GetFormat() < second.GetFormat())
					return TRUE;
			}
		}

		return FALSE;
	}

	// ���ز����� "=="
	BOOL operator == ( const D3D11VideoMode& first, const D3D11VideoMode& second)
	{
		return first.GetWidth()  == second.GetWidth() &&
			   first.GetHeight() == second.GetHeight()&&
			   first.GetFormat() == second.GetFormat();
	}
}