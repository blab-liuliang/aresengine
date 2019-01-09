#include <Engine/FxSystem/AresFxObject.h>
#include <Engine/FxSystem/AresFxEntity.h>

namespace Ares
{
	// ��ȡ����ת��
	Transform FxObject::GetWorldTransform()
	{
		Transform result;
		if( m_entity)
			result = m_entity->GetTransform();

		return result * (*GetTransform());
	}
}