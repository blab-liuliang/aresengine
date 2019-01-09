#include "CMDLine.h"
#include <string>
#include "AILogic.h"

namespace Ares
{
	// ���������
	bool CMDLine::Parser( int argc, char* argv[])
	{
		if( argc > 1)
		{
			// ���ɵ�������
			if( std::string(argv[1]) == "gnav")
				GenerateNavMesh( argc, argv);

			return true;
		}

		return false;
	}

	// ������������
	void CMDLine::GenerateNavMesh( int argc, char* argv[])
	{
		CAILogic::BuildNavMesh( argv[2], argv[3], argv[4], argv[5]);
	}
}