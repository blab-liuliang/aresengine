#include "NetLogic.h"
#include "client.h"

namespace Ares
{
	// ���캯��
	NetLogic::NetLogic()
	{
		//m_client = new Net::client;
		//m_client->connect( "127.0.0.1", 6688);
		//m_client->run();
	}

	// �ύBug
	void NetLogic::SubmitBug( const char* bugDesc)
	{
		//m_client->write( bugDesc);
	}
}