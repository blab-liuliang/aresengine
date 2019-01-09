#pragma once
#include <stdio.h>
#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <vector>
#include <map>
#include <Core/3rdParty/LZO/minilzo.h>

using namespace std;

//��ʼ���ַ�����
#define STRING_INIT(chararray)	  chararray[0] = '\0';
//ȡ�������С
#define ARRAY_SIZE(chararray)	  (sizeof(chararray)/sizeof(chararray[0]))
//�ַ�����ȫ����
//��1Ŀ�괮
//��2������
#define STRING_COPY_ALL( chararray ,srcstr )	strcpy_s(chararray,ARRAY_SIZE(chararray),srcstr);

#define FILE_HEADER_NAME_MAX_SIZE	50
#define FILE_HEADER_AUTHOR_MAX_SIZE	60
#define SAFE_DELETE(p)  { if(p) { delete (p); (p)=NULL; } }
#define SAFE_DELETE_ARRAY(p) { if(p) { delete[] (p);   (p)=NULL; } }

//��ģ����Ⱦ״̬m_dwRenderFlag��λ
#define RENDERFLAG_LOW_NOALPHA					0				//��ͨ��ALPHA
#define RENDERFLAG_LOW_ALPHABLEND				1				//ʹ��ALPHA���
#define RENDERFLAG_LOW_ALPHATEST				2				//ʹ��ALPHA����

//��ģ����Ⱦ״̬m_dwRenderFlag��λ
#define RENDERFLAG_HIGH_REFLECT					1				//����
#define RENDERFLAG_HIGH_DROPNORMAL				2				//�������߼���
#define RENDERFLAG_HIGH_FOGINVALID				4				//������Ӱ��
#define RENDERFLAG_HIGH_CULLMODE_NONE			8				//������Ⱦ
#define RENDERFLAG_HIGH_COMBOBATCH				16				//��ϴ����Ⱦ
#define RENDERFLAG_HIGH_NOUSETEXLOD				32				//����������LOD

//������Ϸ��Դ����
#define GAMERES_MESH_S						0				//��̬ģ��
#define GAMERES_MESH_D						1				//������ģ��
#define GAMERES_MATERIAL					2				//����
#define GAMERES_SKINANI						3				//����
#define GAMERES_UVANI						4				//UV����
#define GAMERES_BOUNDINGBOX					5				//�󶨺�


//ģ�ͱ������
#define MESHFLAG_NORMAL						0				//��ͨ
#define MESHFLAG_USEBOUNDINGBOXMESH			1				//ʹ�ð󶨺�ģ��
#define MESHFLAG_USEBUMPVERTEX				2				//ʹ�ð�͹��ͼ�����ʽ
#define MESHFLAG_USEALPHABLEND				4				//�Ƿ�ʹ��ALPHA��Ⱦ
#define MESHFLAG_BOUNDINGMESHPICKTYPE		8				//���հ�ģ�ͷ�ʽ���м�ѡ
#define	MESHFLAG_SWING						16				//�Ƿ�ҡ��
#define MESHFLAG_ALPHACOLOR					32				//ɫ��ֵ����ALPHA��ɫ��Ϊ��
#define MESHFLAG_NOCHECKDISTANCEVISIBLE		64				//���벻Ӱ����ʾ
#define MESHFLAG_WATER						128				//����ˮģ��
#define MESHFLAG_LIGHTMAPUV					256				//ʹ��LightMap UV


//ģ������
#define MESHTYPE_SHAPE						0				//����ͼ��
#define MESHTYPE_PATCHOBJ					1				//PATCH BOJ							
#define MESHTYPE_TRIOBJ						2				//����ģ��
#define MESHTYPE_BONE						3				//����ģ��

struct	SFileHeader
{
	BYTE	Ver;										// �汾
	char	Name[FILE_HEADER_NAME_MAX_SIZE];			// ����
	char	Author[FILE_HEADER_AUTHOR_MAX_SIZE];		// ����IP
	DWORD	Type;										//����	[��8λ�����ͣ���24λ���ڱ��]
	int		NodeNum;									//�ڵ�����

