#pragma once

#include <string>
#include <Core/AresMath.h>

using namespace std;

namespace Ares
{
	//------------------------------------
	// ��������ת�� 2013-1-23 ����
	//     ����༭������
	//------------------------------------
	namespace DTC
	{
		// Vector3 ת string
		string Vector3ToString( const Vector3& vec);

		// string ת Vector3
		Vector3 StringToVector3( const string& str);

		// ColorRGB ת string
		string ColorRGBToString( const ColorRGB& color);

		// string ת ColorRGB
		ColorRGB StringToColorRGB( const string& str);
	}

}