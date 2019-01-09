#include "Function.h"
#include "stdmat.h"
//#include "BoneKeeper.h"
#include "cs/bipexp.h"
#include "max.h"
#include "stdmat.h"
#include "decomp.h"
#include <algorithm>
#include "AeConfig.h"

namespace M1_IGame
{
	extern SExportConfig  g_config;	// ��������

	// �Ӳ��ʵ�Diffuse slot�л�ȡ����
	void  GetIndicesFromTexMap( int& i1, int& i2, Mtl* _mtl)
	{
		if( !_mtl) return;

		// Get the bitmapTexture which is in the diffuse
		BitmapTex* tMap = static_cast<BitmapTex*>( _mtl->GetSubTexmap( ID_DI));
		if( !tMap || tMap->ClassID() != Class_ID( BMTEX_CLASS_ID, 0)) return;

		// Get information about uvs from Material
		UVGen* pUVGen = tMap->GetUVGen();
		if ( pUVGen)
		{
			// Get the axis used to get the suitable indices
			const int iAxis = pUVGen->GetAxis();
			switch ( iAxis)
			{
			case AXIS_UV:
				{
					i1 = 0;
					i2 = 1;
				}
				break;

			case AXIS_VW:
				{
					i1 = 1;
					i2 = 2;
				}
				break;

			case AXIS_WU:
				{
					i1 = 2;
					i2 = 0;
				}
				break;
			}
		}
	}


	// ��ȫ��·���в�ֳ�������,�ɸ��ĺ�׺��
	string SplitNameExt( const char* fullPath, const char* aimExt)
	{
		// ȥ������·��
		char  fileName[128];
		char  fileExt[20];
		char  fileNameAndExt[148];

		_splitpath( fullPath, NULL, NULL, fileName, fileExt);

		if ( aimExt) sprintf( fileNameAndExt, "%s%s", fileName, aimExt);
		else		 sprintf( fileNameAndExt, "%s%s", fileName, fileExt);

		return fileNameAndExt;
	}

	// ����PhysiqueModifier
	Modifier*  FindPhysiqueModifier( INode* pNode)
	{
		// Get object from node, abort if no object
		Object* pObject = pNode->GetObjectRef();

		if( !pObject)
			return NULL;

		// Is derived object
		if ( pObject->SuperClassID() == GEN_DERIVOB_CLASS_ID)
		{
			// Yes -> Cast
			IDerivedObject* pDerivedObject = static_cast<IDerivedObject*>(pObject);

			// Iterate over all entries of the modifier stack
			int modStackIndex=0;
			while ( modStackIndex < pDerivedObject->NumModifiers())
			{
				// Get current modifier
				Modifier* pModifier = pDerivedObject->GetModifier( modStackIndex);

				// Is this Physique ?
				if (pModifier->ClassID() == Class_ID(PHYSIQUE_CLASS_ID_A, PHYSIQUE_CLASS_ID_B))
				{
					return pModifier;
				}

				// Next modifier stack entry.
				modStackIndex++;
			}
		}

		// not found
		return NULL;
	}

	Modifier* FindMaxSkinModifier( INode* nodePtr)
	{
		// Get object from node. Abort if no object.
		Object* ObjectPtr = nodePtr->GetObjectRef();

		if (!ObjectPtr) return NULL;

		// Is derived object ?
		if (ObjectPtr->SuperClassID() == GEN_DERIVOB_CLASS_ID) 
		{
			// Yes -> Cast.
			IDerivedObject* DerivedObjectPtr = static_cast<IDerivedObject*>(ObjectPtr);

			// Iterate over all entries of the modifier stack.
			int ModStackIndex = 0;
			while (ModStackIndex < DerivedObjectPtr->NumModifiers())
			{
				// Get current modifier.
				Modifier* ModifierPtr = DerivedObjectPtr->GetModifier(ModStackIndex);

				//DebugBox("Modifier Testing: %i \n",ModStackIndex);

				// Is this Physique ?
				if( ModifierPtr->ClassID() == SKIN_CLASSID/* Class_ID(9815843,87654) */) //PHYSIQUE_CLASS_ID_A, PHYSIQUE_CLASS_ID_B))
				{
					// Yes -> Exit.
					return ModifierPtr;
				}
				// Next modifier stack entry.
				ModStackIndex++;
			}
		}
		// Not found.
		return NULL;
	}