	SFileHeader()
	{
		STRING_INIT(Name);
		STRING_INIT(Author);
	}

};
//�Ż������Ķ���
struct  SExport_Vertex
{
	float	m_fPosX;					//X��Y��Z	
	float	m_fPosY;
	float	m_fPosZ;

	float   m_fNPosX;					//Normal
	float	m_fNPosY;
	float   m_fNPosZ;

	float   m_fRed;					//����ɫ
	float	m_fGreen;
	float   m_fBlue;

	float   m_fU;						//����
	float   m_fV;		

public:
	//���ز�����
	bool   operator == (SExport_Vertex   &v)
	{
		if(m_fPosX != v.m_fPosX)return false;
		if(m_fPosY != v.m_fPosY)return false;
		if(m_fPosZ != v.m_fPosZ)return false;
		if(m_fNPosX != v.m_fNPosX)return false;
		if(m_fNPosY != v.m_fNPosY)return false;
		if(m_fNPosZ != v.m_fNPosZ)return false;
		if(m_fRed != v.m_fRed)return false;
		if(m_fGreen != v.m_fGreen)return false;
		if(m_fBlue != v.m_fBlue)return false;
		if(m_fU != v.m_fU)return false;
		if(m_fV != v.m_fV)return false;
		return true;
	}
}
;

//�Ż���������
struct   SExport_Face
{
	int		m_nVertexIndex1;			//��������
	int		m_nVertexIndex2;
	int		m_nVertexIndex3;
}
;


//�����ܹ���Ȩ��Ӱ����Ϣ
struct	SVertex_BoneWeight
{
	int		m_nVertexIndex;			//��������
	int		m_nBoneIndex;			//��������
	float   m_fWeight;				//Ӱ��Ȩ��
}
;

//��ģ��
struct	SSubMesh
{
	char	m_szSubMeshName[60];		//��ģ������(�Ӳ��ʷֽ��ģ������)
	char	m_szOldMeshName[60];		//ԭģ������(�Ӳ��ʷֽ�ǰ��ģ������)
	DWORD	m_dwMeshType;				//ģ������
	int		m_nMaterialID;			//��������
	int		m_nRed;					//ɫ��
	int		m_nGreen;
	int		m_nBlue;
	int		m_nAlpha;
	int		m_nVertexNum;				//������
	int		m_nEdgeNum;				//����
	int		m_nFaceNum;				//����
}
;
//ģ�;���
struct SMeshMatrix
{
	FLOAT	 m[16];
}
;

struct	SSubMesh_Temp
{
	SSubMesh						m_sSubMeshInfo;				//��ģ����Ϣ
	D3DXMATRIX						m_matSubMeshMatrix;			//��ģ�͵ľ���
	vector<SExport_Vertex>			m_pVertexArray;				//������Ϣ
	vector<SExport_Face>			m_pFaceArray;				//����Ϣ
	int								m_nBoneInfoIndex;			//������Ϣ����
	int								m_nVertexBoneWeightNum;		//Ȩ������
	vector<SVertex_BoneWeight>		m_pVertexBoneWeightArray;	//�����ܹ���Ȩ��Ӱ��
	vector<D3DXVECTOR2>				m_pLightMapUVArray;			//LightMap��UV��Ϣ����
	DWORD							m_dwRenderFlag;				//��Ⱦ��־
	int								m_nSwingSpeed;				//ҡ���ٶ�
	int								m_nSwingRegion;				//ҡ�ڷ���
	float							m_fNormalLevel;				//����ǿ��ֵ
}
;
struct SMeshNode_Temp
{
	//����
	int								m_nSubMeshNum;
	//D3Dģ����
	vector<SSubMesh_Temp>			m_pSubMeshArray; 
}
;

