#include "SCLogic.h"
#include "LightMap.h"

namespace QT_UI
{
	// ���캯��
	Lightmap::Lightmap( QWidget* parent)
		: QMainWindow( parent)
	{
		setupUi( this);

		connect( m_testBake, SIGNAL(clicked()), this, SLOT(Bake()));
	}

	// ��������
	Lightmap::~Lightmap()
	{
	}

	// �決������
	void Lightmap::Bake()
	{
		//LuaScriptPtr script = AResSystem->LoadLuaScript("H:\\AresEngine\\Sdk\\bin\\data\\script\\D3D11Render.lua");

		//script->ExecFunc( "OnInit");

		// �Ƿ񹹽���̬����
		if( m_isBuildStatic->isChecked ())
		{
			// �Ƿ�ֻ������ǰѡ�� 
			if( m_isBuildSelectedOnly->isChecked ())
				BakeSelected();
		}
	}

	// �決
	void Lightmap::BakeSelected()
	{
		RenderEntity* curEntity = SCLogic_EntityEdit->GetEditEntity<RenderEntity>();
		if( curEntity /*&& curEntity->IsStatic()*/)
			Logic_LightmapBake->AddTask( curEntity);
		else
			QMessageBox::warning( this, "Warning", "No static entity is selected!");
	}
}