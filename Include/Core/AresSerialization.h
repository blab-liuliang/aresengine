#pragma once

#include <string>
#include <ostream>
#include <fstream>
#include <istream>
#include <boost/serialization/serialization.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/set.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/serialization/export.hpp>

using namespace std;

namespace Ares
{
	//--------------------------------------------
	// ���л�(���������) 2011-10-27 ����
	//--------------------------------------------
	namespace Serialization
	{
		// ���л����������ļ�
		template <typename T> void SerializeToBinaryFile( const char* filename, const T& object)
		{
			ofstream ofs( filename, ios::binary | ios::out);
			if( ofs.is_open())
			{
				boost::archive::binary_oarchive boarchive( ofs);
				boarchive << object;
			}
		}

		// �������ļ������л�
		template <typename T> void UnSerializeFromBinaryFile( const char* filename, T& object)
		{
			ifstream ifs( filename, ios::binary | ios::in);
			if( ifs.is_open())
			{
				boost::archive::binary_iarchive biarchive( ifs);
				biarchive >> object;
			}
		}

		// ���л����ı��ļ�
		template <typename T> void SerializeToTextFile( const char* filename, const T& object)
		{
			ofstream ofs( filename, ios::out);
			if( ofs.is_open())
			{
				boost::archive::text_oarchive toarchive( ofs);
				toarchive << object;
			}
		}

		// �ı��ļ������л�
		template <typename T> void UnSerializeFromTextFile( const char* filename, T& object)
		{
			ifstream ifs( filename, ios::in);
			if( ifs.is_open())
			{
				boost::archive::text_iarchive tiarchive( ifs);
				tiarchive >> object;
			}
		}

		// ����ַ���
		void PackString( string& out, const vector<float>& source, char separator);

		// ����ַ���
		void PackString( string& out, const vector<int>& source, char separator);

		// ����ַ���(float)
		void UnPackString(vector<float>& out, const string& source, char separator);

		// ����ַ���(int)
		void UnPackString(vector<int>& out, const string& source, char separator);
	};
}