struct	STexture
{
	int					m_nIndex;						//��Ӧ��ͨ������
	char				m_szFileName[60];				//�ļ���
}
;
//���ʽ��
struct	SMatNode_New
{
	DWORD	m_dwMatType;											//��������	(0 :��ͨ  1:���ز���)
	DWORD	m_dwGHBump;											//��ͼ���������
	int		m_nNum;												//��ͼ���������
	int		m_nUVAniNum;											//UV��������	
}
;
//����
struct	SMatNode_Temp
{
	SMatNode_New			m_sMatInfo;
	float					m_fShininess ;							//����ϵ��
	float					m_fShinStr ;							//�߹�ϵ��
	int						m_nMaterialNum;
	vector<int>				m_pMaterialArray;
	int						m_nTextureNum;
	vector<STexture>		m_pTextureArray;
}
;
//��͹��ͼ��Ϣ
struct	SBumpInfo
{
	//���ð�͹��ͼ����
	D3DXVECTOR4					m_vec4BumpACColor;
	D3DXVECTOR4					m_vec4BumpSCColor;
	FLOAT						m_fBumpSPValue;
	FLOAT						m_fBumpSLValue;
	D3DXVECTOR4					m_vec4BumpECColor;
	D3DXVECTOR4					m_vec4BumpSkCColor;
	D3DXVECTOR4					m_vec4BumpSkACColor;
}
;


class YNDMeshFile
{

public:
	//����
	YNDMeshFile();
	//����
	~YNDMeshFile();

	//���
	VOID						CleanUp();
	//���ļ��ж�ȡ����
	BOOL						ReadDataFromFile(const char* szFileName);
	//ȡ��ģ��������
	int							Fun_GetMeshNodeNum();
	//ȡ�ö�Ӧģ����
	SMeshNode_Temp*				Fun_GetMeshNodePtr(int vIndex);

	//ȡ�ò�������
	int							Fun_GetTextureNum();
	//ȡ�ö�Ӧ�Ĳ���
	STexture*					Fun_GetTexturePtr( int vIndex);
	//ȡ�ò��ʵ���ͼ����
	const char*					Fun_GetTextureName( int	vIndex);
	//ȡ�ñ��
	BOOL						CheckFlag(DWORD vHeaderType,WORD	vFlag);
private:

	//ͷ��Ϣ
	SFileHeader					m_sFileHeader;
	//����ģ�͵���ѡ��
	int							m_nAniMeshType;
	//ģ������
	int							m_nMeshNum;
	//ģ����
	vector<SMeshNode_Temp>		m_pMeshNodeArray;	

	//��ģ������
	int							m_nAllSubMeshNum;

	//��ͼ��
	int							m_nTextureNum;
	vector<STexture>			m_pTextureVec;

	//�������������������ڼ�����ײ�ã���Ȼ��Ҳ���Թ���������ʹ�á�
	//���������
	int							m_nAllBoundingMeshVertexSize;
	//����
	vector<D3DXVECTOR3>			m_pAllBoundingMeshVertexArray;

	//�������
	int							m_nAllBoundingMeshFaceSize;
	//����Ϣ
	vector<SExport_Face>		m_pAllBoundingMeshFaceArray;

	//�Ƿ��й�������
	bool						m_bHasSkinAni;

	//�Ƿ���֡����
	bool						m_bHasFrameAni;

	//�Ƿ��Ƕ���ģ�͵Ķ���ģ���ļ�
	bool						m_bMultiSubMesh;

	//�Ƿ���ڰ󶨺�ģ��
	bool						m_bBoundingBoxMesh;

	//�Ƿ�����˶���֡��ģ�Ͱ�Χ��
	bool						m_bLoadAniFrameBoundingBoxOK;

	//�Ƿ�ʹ����Ⱦ���
	bool						m_bUserRenderFlag;

	//�Ƿ��ǰ�͹��ͼ�����ʽ
	bool						m_bUseBumpRender;

	//�Ƿ�ҡ��
	bool						m_bUseSwingRender;

	//alphaɫ��
	bool						m_bAlphaColorRender;

	//����Ӱ����ʾ
	bool						m_bDistanceVisible;

	//�Ƿ�ʹ�ð�ģ�ͽ��м�ѡ
	bool						m_bBoundingMeshPickType;

	//�Ƿ�ʹ��LIGHTMAP UV
	bool						m_bUseLightMapUV;

	//�Ƿ���ˮģ��
	bool						m_bIsWaterMesh;

	//�Ƿ��ڴ�����ɺ�ɾ������ײ��
	bool						m_bAutoDeleteBoundingVertexAndFace;
	//ָ���Ĺ����ļ�
	char						m_szActionFileName[100];
};