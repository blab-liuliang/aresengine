#include "IGame_AnimationManager.h"
#include "Init.h"
#include "AeConfig.h"
#include <BipedApi.h>
#include <bipexp.h>
#include <sstream>
#include <decomp.h>
#include <Core/AresMath.h>
#include "Function.h"

using namespace Ares;
using namespace std;

extern Interface*   g_pI;

namespace M1_IGame
{
	extern IGameScene *     g_pIGame;
	extern SExportConfig    g_config;	// ��������

	// ��ȡ�ؼ�֡ʱ��
	static TimeValue GetKeyTime(Control* control, int i);

	// ���캯��
	CAnimationManager::CAnimationManager()
	{
		// ��ʼ������
		InitScene();
	}

	// ��Ӷ���
	bool CAnimationManager::AddAnimation( const string& aniName, int start, int end, CM1Animation& m1Animation)
	{
		Interval interval;
		interval.SetStart( start * g_pIGame->GetSceneTicks());
		interval.SetEnd( end * g_pIGame->GetSceneTicks());

		// ��ȡ���е�max���
		m_nodes.clear();
		FindAllNodes( m_nodes);

		// ��ȡ�������
		m_boneNodes.clear();
		for ( size_t i=0; i<m1Animation.m_header.m_iNumBones; i++)
		{
			SM1Bone& bone = m1Animation.m_pRootBone[i];
			
			IGameNode* pGameNode = GetIGameNodeByName( bone.m_cName, m_nodes);
			if( pGameNode)
				m_boneNodes.push_back( pGameNode);
			else
			{
				ostringstream oss;
				oss << "�޷���Ӷ���,����\"" << bone.m_cName << "\"������...";

				::MessageBoxA( NULL, oss.str().c_str(), "AresX Warn", MB_OK);

				m_boneNodes.push_back( NULL);
			}
		}

		// ��ȡҪ�뵼�����������
		GetExportBones();

		// �¼�����
		SM1AnimationSet animationSet;

		strcpy( animationSet.m_header.m_cName, aniName.c_str());
		animationSet.m_header.m_fLenght = TicksToSec(interval.Duration()-1);		// ����ʱ��
		animationSet.m_header.m_iNumBoneUses = m_boneNodes.size();
		animationSet.m_boneUsed	   = new bool[m_boneNodes.size()];
		animationSet.m_pAnimations = new SM1Animation[m_boneNodes.size()];

		// ����
		for ( size_t i=0; i<m_boneNodes.size(); i++)
		{
			SM1Animation& boneAnimation = animationSet.m_pAnimations[i];
			bool&		  boneUsed		= animationSet.m_boneUsed[i];

			if( m_boneNodes[i] && IsNeedExport( m_boneNodes[i]))
			{
				// ��������
				boneUsed = true;
				boneAnimation.m_header.m_iBoneIndex = i;

				Control* pControl = m_boneNodes[i]->GetMaxNode()->GetTMController();
				if( g_config.m_keyFrame)
				{
					//SampleQuaternion( boneAnimation, m_boneNodes[i], interval);
					vector<TimeValue> keyTimes;
					GetBoneAnimationSetTime(keyTimes, interval, m_boneNodes[i]);
					if( keyTimes.size() > 0)
						BuildKeys( boneAnimation, m_boneNodes[i], keyTimes, interval);
					else
						SampleKeys( boneAnimation, m_boneNodes[i], interval);
				}
				else
				{
					SampleKeys( boneAnimation, m_boneNodes[i], interval);
				}
			}
			else
			{
				// ����޴˹�������
				boneUsed = false;
				boneAnimation.m_header.m_iBoneIndex = -1;
			}
		}

		// ����animationSet
		int aniSetNum = m1Animation.m_header.m_iNumAnimationSet;
		m1Animation.m_header.m_iNumAnimationSet = aniSetNum+1;
		SM1AnimationSet* tAnimations = m1Animation.m_pAnimationSets;
		m1Animation.m_pAnimationSets = new SM1AnimationSet[ aniSetNum+1];

		// ǰ�ڸ���
		if( tAnimations)
			memcpy( m1Animation.m_pAnimationSets, tAnimations, sizeof( SM1AnimationSet) * aniSetNum);
		
		m1Animation.m_pAnimationSets[aniSetNum] = animationSet;

		// �ͷ��ڴ�
		for ( int i=0; i<aniSetNum; i++)
		{	
			tAnimations[i].m_pAnimations = NULL;
			tAnimations[i].m_boneUsed	 = NULL;
		}

	
		if( aniSetNum)
			delete[] tAnimations;

		animationSet.m_pAnimations = NULL;
		animationSet.m_boneUsed	   = NULL;

		return true;
	}

