#pragma once

#include <string>
#include <stdexcept>
#include <boost/exception/all.hpp>

namespace Ares
{
	//-------------------------------------
	// �쳣 2012-3-9 ����
	//-------------------------------------
	struct ares_exception : virtual std::exception, virtual boost::exception
	{};

	// �쳣��Ϣ���Ͷ���
	typedef boost::error_info<struct exception_str, std::string> err_str;

	// �׳��쳣
	#define THR \
	{ \
		stringstream ss; \
		ss << x <<  ":" << __FILE__ << ": " << __LINE__; \
		throw std::runtime_error( ss.str()); \
	}

	// ������󣬾��׳��������
	#define TIF(hr)	\
	{ \
		if ( FAILED(hr)) \
		{ \
			std::stringstream ss; \
			ss << __FILE__ << ": " << __LINE__; \
			throw std::runtime_error( ss.str()); \
		} \
	}
}