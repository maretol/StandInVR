//written by Yusei
#include "DxData.h"
#include "DxLib.h"


// �v���O������ WinMain ����n�܂�܂�

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

	int ModelHandle;

	// �c�w���C�u�����̏�����
	if (DxLib_Init() < 0)
	{
		// �G���[�����������璼���ɏI��
		return;
	}

	// �y�o�b�t�@��L���ɂ���
	SetUseZBuffer3D(TRUE);

	// �y�o�b�t�@�ւ̏������݂�L���ɂ���
	SetWriteZBuffer3D(TRUE);

	// �R�c��ԏ�ɉ~����`�悷��
	DrawCone3D(VGet(320.0f, 400.0f, 0.0f), VGet(320.0f, 100.0f, 0.0f), 80.0f, 16, GetColor(0, 0, 255), GetColor(255, 255, 255), TRUE);




	// ���f���̓ǂݍ���
	ModelHandle = MV1LoadModel("DxChara.x");

	// ���C�e�B���O�̌v�Z�����Ȃ��悤�ɐݒ��ύX
	SetUseLighting(FALSE);

	// ���f�����J�����̉f��ʒu�Ɉړ�
	MV1SetPosition(ModelHandle, VGet(320.0f, -300.0f, 600.0f));

	// ���f����`��
	MV1DrawModel(ModelHandle);

	// �L�[�̓��͑҂�
	WaitKey();
	
	// �c�w���C�u�����̌�n��
	DxLib_End();
}