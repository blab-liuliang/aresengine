#ifndef ARES_SOUNDSYSTEM_H
#define ARES_SOUNDSYSTEM_H

#include <Core/AresMath.h>

namespace Ares
{
	//--------------------------------------
	// ������ 2011-07-15   ����
	//--------------------------------------
	class  ISound
	{
	public:
		// ����3D����
		virtual bool Set3DAttributes( const Vector3& pos, const Vector3& velocity)=0;
	};

	//--------------------------------------
	// ������ 2011-07-15   ����
	//--------------------------------------
	class  ISoundBox
	{
	public:
		// ����3D����
		virtual bool Set3DAttributes( const Vector3& pos, const Vector3& velocity)=0;
	};


	//-----------------------------------
	// ����ϵͳ 2013-7-8 ����
	//-----------------------------------
	class SoundSystem
	{
	public:
		SoundSystem(){}
		virtual ~SoundSystem(){}

		// ����ϵͳ
		static SoundSystem* Create();

		// ��ʼ��
		virtual bool Init( int numsoftwarechannels)=0;

		// ��������
		virtual bool PlaySound( const char* fileName)=0;

		// ��������
		virtual bool PlaySound( ISound* sound){ return false;}

		// ��������
		virtual ISound* LoadSound( const char* fileName)=0; 

		// ��������
		virtual bool Set3DListenerAttributes(  int listener, const Vector3& pos, const Vector3& velocity, const Vector3& forward, const Vector3& up)=0;		
	};
}

#endif