//written by Yusei
#include "DxData.h"

DxData::DxData() {
	// �R���X�g���N�^�B�N���X�ϐ��Ȃǂ��`�������ꍇ�������g��
	// �ڂ����͒��ׂ�
}

DxData::~DxData() {
	// �f�X�g���N�^�B���͍l���Ȃ��Ă悢
}

void DxData::setOutputDevice(OUTPUTDEVICE output) {
	// VR�f�o�C�X������� output = OUTPUTDEVICE.HMD ������
	// �Ȃ������� output = OUTPUTDEVICE.MONITOR ������B
	// ���݂͍l�������Ƃ��悵

}

void DxData::Init() {
	// �܂��Ăяo����鏉��������
	// �����ŏ���������

	ChangeWindowMode(true); // �E�B���h�E�ŕ\���Bfalse�őS��ʃ��[�h�i�킩��ɂ������false�ɂ��Ă݂�Ƃ悢�j
	if (DxLib_Init() == -1) {
		return;
	}

}

void DxData::DxMain() {
	// �����ɃO���t�B�b�N�������L��

	DrawPixel(320, 240, GetColor(255, 255, 255));

	WaitKey();
	DxLib_End();
}