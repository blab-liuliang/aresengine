#pragma once

#include <string>
#include <vector>
#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include <boost/system/error_code.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

using namespace boost;
using namespace boost::asio;
using namespace boost::asio::ip;

namespace Net
{
	//------------------------------------
	// ���������߼� 2012-9-3 ����
	//------------------------------------
	class client
	{
		typedef boost::shared_ptr<tcp::socket>  socket_ptr;
		typedef boost::shared_ptr<std::vector<char>> buffer_ptr;
	public:
		// ���캯��
		client();

		// ��ʼ����
		void run();

		// ���ӷ�����
		void connect( const char* ip, int port);

		// �첽��
		void read();

		// �첽д
		void write( const char* data);

	private:
		// internal run
		void internal_run();

		// �첽���ӵ���
		void conn_handler( const system::error_code& ec, socket_ptr sock);

		// �첽������
		void read_handler( const system::error_code& ec, buffer_ptr str);

		// �첽д����
		void write_handler( const system::error_code& ec);

	private:
		io_service	m_ios;			// io_service
		socket_ptr	m_socket;		// �׽���
	};
}