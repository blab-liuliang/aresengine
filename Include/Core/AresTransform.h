#pragma once

#include <bitset>
#include "AresMath.h"

using namespace std;

namespace Ares
{
	////-----------------------------------------------
	//// RTTransform 2012-11-13 ����
	//// Transforms with only translation and roation
	////-----------------------------------------------
	//struct RTTransform
	//{
	//public:
	//	// ���캯��
	//	RTTransform();

	//	// ����ԭ��
	//	void SetOrigin( const Vector3& origin) { m_origin = origin; }

	//	// ������ת
	//	void SetRotation( const Quat& quat) { m_rotation = quat; }

	//	// �������
	//	Matrix44 GetMatrix() const;

	//	// ���л�
	//	template <typename Archive>
	//	void serialize( Archive& ar, const unsigned int version)
	//	{
	//		ar & m_rotation;
	//		ar & m_origin;
	//	}

	//protected:
	//	Quat		m_rotation;			// ��ת
	//	Vector3		m_origin;			// storage for translation
	//};

}