	// ת����ARES����ϵ
	D3DXMATRIX MAXtoARES( Matrix3& mat)
	{
		AffineParts parts;
		decomp_affine( mat, &parts);

		D3DXMATRIX matOffset;
		D3DXMATRIX matScale;
		D3DXMATRIX matTrans;
		D3DXQUATERNION quatD3DX;

		quatD3DX.x =  parts.q.x;
		quatD3DX.y =  parts.q.y;
		quatD3DX.z =  parts.q.z;
		quatD3DX.w =  parts.q.w;

		D3DXMatrixIdentity( &matOffset);
		D3DXMatrixIdentity( &matTrans);

		// ��ת
		D3DXMatrixRotationQuaternion( &matOffset, &quatD3DX);

		// ����
		D3DXMatrixScaling( &matScale, parts.k.x, -parts.k.y, parts.k.z);

		// ƽ��
		//D3DXMatrixTranslation( &matTrans, parts.t.x, parts.t.y, parts.t.z);
		D3DXMatrixTranslation( &matTrans, parts.t.x * 0.0154f, -parts.t.y * 0.0154f, parts.t.z * 0.0154f);
		matOffset = matOffset * matScale * matTrans;

		return matOffset;
	}

	// ��������
	void ChangeExt( char* dst, const char* source, const char* ext)
	{
		char tfileDir[2048];
		char tfileName[1024];
		_splitpath( source, NULL, tfileDir, tfileName, NULL);

		strcpy( dst, tfileDir);
		strcat( dst, tfileName);
		strcat( dst, ext);
	}

	// ��������
	void NameExt( char* dst, const char* source)
	{
		char tfileName[1024];
		char tfileExt[1024];
		_splitpath( source, NULL, NULL, tfileName, tfileExt);

		strcpy( dst, tfileName);
		strcat( dst, tfileExt);
	}

	// �ļ�����
	//bool CopyFile(char* source, char* target)
	//{
	//	FILE*  fileHandle = NULL;
	//	if ( !( fileHandle = fopen( source, "rb"))) 
	//		return false;

	//	// ����ļ���С,һ���Զ����ڴ�
	//	fseek( fileHandle, 0, SEEK_END);
	//	size_t iEnd = ftell( fileHandle);
	//	fseek( fileHandle, 0, SEEK_SET);
	//	size_t iStart = ftell( fileHandle);
	//	size_t fileSize = iEnd - iStart;

	//	// Allocate memory for whole file
	//	unsigned char* ucpBuffer = NULL;
	//	ucpBuffer = new unsigned char[ fileSize];

	//	if ( !ucpBuffer) return false;

	//	// load file into buffer
	//	size_t size = fread( ucpBuffer, 1, fileSize, fileHandle);

	//	// close the file , we don't need it any more
	//	fclose( fileHandle);

	//	// д��
	//	FILE*  fileWrite;
	//	if( !( fileWrite = fopen( target, "wb")))
	//		return false;

	//	fwrite( ucpBuffer, 1, fileSize, fileHandle);


	//	delete[] ucpBuffer;
	//}

	// ת����Ares�ռ�
	Ares::Transform GMatrixToAresTransform( const GMatrix& mat)
	{
		Ares::Transform result;

		const Ares::Matrix44& mat44 = (const Ares::Matrix44&)mat;
		result.m_rotation.FromMatrix( mat44);
		result.m_rotation.y = -result.m_rotation.y;
		result.m_origin = Ares::Vector3( mat44._41, -mat44._42, mat44._43);

		result.m_origin.x *=  g_config.m_scale.x;
		result.m_origin.y *=  g_config.m_scale.y;
		result.m_origin.z *=  g_config.m_scale.z;

		return result;
	}

	// ת��
	void Point3ToSM1Vertex( Ares::SM1Vertex& oV, const Point3& iV)
	{
		oV.m_fVert[0] =   iV.x * g_config.m_scale.x;
		oV.m_fVert[1] =  -iV.y * g_config.m_scale.y;
		oV.m_fVert[2] =   iV.z * g_config.m_scale.z;
	}
}