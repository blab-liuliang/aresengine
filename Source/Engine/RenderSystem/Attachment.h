#pragma once

#include <string>
#include "Engine/SceneSystem/SceneNode.h"

using namespace std;

namespace Ares
{
	//--------------------------------
	// Attachment 2011-08-08 ����
	// ˵����
	//     ��ɫ����,������
	//--------------------------------
	struct SAttachment
	{
		string			 m_boneName;	// ������
		int				 m_boneIdx;		// ��������
		//s_ptr<SceneNode>  m_sceneNode;	// ���(����������Ϊ������,���Ծ�������SceneNode)	
	};
}