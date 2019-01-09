#include <QtGui/QFileDialog>
#include "TextureTool.h"
#include "Engine/ResSystem/AresResSystem.h"

namespace QT_UI
{
	// ���캯��
	TextureTool::TextureTool( QWidget* parent)
		: QMainWindow( parent)
	{
		setupUi( this);

		connect( m_actionOpen,      SIGNAL(triggered()), this, SLOT(Open()));
		connect( m_actionAddSubTex, SIGNAL(triggered()), this, SLOT(AddSubTex()));

		m_graphicsItem.setFlag( QGraphicsItem::ItemIsMovable, true);
		m_graphicsScene.addItem( &m_graphicsItem);
		m_graphicsView->setScene( &m_graphicsScene);

		m_textureSetBuild = new_ TextureSetBuild;
	}

	// ��������
	TextureTool::~TextureTool()
	{
	}

	// ��ʼ��App
	void TextureTool::InitApp()
	{
	}

	// ��ʾ����
	void TextureTool::ShowTexture( TexturePtr tex)
	{
		int	width  = static_cast<int>(tex->GetWidth( 0));
		int	height = static_cast<int>(tex->GetHeight( 0));

		// ���������ʽ
		A_ASSERT( tex->GetFormat() == EF_ARGB8);
		A_ASSERT( tex->GetType() == Texture::TT_2D);

		Texture::Modifier modifie( *tex, TMA_ReadWrite, 0, 0, 0, 0, width, height);
		uchar* colors = modifie.GetPointer<uchar>();

		QImage image( colors, width, height, QImage::Format_ARGB32);

		// deal with the TGA flipping of axis
		// bit5 == 0 : flip
		// bit5 == 1 : don't flip
		// image = image.mirrored( 0, !(header.descriptor&16)); // copies the image. performance loss, but who cares ;-)

		m_graphicsItem.setPixmap( QPixmap( QPixmap::fromImage(image)));
	}

	// ������
	void TextureTool::Open()
	{
		m_textureSetBuild->SetTextureSize( 1024, 1024, EF_ARGB8);

		ShowTexture( m_textureSetBuild->GetResultTexture());
	}

	// �������������
	void TextureTool::AddSubTex()
	{
		QString fileName = QFileDialog::getOpenFileName( this, tr("������"), "", tr("(*.dds)"));
		if( !fileName.isEmpty())
		{
			string tFileName = fileName.toStdString();
			m_textureSetBuild->Insert( tFileName.c_str());

			ShowTexture( m_textureSetBuild->GetResultTexture());
		}
	}
}