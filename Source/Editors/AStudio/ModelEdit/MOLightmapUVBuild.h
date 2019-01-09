#pragma once

#include <string>
#include <d3dx9.h>
#include <Core/AresMath.h>
#include <Physics/Rect3.h>
#include <Engine/RenderSystem/AresModelIDCard.h>
#include <boost/filesystem.hpp>

using namespace boost;
using namespace boost::filesystem;

namespace Ares
{
	//---------------------------------------
	// BuildSettings 2012-7-10 ����
	//---------------------------------------
	struct BuildSettings
	{
		int				m_maxCharts;
		int				m_width;
		int				m_height;
		float			m_maxStretch;
		float			m_gutter;
		BYTE			m_outputTextureIndex;
		bool			m_topologicalAdjacency;
		bool			m_geometricAdjacency;
		bool			m_falseEdges;
		bool			m_fileAdjacency;
		string			m_szAdjacencyFilename;
		string			m_szFalseEdgesFilename;

		bool			m_userAbort;
		bool			m_subDirs;
		bool			m_colorMesh;
		bool			m_verBose;
		bool			m_IMT;
		bool			m_textureSignal;
		bool			m_PRTSignal;
		bool			m_vertexSignal;
		DWORD			m_qualityFlag;
		D3DDECLUSAGE	m_vertexSignalUsage;
		BYTE			m_vertexSignalIndex;
		BYTE			m_IMTInputTextureIndex;
		string			m_szIMTInputFilename;

		// ���캯��
		BuildSettings()
		{
			m_userAbort				= false;
			m_subDirs				= false;
			m_topologicalAdjacency	= false;
			m_geometricAdjacency	= false;
			m_fileAdjacency			= false;
			m_qualityFlag			= D3DXUVATLAS_DEFAULT;

			m_falseEdges			= false;
			m_maxCharts				= 0;
			m_maxStretch			= 1 / 2.f;
			m_gutter				= 4.f;
			m_width					= 512;
			m_height				= 512;
			m_colorMesh				= false;
			m_outputTextureIndex	= 0;

			m_IMT					= false;
			m_textureSignal			= false;
			m_PRTSignal				= false;
			m_vertexSignal			= false;
			m_vertexSignalUsage		= D3DDECLUSAGE_COLOR;
			m_vertexSignalIndex		= 0;
		}
	};

	//--------------------------------------
	// ����ͼUV���ɹ����� 2012-7-10 ����
	//--------------------------------------
	class LightmapUVBuild
	{
	public:
		// ���캯��
		LightmapUVBuild();

		// ָ���ļ�
		void Open( const char* filePath);

		// �����ļ�
		void Save( const char* filePath = NULL);

		// ִ������( *mod, *.�尲)
		void Build( const BuildSettings& config);

		// ��ԭ
		void Restore();

		// ��ȡ���
		void OrganizationResult( vector<Int3>& rIndices, vector<Vector2>& rUvs, Rect2& rUvRect, vector<DWORD>& rFacePartitioning, vector<DWORD>& rVertexRemapArray, ID3DXMesh* inMesh, LPD3DXBUFFER pFacePartitioning, LPD3DXBUFFER pVertexRemapArray);

		// �޸�Mesh
		void ModifyMesh( vector<Int3>& rIndices, vector<Vector2>& rUvs, Rect2& rUvRect, vector<DWORD>& rFacePartitioning, vector<DWORD>& rVertexRemapArray, Mesh::IDCard& mesh);

		// ��ʾ���
		void ShowResult( const vector<Int3>& rIndices, const vector<Vector2>& rUvs);

	private:
		// ����Mod
		void BuildMod();

		// ����D3D9Device
		void CreateNullRefDevice();

		// ��ȡUV��Ӧ
		int VertexMapping(  int idx, Mesh::IDCard& mesh);

		// �����ļ�
		void BackupMod();
		
		// �ж��Ƿ���Դ����
		bool IsOrigMod();

	private:
		path					m_filePath;			// Ҫ���ɹ���ͼuv���ļ�
		BuildSettings			m_settings;			// ��������ѡ��
		IDirect3DDevice9*		m_device;			// ����ѽ(fuck ms)
		vector<Mesh::IDCard*>	m_meshs;			// ģ��
	};

	extern LightmapUVBuild*	g_lightmapUVBuild;
	#define AUVBuild		g_lightmapUVBuild
}