#pragma once

namespace Ares
{
	//----------------------------------------
	// AStudio �����н��� 2012-8-16 ����
	//----------------------------------------
	class CMDLine
	{
	public:
		// ���������
		static bool Parser( int argc, char* argv[]);

		// �����������
		static void GenerateNavMesh( int argc, char* argv[]);
	};
}