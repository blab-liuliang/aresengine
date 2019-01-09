#pragma once

#include <vector>
#include <boost/any.hpp>

using namespace std;
using namespace boost;

namespace Ares
{
	//-----------------------------------------
	// �����������  2010-11-19 thanks boost
	//-----------------------------------------
	typedef vector<any> AresAnyParams;

	//-----------------------------------------
	// �������Ա�����ص� 2010-11-19  ����
	// ժ�� <<CEGUI.CGGUIMemberFunctionSlot.h>>
	//-----------------------------------------
	template< typename T, typename R>
	class CMemFunGeneralSlot
	{
		typedef R( T::*MemberFunctionType)( AresAnyParams);
	public:
		// ���캯��
		CMemFunGeneralSlot( MemberFunctionType func, T* obj):
			m_function( func),
			m_pObject( obj)
		{}

		// () ����
		bool operator()( AresAnyParams argv){
			return (m_pObject->*m_function)( argv);
		}
		
	private:
		MemberFunctionType  m_function;		// ��Ա����
		T*                  m_pObject;		// ��ָ��
	};

	//-----------------------------------------
	// �޲γ�Ա�����ص� 2010-11-19  ����
	//-----------------------------------------
	template< typename T, typename R>
	class CMemFun0ParamSlot
	{
		typedef R( T::*MemberFunctionType)();
	public:
		// ���캯��
		CMemFun0ParamSlot( MemberFunctionType func, T* obj):
		  m_function( func),
			  m_pObject( obj)
		  {}

		  // () ����
		  bool operator()(){
			  return (m_pObject->*m_function)();
		  }

	private:
		MemberFunctionType  m_function;		// ��Ա����
		T*                  m_pObject;		// ��ָ��
	};
}