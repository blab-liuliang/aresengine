#pragma once

#include <QtGui/QDialog>
#include "ui_VideoSetting.h"

namespace QT_UI
{
	//----------------------------------------
	// ģ�ͱ༭�� ������ 2010-12-30
	//----------------------------------------
	class CVideoSetting : public QDialog, public Ui_VideoSetting
	{
		Q_OBJECT

	public:
		CVideoSetting( QWidget* parent = 0);

	public slots:
		// ����fps
		void  SetFps(float fps);

		// �������������
		void ApplyCameraSettings();

		// ����������ļ��б���ʾ
		void UpdateCameraSettingsDisplay();

	private slots:
		// ���������������Ƹı�
		void SetCameraSettings();

		// ����VideoFillMode
		void  UpdateFillMode();

		// ����alpha����ֵ
		void SetAlphaTestValue( int value);

		// �趨Axis����
		void  SetAxisScale(  double scale);

		// ������ӰSoftNess
		void  SetShadowSampleSize( int size);

		// ������ӰSoftNess
		void  SetShadowLBR( double lbr);

		// ������Ӱ�Ƿ����ģ��
		void SetBlur( bool blur);

		// �Ƿ�����Ӱ
		void SetShadow( bool bShadow);

		// �Ƿ���ʾ����
		void SetCapsuleVisible( bool visible);

		// ����FXAA
		void UpdateFXAA();

		// ����ɫ��ӳ��
		void SetToneMapping();
		
	public slots:
		// ��ʾ��Ӱ Foucs region B( ��Bug��ʱ��)
		void ShowFocusRegionB();
	};
}