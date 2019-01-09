#pragma once

#include <string>
#include "max.h"

using namespace std;

namespace M1_IGame
{
	//----------------------------------------------
	// �������� 2010-08-31   ����
	//----------------------------------------------
	struct SExportConfig
	{
		string  m_m1Location;	// �洢λ��
		string	m_modLocation;	// ģ�ʹ洢λ��
		string  m_matLocation;	// ����λ��
		string  m_aniLocation;	// ����λ��
		string	m_triLocation;	// ������λ��

		bool    binary;			// �Ƿ�����Ƶ���
		Point3  m_scale;
		bool    m_bDDS;			// ��������dds��ʽ
		bool    m_bCopyTexture;	// ��������Ŀ��·��
		BOOL	m_keyFrame;		// �Ƿ񶯻����ȹؼ�֡����
		int		m_sampledensity;// ���������ܶ�

		BOOL	m_exportM1;		// ����m1�ļ�
		BOOL	m_exportMod;	// ����ģ��
		BOOL    m_exportMat;	// ��������
		BOOL	m_exportAni;	// ��������
		BOOL	m_exportTri;	// ��ײ������ 

		string	m_colTriFilter;	// ��ײmesh����

		// ���캯��
		SExportConfig()
		{
			binary = true;
			m_scale.x =  0.01f;
			m_scale.y =  0.01f;
			m_scale.z =  0.01f;
			m_bDDS    =  false;
			m_bCopyTexture = true;
			m_keyFrame	= true;
			m_exportTri = true;

			m_sampledensity = 3;
			m_colTriFilter  = "collision";
		}
	};
}