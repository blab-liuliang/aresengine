#pragma once

#include <vector>
#include <string>
#include "Core/AresPlatform.h"

using namespace std;

namespace Ares
{
	// TokenType
	enum TokenType
	{
		TKT_UnKnown  = 0,		// δ֪
		TKT_Delimiter,
		TKT_OpenParentheses,	// (
		TKT_CloseParentheses,	// )
		TKT_OpenBracket,		// [
		TKT_CloseBracket,		// ]
		TKT_OpenBrace,			// {
		TKT_CloseBrace,			// }
		TKT_Equal,				// =
		TKT_Quote,
		TKT_Float,
		TKT_String,
	};

	enum
	{
		TKF_StringsOnly = 0x00000001,	// tell tokenizer to only output string tokens
	};

	//---------------------------------
	// CgToken 2012-4-9 ����
	//---------------------------------
	struct CgToken
	{
		TokenType  m_type;		// token type
		int		   m_line;		// line num

		// constructor
		CgToken( int line, TokenType type)
			: m_line( line), m_type( type)
		{}
	};

	// string token
	struct CgTokenString : public CgToken
	{
		string	m_str;

		// constructor
		CgTokenString( int line, const char* string)
			: CgToken( line, TKT_String)
		{
			m_str = string;
		}
	};

	//---------------------------------
	// Cg�Ƿ������� 2012-4-9 ����
	//---------------------------------
	class CgTokenizer
	{
	public:
		// Token state
		enum TokState
		{
			TKS_InWhite,			// �հ״�
			TKS_InText,				// ��Ч�ı�
			TKS_InQuots,			// ���Ŵ�
			TKS_InSingleAnnotation,	// ����ע��
			TKS_InMultiAnnotation,	// ����ע��
		};

		#define  Default_Delims  " \t\r\n,;"

	public:
		// Tokenize the contents of a file
		bool TokenizeFile( const char* fileName, DWORD flags=0, const char* delims=Default_Delims);

		// Tokenize string
		bool TokenizeString( BYTE* code, int size, DWORD flags, const char* delims);

	private:
		// determine what type of token this is
		TokenType ClassifyToken( const char* text, DWORD flags);

		// Try to decide what kind of token this may be
		// �Ƿ�Ϊ�����
		TokenType IsDelimiter( char chTok, const char* delims, int numDelims);

		// Is this a special character already existing as one of our tokens
		TokenType IsSpecialCharacter( char chTok);

		// Finalize a token( determine it's type and make it) and add it to the list
		TokenType FinalizeToken( const char* text, DWORD flags);

		// Allocate a new token
		CgToken* AllocToken( TokenType type, const char* text=NULL);

		// Destroy the current tokens
		void DestroyTokens();

		// Add line num
		void AddLineNum( char chTok);

	private:
		vector<string>		m_errors;			// �����뾯��	

		int					m_curLine;			// ��ǰ��
		int					m_curTokenIdx;		// the current token we're looking at
		vector<CgToken*>	m_tokens;			// the list of tokens
	};
}