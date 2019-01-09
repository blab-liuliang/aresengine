#pragma once

#include <map>
#include <string>
#include <fmod.hpp>
#include <Core/AresMath.h>
#include "AresSoundSystem.h"

using namespace std;

namespace Ares
{
	//---------------------------------------
	// SoundSystem 2010-08-03  ����
	//---------------------------------------
	class Win32SoundSystem : public SoundSystem
	{
		struct SSoundChannel
		{
			FMOD::Sound*	m_sound;
			FMOD::Channel*  m_channel;

			// ���캯��
			SSoundChannel()
			{
				m_sound   = NULL;
				m_channel = NULL;
			}
		};

		typedef map<string, SSoundChannel*>   SoundMap;

	public:
		Win32SoundSystem();
		~Win32SoundSystem();

	public:
		// ��ʼ��
		virtual bool Init( int numsoftwarechannels);

		// ��������
		virtual bool PlaySound( const char* fileName);

		// ��������
		virtual bool PlaySound( ISound* sound){ return false;}

		// ��������
		virtual ISound* LoadSound( const char* fileName); 

		// ��������
		virtual bool Set3DListenerAttributes(  int listener, const Vector3& pos, const Vector3& velocity, const Vector3& forward, const Vector3& up);

	private:
		// �����ļ�����ȡ����
		SSoundChannel* GetSoundChannel( const char* fileName);

		// �½�������ͨ��
		SSoundChannel* NewSoundChannel( const char* fileName);

	private:
		FMOD::System	*m_system;			// ����������

		SoundMap         m_soundList;		// �����б�
	};
}