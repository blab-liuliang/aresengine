#include <QtGui>
#include "QLuaSyntaxHighLighter.h"

namespace Qt_Ares
{
	// ���캯��
	QLuaSyntaxHighLighter::QLuaSyntaxHighLighter( QTextDocument* parent)
		: QSyntaxHighlighter( parent)
	{
		HighlightingRule rule;

		//functionFormat.setFontItalic(true);
		functionFormat.setForeground(Qt::darkRed);
		rule.pattern = QRegExp("\\b[A-Za-z0-9_]+(?=\\()");
		rule.format = functionFormat;
		m_highLightRules.append(rule);

		m_keyWordFormat.setForeground( Qt::blue);
		QStringList keywordPatterns;
		keywordPatterns << "\\bfunction\\b"  << "\\bend\\b"  << "\\bboolean\\b"  << "\\blocal\\b"  << "\\bbool4\\b"
						<< "\\bhalf\\b"  << "\\bhalf1\\b"  << "\\bhalf2\\b"  << "\\bhalf3\\b"  << "\\bhalf4\\b"
						<< "\\bfloat\\b" << "\\bfloat1\\b" << "\\bfloat2\\b" << "\\bfloat3\\b" << "\\bfloat4\\b" 
						<< "\\double\\b" << "\\bdouble1\\b"<< "\\bdouble2\\b"<< "\\bdouble3\\b"<< "\\bdouble4\\b" 
						<< "\\bint\\b"   << "\\bint1\\b"   << "\\bint2\\b"   << "\\bint3\\b"   << "\\bint4\\b" 
						<< "\\buniform\\b"<<"\\bshared\\b" <<"\\bstruct\\b" << "\\breturn\\b" ;

		foreach( const QString& pattern, keywordPatterns)
		{
			rule.pattern = QRegExp( pattern);
			rule.format  = m_keyWordFormat;
			m_highLightRules.append( rule);
		}

		classFormat.setForeground(Qt::darkMagenta);
		rule.pattern = QRegExp("\\bQ[A-Za-z]+\\b");
		rule.format = classFormat;
		m_highLightRules.append(rule);

		// ȫ�ֱ���
		QStringList globalVarialPatterns;
		globalVarialPatterns << "\\bg_viewProj\\b"  << "\\bg_time\\b" << "\\bg_world\\b"<<"\\bg_lightVP\\b"<<"\\bg_lightVPR\\b"<<"\\bg_shadowMap\\b" <<"\\bg_camPos\\b";
		globalFormat.setForeground( Qt::lightGray);
		foreach( const QString& pattern, globalVarialPatterns)
		{
			rule.pattern = QRegExp( pattern);
			rule.format  = globalFormat;
			m_highLightRules.append( rule);
		}

		singleLineCommentFormat.setForeground(Qt::darkGreen);
		rule.pattern = QRegExp("--[^\n]*");
		rule.format = singleLineCommentFormat;
		m_highLightRules.append(rule);

		multiLineCommentFormat.setForeground(Qt::darkGreen);

		quotationFormat.setForeground(Qt::darkGreen);
		rule.pattern = QRegExp("\".*\"");
		rule.format = quotationFormat;
		m_highLightRules.append(rule);

		commentStartExpression = QRegExp("/\\*");
		commentEndExpression = QRegExp("\\*/");
	}

	// �߶�block
	void  QLuaSyntaxHighLighter::highlightBlock( const QString& text)
	{
		foreach (const HighlightingRule &rule, m_highLightRules) 
		{
			QRegExp expression(rule.pattern);
			int index = expression.indexIn(text);

			while (index >= 0) 
			{
				int length = expression.matchedLength();
				setFormat(index, length, rule.format);
				index = expression.indexIn(text, index + length);
			}
		}

		setCurrentBlockState(0);

		int startIndex = 0;
		if (previousBlockState() != 1)
			startIndex = commentStartExpression.indexIn(text);

		while (startIndex >= 0) 
		{
			int endIndex = commentEndExpression.indexIn(text, startIndex);
			int commentLength;
			if (endIndex == -1) 
			{
				setCurrentBlockState(1);
				commentLength = text.length() - startIndex;
			} else 
			{
				commentLength = endIndex - startIndex + commentEndExpression.matchedLength();
			}

			setFormat(startIndex, commentLength, multiLineCommentFormat);
			startIndex = commentStartExpression.indexIn(text, startIndex + commentLength);
		}
	}
}