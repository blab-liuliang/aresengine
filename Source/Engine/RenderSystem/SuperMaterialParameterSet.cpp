#include <algorithm>
#include <Engine/RenderSystem/SuperMaterialParameterSet.h>

namespace Ares
{
	// ��������� "="
	void SMStaticParameterSet::operator = (const SMStaticParameterSet& src)
	{
		m_items = src.m_items;
	}

	// ��Ӳ���
	void SMStaticParameterSet::SetParameter( const char* name, ShaderParamPtr sparam, const char* spab)
	{
		if( name && strlen(name)>0)
		{
			int oIdx;
			if( !IsExistedParameter( name, &oIdx))
			{
				ParameterItem item;
				item.m_name = name;
				item.m_auto = spab ? spab : "";
				item.m_value= sparam;
				m_items.push_back( item);
			}
			else
			{
				m_items[oIdx].m_value = sparam;
				if( spab)
					m_items[oIdx].m_auto = spab;
			}
		}
	}

	// �Ƿ��Ѵ���
	bool SMStaticParameterSet::IsExistedParameter( const char* name, int* oIdx)
	{
		for( size_t i=0; i<m_items.size(); i++)
		{
			if( m_items[i].m_name==name) 
			{
				if( oIdx)
					*oIdx = (int)i;

				return true;
			}
		}

		return false;
	}
}