#ifndef ARES_COLLISION_OBJECT_USERDATA_H
#define ARES_COLLISION_OBJECT_USERDATA_H

namespace Ares
{
	enum COUserDataType
	{
		COU_EntityFilter,		// ʵ��ɸѡ
	};

	//------------------------------------
	// ʵ��ɸѡ 2013-7-8 ����
	//------------------------------------
	class Entity;
	struct COUserDataEntityFilter : public CollisionObject::UserData
	{
		Entity*		m_entity;

		// ���캯��
		COUserDataEntityFilter( Entity* entity)
			: CollisionObject::UserData( COU_EntityFilter)
			, m_entity( entity)
		{}
	};
}

#endif