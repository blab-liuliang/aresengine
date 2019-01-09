#include "Engine/UISystem/MyGUI_Diagnostic.h"
#include "Engine/AresRoot.h"

using namespace Ares;

namespace MyGUI
{
	// ��־
	void MyGUI_Logging( int level, const char* msg)
	{
		switch( level)
		{
		case Info:
		case Warning:
		case Error:
		case Critical:
			{
				ALogSystem.Warning( "%s", msg);
			}
			break;
		}
	}
}