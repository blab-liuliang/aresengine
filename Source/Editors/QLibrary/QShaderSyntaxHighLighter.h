#pragma once

#include <QSyntaxHighlighter>
#include <QTextCharFormat>

class QTextDocument;
namespace Qt_Ares
{
	//-------------------------------
	// shader�߶ȱ༭ 2011-04-06
	//-------------------------------
	class QShaderSyntaxHighLighter : public QSyntaxHighlighter
	{
		Q_OBJECT

	public:
		// ���캯��
		QShaderSyntaxHighLighter( QTextDocument* parent = 0);

	protected:
		// �߶�block
		void  highlightBlock( const QString& text);

	private:
		// �߶ȹ���
		struct HighlightingRule
		{
			QRegExp			pattern;
			QTextCharFormat format;
		};

		QRegExp commentStartExpression;
		QRegExp commentEndExpression;
		QTextCharFormat classFormat;
		QTextCharFormat singleLineCommentFormat;
		QTextCharFormat multiLineCommentFormat;
		QTextCharFormat quotationFormat;
		QTextCharFormat functionFormat;
		QTextCharFormat globalFormat;						// ȫ�ֱ���
		QTextCharFormat	mainFunFormat;	

		QVector<HighlightingRule>	m_highLightRules;
		QTextCharFormat				m_keyWordFormat;		// �ؼ��ָ�ʽ
	};
}