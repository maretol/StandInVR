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

	VERTEX3DSHADER Vertex[4];
	unsigned short Index[6];
	int vshandle;
	int pshandle;
	int texhandle;
	int x;
	int xadd;
	float color;
	float coloradd;
	int ModelHandle;
	FLOAT4 f4;

	// 2D

	DrawBox(0, 0, 640, 480, GetColor(200, 200, 200), TRUE);	// ��ʑS�̂���]�̐F�œh��Ԃ�


	//3D

	// �y�o�b�t�@��L���ɂ���
	SetUseZBuffer3D(TRUE);

	// �y�o�b�t�@�ւ̏������݂�L���ɂ���
	SetWriteZBuffer3D(TRUE);

	// �R�c��ԏ�ɃJ�v�Z����`�悷��
	DrawCapsule3D(VGet(320.0f, 100.0f, 0.0f), VGet(320.0f, 300.0f, 0.0f), 40.0f, 8, GetColor(255, 0, 255), GetColor(255, 255, 255), TRUE);

	// �J����

	// ���f���̓ǂݍ���
	ModelHandle = MV1LoadModel("DxChara.x");

	// ���C�e�B���O�̌v�Z�����Ȃ��悤�ɐݒ��ύX
	SetUseLighting(FALSE);

	// ���f�����J�����̉f��ʒu�Ɉړ�
	MV1SetPosition(ModelHandle, VGet(320.0f, -300.0f, 600.0f));

	// ���f����`��
	MV1DrawModel(ModelHandle);

	//  �V�F�[�_�[���g���ĂQ�c�|���S����`��

	// �Q�|���S�����̒��_�̃f�[�^���Z�b�g�A�b�v
	Vertex[0].pos = VGet(2.0f, 540.0f,0.0f);
	Vertex[0].norm = VGet(0.0f, 0.0f, -1.0f);
	Vertex[0].dif = GetColorU8(255, 0, 255, 255);
	Vertex[0].spc = GetColorU8(0, 0, 0, 0);
	Vertex[0].u = 0.0f;
	Vertex[0].v = 0.0f;
	Vertex[0].su = 0.0f;
	Vertex[0].sv = 0.0f;

	Vertex[1].pos = VGet(420.0f, 340.0f, 0.0f);
	Vertex[1].norm = VGet(0.0f, 0.0f, -1.0f);
	Vertex[1].dif = GetColorU8(0, 0, 255, 255);
	Vertex[1].spc = GetColorU8(0, 0, 0, 0);
	Vertex[1].u = 1.0f;
	Vertex[1].v = 0.0f;
	Vertex[1].su = 0.0f;
	Vertex[1].sv = 0.0f;

	Vertex[2].pos = VGet(220.0f, 140.0f, 0.0f);
	Vertex[2].norm = VGet(0.0f, 0.0f, -1.0f);
	Vertex[2].dif = GetColorU8(255, 255, 0, 255);
	Vertex[2].spc = GetColorU8(0, 0, 0, 0);
	Vertex[2].u = 0.0f;
	Vertex[2].v = 1.0f;
	Vertex[2].su = 0.0f;
	Vertex[2].sv = 0.0f;

	Vertex[3].pos = VGet(420.0f, 140.0f, 0.0f);
	Vertex[3].norm = VGet(0.0f, 0.0f, -1.0f);
	Vertex[3].dif = GetColorU8(255, 255, 0, 255);
	Vertex[3].spc = GetColorU8(0, 0, 0, 0);
	Vertex[3].u = 1.0f;
	Vertex[3].v = 1.0f;
	Vertex[3].su = 0.0f;
	Vertex[3].sv = 0.0f;

	// �Q�|���S�����̒��_�ԍ��z����Z�b�g�A�b�v
	Index[0] = 0;
	Index[1] = 1;
	Index[2] = 2;
	Index[3] = 2;
	Index[4] = 1;
	Index[5] = 3;

	// ���_�V�F�[�_�[��ǂݍ���
	vshandle = LoadVertexShader("VertexShaderTestVS.vso");

	// �s�N�Z���V�F�[�_�[��ǂݍ���
	pshandle = LoadPixelShader("VertexShaderTestPS.pso");

	// �`��Ɏg�p����摜�̓ǂݍ���
	texhandle = LoadGraph("Tex1.bmp");

	// �`���𗠉�ʂɂ���
	SetDrawScreen(DX_SCREEN_BACK);

	// �\�����W���ړ����鏈���̏�����
	x = 0;
	xadd = 8;

	// �F��ω������鏈���̏�����
	color = 0.0f;
	coloradd = 1.0f / 60.0f;

	// ESC�L�[���������܂Ń��[�v
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		// ��ʂ�������
		ClearDrawScreen();

		// ���W���ړ�������
		x += xadd;
		if (x > 200 || x < -200)
		{
			xadd = -xadd;
		}

		// �F�̒l��ω�������
		color += coloradd;
		if (color <= 0.0f || color >= 1.0f)
		{
			coloradd = -coloradd;
		}

		// ���W�l�𒸓_�V�F�[�_�[ float4�^�萔�O�ԂɃZ�b�g
		f4.x = (float)x;
		f4.y = 0.0f;
		f4.z = 0.0f;
		f4.w = 0.0f;
		SetVSConstF(0, f4);

		// �F�̒l���s�N�Z���V�F�[�_�[ float4�^�萔�O�ԂɃZ�b�g
		f4.x = color;
		f4.y = color;
		f4.z = color;
		f4.w = 1.0f;
		SetPSConstF(0, f4);

		// �g�p���钸�_�V�F�[�_�[�̃Z�b�g
		SetUseVertexShader(vshandle);

		// �g�p����s�N�Z���V�F�[�_�[���Z�b�g
		SetUsePixelShader(pshandle);

		// �g�p����e�N�X�`�����O�ԂɃZ�b�g
		SetUseTextureToShader(0, texhandle);

		// �V�F�[�_�[���g�p�����Q�|���S���̕`��
		DrawPolygonIndexed3DToShader(Vertex, 4, Index, 2);

		// ����ʂ̓��e��\��ʂɔ��f������
		ScreenFlip();
	}

	// �g�p�������_�V�F�[�_�[�� float4�^�萔�̐ݒ�𖳌�������
	ResetVSConstF(0, 2);

	// �g�p�����s�N�Z���V�F�[�_�[�� float4�^�萔�̐ݒ�𖳌�������
	ResetPSConstF(0, 1);

	// �ǂݍ��񂾒��_�V�F�[�_�[�̍폜
	DeleteShader(vshandle);

	// �ǂݍ��񂾃s�N�Z���V�F�[�_�[�̍폜
	DeleteShader(pshandle);

	// �L�[���͑҂�������
	WaitKey();

	DxLib_End();
}