#pragma once

#include <Core/AresMath.h>
#include <Physics/Shapes.h>

namespace Ares
{
	// 3D������ƽ�� �ռ�λ�ü�� EM_PLANE_FRONT = 0, EM_PLANE_BACK = 1, EM_PLANE_INTERSECT = 2,
	int PlaneClassify( const Rect3& rect, const Plane3& plane);

	// ��������������ײ
	bool Intersect( const Line3& line, const Triangle3& triangle, float& fDist);

	// ͨ����������ڻ�ȡPick����
	bool WindowPointToRay(	Vector3& rayOrig, Vector3& rayDir, LONG x, LONG y, UINT d3dBackBufferWidth, UINT d3dBackBufferHeight, const Matrix44& matView, const Matrix44& matProj);

	// global function
	bool WindowPointToRay( Vector3& rayOrig, Vector3& rayDir, LONG x, LONG y, UINT d3dBackBufferWidth, UINT d3dBackBufferHeight, const Matrix44& matView, const Matrix44& matProj, const Matrix44& matOffset);

	// ��Ļ��ת����3D�ռ�
	void ScreenPointTo3DSpace( Vector3& result, LONG x, LONG y, LONG screenWidth, LONG screenHeight, const Matrix44& transform);
}