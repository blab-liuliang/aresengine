#pragma once

#include "AresEntity.h"
#include "GPTile.h"
#include <string>
#include <map>
#include <vector>
#include <boost/shared_ptr.hpp>

using namespace std;
using namespace boost;

namespace Ares
{
	//----------------------------
	// QtGPTile 2011-08-18 ����
	//----------------------------
	class SceneTile : public CGPTile
	{
		friend class Scene;
		typedef map<string, s_ptr<Entity> > EntityList;
	public:
		SceneTile( const char* fileLocation);
		~SceneTile();

		// ���ʵ��
		void AddEntity( const char* uniqueName, EntityPtr pEntity);

		// ɾ��ʵ��
		void DelEntity( const char* name);

	public:
		// ��ȡ�洢λ��
		const string& GetLocation() const { return m_location; }

		// ��ȡ��Χ��
		void GetBoundingBoxByLayer( Rect3& box, const char* layer, bool update=false);

	protected:
		// ��������
		virtual void Load();

		// ж������
		virtual void Unload();

		// ����Tile
		void Save();

	private:
		string				m_location;		// ����λ��
		int					m_version;		// �汾��
		EntityList			m_entitys;		// ��
	};
}