	// ɾ������
	bool CAnimationManager::DelAnimation( int aniIndex, CM1Animation& m1Animation)
	{
		int oldAniSetNum = m1Animation.m_header.m_iNumAnimationSet;

		// �Ϸ��Լ��
		if( oldAniSetNum < aniIndex || aniIndex < 0)
			return false;

		if( m1Animation.m_pAnimationSets[aniIndex].m_pAnimations)
			delete[] m1Animation.m_pAnimationSets[aniIndex].m_pAnimations;
		if( m1Animation.m_pAnimationSets[aniIndex].m_boneUsed)
			delete[] m1Animation.m_pAnimationSets[aniIndex].m_boneUsed;

		for( int j=aniIndex; j<oldAniSetNum-1; j++)
		{
			m1Animation.m_pAnimationSets[j] = m1Animation.m_pAnimationSets[j+1];
		}

		// ��ֹ2��ɾ��
		m1Animation.m_pAnimationSets[oldAniSetNum-1].m_pAnimations = NULL;
		m1Animation.m_pAnimationSets[oldAniSetNum-1].m_boneUsed	   = NULL;

		m1Animation.m_header.m_iNumAnimationSet--;

		return true;
	}

	// �޸Ķ�������
	bool CAnimationManager::EditAnimation( const string& newName, int index,CM1Animation& m1Animation)
	{
		return true;
	}

	// ��������˳��
	bool CAnimationManager::ExchangeAnimation( int index0, int index1, CM1Animation& m1Animation)
	{
		return true;
	}

	// ����ӽ��
	void CAnimationManager::FindChildNodes( IGameNode* parent, vector<IGameNode*>& out)
	{
		if( !parent)
			return;

		for ( int i=0; i<parent->GetChildCount(); i++)
		{
			IGameNode* tChild = parent->GetNodeChild( i);
			if( tChild)
			{
				out.push_back( tChild);

				FindChildNodes( tChild, out);
			}
		}
	}

	// ��ȡ���нӵ�
	void CAnimationManager::FindAllNodes( vector<IGameNode*>& out)
	{
		out.clear();

		for( int i=0; i<g_pIGame->GetTopLevelNodeCount(); i++)
		{
			IGameNode* topNode = g_pIGame->GetTopLevelNode( i);
			out.push_back( topNode);

			FindChildNodes( topNode, out);
		}
	}

	// ��ȡ���
	IGameNode* CAnimationManager::GetIGameNodeByName( const char* name, vector<IGameNode*>& nodes)
	{
		for ( size_t i=0; i<nodes.size(); i++)
		{
			IGameNode* pNode = nodes[i];
			if( !pNode)
				return NULL;

			if( strcmp( pNode->GetName(), name)==0)
				return pNode;
		}

		return NULL;
	}

	// ����TransKeys
	void CAnimationManager::BuildKeys( SM1Animation& boneAnimation, IGameNode* pGameNode, vector<TimeValue>& keyTimes,Interval interval)
	{	
		boneAnimation.m_header.m_iNumRotationKeys = keyTimes.size();
		boneAnimation.m_header.m_iNumTransKeys	  = keyTimes.size();

		boneAnimation.m_pRotationKeys = new SM1AnimationQuaternionKey[keyTimes.size()];
		boneAnimation.m_pTransKeys    = new SM1AnimationVectorKey[keyTimes.size()];

		for( size_t i=0; i<keyTimes.size(); i++)
		{
			TimeValue t		  = keyTimes[i];
			TimeValue tn	  = t - interval.Start();
			Transform  tfL	  = GMatrixToAresTransform( pGameNode->GetWorldTM( t));
			IGameNode* parent = pGameNode->GetNodeParent();
			if ( parent && IsBone( parent))
			{
				Transform tfP = GMatrixToAresTransform( parent->GetWorldTM( t));
				
				tfL = ~tfP * tfL;
			}

			// ʱ��
			boneAnimation.m_pRotationKeys[i].m_fTime = TicksToSec( tn);
			boneAnimation.m_pTransKeys[i].m_fTime    = TicksToSec( tn);
			
			memcpy( boneAnimation.m_pRotationKeys[i].m_quatKey, &tfL.m_rotation, sizeof( Ares::Quat));
			memcpy( boneAnimation.m_pTransKeys[i].m_vecKey, &tfL.m_origin, sizeof( Ares::Vector3)); 
		}
	}

