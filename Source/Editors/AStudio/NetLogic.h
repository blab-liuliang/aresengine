#pragma once

namespace Ares
{
	//---------------------------------------
	// NetLogic 2012-9-3 ����
	//---------------------------------------
	//class Net::client;
	class NetLogic
	{
	public:
		NetLogic();

		// �ύBug
		void SubmitBug( const char* bugDesc);

	private:
		//Net::client*		m_client;		// ����ͨѸ
	};
}