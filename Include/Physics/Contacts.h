#pragma once

#include <Core/AresMath.h>

namespace Ares
{
	//----------------------------------------
	// ��ײ�Ӵ� 2012-11-19	���� 
	//----------------------------------------
	class CollisionObject;
	struct Contact
	{
		Vector3				m_point;			// the position of the contact in world coordinates
		Vector3				m_normal;			// the direction of the contact in world coordinates
		float				m_depth;			// the depth of penetration at the contact point

		CollisionObject*	m_body0;			// ��ײ����0
		CollisionObject*	m_body1;			// ��ײ����1

		Contact() 
			: m_body0( NULL) , m_body1( NULL)
		{}
	};

	//------------------------------------
	// ��ײ���	2012-11-19 ����
	//------------------------------------
	class ContactResult
	{
	public:		
		// ���������"[]" const
		Contact& operator[]( INT i)
		{
			return m_contacts[i];
		}

		// ���
		void AddContact( CollisionObject* objectA, CollisionObject* objectB, const Vector3& normal, const Vector3& point0, const Vector3& point1)
		{
			Contact contact;
			contact.m_body0  = objectA;
			contact.m_body1	 = objectB;
			contact.m_normal = normal;
			contact.m_point  = 0.5f * ( point0+point1);
			contact.m_depth  = 0.5f * ( point0-point1).Length();

			m_contacts.push_back( contact);
		}

		// ��ȡ��С
		size_t GetSize() { return m_contacts.size(); }

	private:
		std::vector<Contact> m_contacts;		// ���Ż�
	};
}