	// ��������
	void CAnimationManager::SampleKeys( SM1Animation& boneAnimation, IGameNode* pGameNode, Interval interval)
	{
		int    delta   = g_pIGame->GetSceneTicks() * g_config.m_sampledensity;
		int    numKeys = ( interval.Duration()) / delta + 1;

		if((interval.Duration()-1) % delta)
			numKeys += 1;

		if( numKeys > 0)
		{
			boneAnimation.m_header.m_iNumMatKeys    = numKeys;

			boneAnimation.m_pMatKeys = new SM1AnimationMatrixKey[numKeys];
		}

		vector<AngAxis> angAxis;
		angAxis.clear();
		for ( int i=0; i<numKeys; i++)
		{
			TimeValue tn  = i  * delta;

			// ��ֹ����
			if( tn >= interval.Duration())
				tn = interval.Duration()-1;

			TimeValue t   = tn + interval.Start();

			GMatrix  matT = pGameNode->GetWorldTM( t);

			IGameNode* parent = pGameNode->GetNodeParent();
			if ( parent && IsBone( parent))
			{
				GMatrix matParent = parent->GetWorldTM( t);
				matParent = matParent.Inverse();

				matT *=  matParent;
			}

			// ʱ��
			boneAnimation.m_pMatKeys[i].m_fTime		 = TicksToSec( tn);

			// data
			for ( int j=0; j<4; j++)
				for ( int k=0; k<4; k++)
				{
					boneAnimation.m_pMatKeys[i].m_matKey[j][k] = matT[j][k];
				}

			//boneAnimation.m_pMatKeys[i].m_matKey[3][0] *= g_config.m_scale.x;
			//boneAnimation.m_pMatKeys[i].m_matKey[3][1] *= g_config.m_scale.y;
			//boneAnimation.m_pMatKeys[i].m_matKey[3][2] *= g_config.m_scale.z;
		}
	}

	struct M1Key : public IKey
	{
		float val[1024];
	};

	// ��ȡ�ؼ�֡ʱ��
	static TimeValue GetKeyTime(Control* control, int i)
	{
		if( !control)
			return 0;

		static M1Key key;
		IKeyControl* keyControl = GetKeyControlInterface( control);
		if( keyControl)
		{
			keyControl->GetKey( i, &key);

			TimeValue time = key.time;

			return time;
		}

		return -1;
	}

	// ��ȡ�ؼ�֡ʱ���
	void CAnimationManager::GetBoneAnimationSetTime( vector<TimeValue>& keyTimes, Interval interval, IGameNode* gameNode)
	{
		Control* control = gameNode->GetMaxNode()->GetTMController();

		Control* tControl;
		IBipMaster* pBip = GetBipMasterInterface( control);
		if( pBip)
		{
			Point3 pos = pBip->GetBipedPos( 0, gameNode->GetMaxNode());
			//Quat   quat= pBip->GetBipedRot( 0, gameNode->GetMaxNode());

			// ˮƽ������
			tControl = pBip->GetHorizontalControl();
			AddKeyTime( keyTimes, tControl, interval);

			// ��ֱ������
			tControl = pBip->GetVerticalControl();
			AddKeyTime( keyTimes, tControl, interval);

			tControl = pBip->GetTurnControl();
			AddKeyTime( keyTimes, tControl, interval);
		}

		// ��bip
		tControl = control->GetPositionController();
		AddKeyTime( keyTimes, tControl, interval);

		tControl = control->GetRotationController();
		AddKeyTime( keyTimes, tControl, interval);

		tControl = control->GetScaleController();
		AddKeyTime( keyTimes, tControl, interval);

		// ��ʼ���β�ؼ���
		AddKeyTime( keyTimes, interval.End());
		AddKeyTime( keyTimes, interval.Start());

		IGameNode* parentNode = gameNode->GetNodeParent();
		if( parentNode && IsBone( parentNode))
			GetBoneAnimationSetTime( keyTimes, interval, parentNode);
	}

