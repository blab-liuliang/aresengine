#include "Init.h"
#include "IGame.h"

namespace M1_IGame
{
	IGameScene *  g_pIGame = NULL;

	// ���³���ʱ,��ʼ������
	void  InitScene()
	{
		g_pIGame = GetIGameInterface();

		// ��������ϵ
		IGameConversionManager* pCM = GetConversionManager();

		UserCoord IGame_Ares = 
		{
			0,	// Left handed coordinate system
			1,  // X Axis goes right
			4, // Y Axis goes in
			2,  // Z Axis goes up
			1,	// U Tex axis is Right
			1,  // V Tex axis is Down
		};

		pCM->SetUserCoordSystem( IGame_Ares);

		// �������� or ֻ����ѡ��
		g_pIGame->InitialiseIGame( false);
		g_pIGame->SetStaticFrame( 0);
	}
}