	// ��ӿ������ؼ�ʱ���
	void CAnimationManager::AddKeyTime( vector<TimeValue>& keyTimes, Control* contrl, Interval interval)
	{
		if( !contrl)
			return;

		BOOL	bResult;
		for(TimeValue keyTime = interval.Start(); keyTime<=interval.End(); keyTime += g_pIGame->GetSceneTicks())
		{
			bResult =contrl->IsKeyAtTime( keyTime, KEYAT_POSITION|KEYAT_ROTATION|KEYAT_SCALE);
			if(bResult)
				AddKeyTime( keyTimes, keyTime);
		}
	}

	// ��ӹؼ�ʱ���
	void CAnimationManager::AddKeyTime( vector<TimeValue>& keyTimes, TimeValue keyTime)
	{
		vector<TimeValue>::iterator it;
		vector<TimeValue>::iterator	it_below = keyTimes.begin();
		for ( it=keyTimes.begin(); it!=keyTimes.end(); it++)
		{
			if( *it == keyTime)
				return;
			else if( *it < keyTime)
				it_below++;
		}

		keyTimes.insert( it_below, keyTime);
	}

	// �ж�ĳ����Ƿ��ǹ���
	bool CAnimationManager::IsBone( IGameNode* gameNode)
	{
		for ( size_t i=0; i<m_boneNodes.size(); i++)
		{
			if( gameNode == m_boneNodes[i])
				return true;
		}

		return false;
	}

	// �жϹ����Ƿ񵼳�
	bool CAnimationManager::IsNeedExport( IGameNode* gameNode)
	{
		// �ս�����赼��
		if( !gameNode)
			return false;

		// �ǹ���������赼��
		if( !IsBone( gameNode))
			return false;

		// ȫ������
		if( !m_exportNodes.size())
			return true;

		// �Ƿ�Ϊ��Ҫ�����Ĺ���
		IGameNode* parentNode = gameNode;
		while( parentNode)
		{
			for( size_t i=0; i<m_exportNodes.size(); i++)
			{
				if( parentNode == m_exportNodes[i])
				{
					return true;
				}
			}

			parentNode = parentNode->GetNodeParent();
		}
		
		return false;
	}

	// ����ַ���(int)
	static void UnPackString(vector<string>& out, const string& source, char separator)
	{
		std::basic_string <char>::size_type last_pos = 0;
		std::basic_string <char>::size_type pos = 0;
		std::string range_elem;
		while( pos < source.size())
		{
			range_elem.clear();
			pos = source.find( separator, pos);
			for ( size_t i = last_pos;  i < pos; ++i )
			{
				range_elem += source[i];
			}
			last_pos = ++pos;

			out.push_back( range_elem);
		}
	}

	// ��ȡҪ�����Ĺ��������
	void CAnimationManager::GetExportBones()
	{
		m_exportNodes.clear();

		for( int i=0; i<g_pI->GetNumProperties(PROPSET_USERDEFINED); i++)
		{
			const PROPSPEC*	   propSpec= g_pI->GetPropertySpec(PROPSET_USERDEFINED, i);
			const PROPVARIANT* propVar = g_pI->GetPropertyVariant(PROPSET_USERDEFINED, i);

			if(propVar->vt != VT_LPWSTR && propVar->vt != VT_LPSTR)
				continue;

			char	key[1024];
			char	value[1024];
			_tcscpy(key, TSTR(propSpec->lpwstr));
			_tcscpy(value, propVar->vt == VT_LPWSTR ? TSTR(propVar->pwszVal) : TSTR(propVar->pszVal));

			if(!_strnicmp( key,"export_bones", 12))
			{
				vector<string> boneNames;
				UnPackString( boneNames, value, ';');

				for( size_t i=0; i<boneNames.size(); i++)
				{
					IGameNode* boneNode = GetIGameNodeByName( boneNames[i].c_str(), m_boneNodes);
					if( boneNode)
						m_exportNodes.push_back( boneNode);
				}
			}
		}
	}
}